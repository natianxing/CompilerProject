#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>
#include <set>
#include <map>
#include <stack>
#include <cctype>
#include <cassert>
#include "IR.h"
#include "IRMutator.h"
#include "IRVisitor.h"
#include "IRPrinter.h"
#include "type.h"

#define INF 0x7fffffff;
using namespace Boost::Internal;
Json::Value root;
Json::Reader reader;
std::map<std::string, Expr> varList;
std::map<std::string, Expr> indexList;
std::map<std::string, int> indexRange;
std::vector<std::string> LHSindex;
std::vector<std::string> RHSindex;
std::map<std::string, int> condition;
int tmpNumber;
//default domain
Type index_type = Type::int_scalar(32);
Type data_type;
Expr default_dom = Dom::make(index_type, 0, 0);

int getProsity(char ch)
{
    int prosity = -1;
    if(ch == '(' || ch == ')')
    {
        prosity = 0;
    }
    if(ch == '+' || ch == '-')
    {
        prosity = 1;
    }
    if(ch == '*' || ch == '/' || ch == '%')
    {
        prosity = 2;
    }
    return prosity;
}
//build index 
Expr cal(char optr, Expr opnd2, Expr opnd1)
{
    Expr result;
    switch (optr)
    {
    case '+':
        return Binary::make(data_type, BinaryOpType::Add, opnd1, opnd2);
        break;
    case '-':
        return Binary::make(data_type, BinaryOpType::Sub, opnd1, opnd2);
        break;
    case '*':
        return Binary::make(data_type, BinaryOpType::Mul, opnd1, opnd2);
        break;
    case '/':
        return Binary::make(data_type, BinaryOpType::Div, opnd1, opnd2);
        break;
    case '%':
        return Binary::make(data_type, BinaryOpType::Mod, opnd1, opnd2);
        break;
    default:
        std::cout<<"Unknown operator: "<<optr<<std::endl;
        exit(0);
        break;
    }
}
Expr makeIndex(std::string s, int range)
{
    //std::cout<<"Index: ["<<s<<"] Range: "<<range<<std::endl;
    int length = s.length();
    std::map<std::string, Expr>::iterator iter;
    std::stack<Expr> opnd;
    std::stack<char> optr;
    std::string tmpStr,name;
    for(int i = 0; i < length; i++)
    {
        // identifier begins with alpha or _
        if(isalpha(s[i])||s[i] == '_')
        {
            int j = 0;
            while((isalpha(s[i+j])||isdigit(s[i+j])||s[i+j] == '_')&& i+j<length)
                j++;
            name = s.substr(i,j);
            iter = indexList.find(name);
            if(iter == indexList.end())
            {
                indexList.insert(std::map<std::string,Expr>::value_type(name,Index::make(index_type, name, default_dom, IndexType::Spatial)));
                indexRange[name] = 0x7fffffff;
                RHSindex.push_back(name);
            }
            opnd.push(indexList[name]);
            i = i + j;
        }
        // IntV begins with digit
        else if(isdigit(s[i]))
        {
            int j = 0;
            while(isdigit(s[i + j])&&i + j < length)
                j++;
            tmpStr = s.substr(i,j);
            opnd.push(IntImm::make(Type::int_scalar(32),std::stoi(tmpStr)));
            i = i + j;
        }
        // deal with operator
        else if(s[i] != ' ')
        {
            if(s[i] == '/' && s[i + 1] == '/')
                i++;
            if(s[i] == '(')
                optr.push(s[i]);
            else if(s[i] == ')')
            {
                while(optr.top() != '(')
                {
                    Expr opnd1 = opnd.top();
                    opnd.pop();
                    Expr opnd2 = opnd.top();
                    opnd.pop();
                    opnd.push(cal(optr.top(),opnd1,opnd2));
                    optr.pop();
                }
                optr.pop();
            }
            else
            {
                if(optr.empty()||getProsity(optr.top())<getProsity(s[i]))
                    optr.push(s[i]);
                else
                {
                    while(!optr.empty()&&getProsity(optr.top())>=getProsity(s[i]))
                    {
                        Expr opnd1 = opnd.top();
                        opnd.pop();
                        Expr opnd2 = opnd.top();
                        opnd.pop();
                        opnd.push(cal(optr.top(),opnd1,opnd2));
                        optr.pop();
                    }
                    optr.push(s[i]);
                }
            }
        }
    }
    while(!optr.empty())
    {
        Expr opnd1 = opnd.top();
        opnd.pop();
        Expr opnd2 = opnd.top();
        opnd.pop();
        opnd.push(cal(optr.top(),opnd1,opnd2));
        optr.pop();
    }
    assert(opnd.size() == 1);
    Expr index = opnd.top();
    opnd.pop();
    // single index 
    if(index->node_type() == IRNodeType::Index)
    {
        
        indexRange[s] = std::min(range,indexRange[s]);
        //std::cout<<s<<" "<<indexRange[s]<<std::endl;
    }
    // complex index
    else if(index->node_type() != IRNodeType::IntImm)
    {
        condition[s] = range;
    }
    indexList.insert(std::map<std::string,Expr>::value_type(s,index));
    return index;
}
Expr makeVarFirst(std::string name, std::string shape, std::string args)
{
    //std::cout<<"Var: name: "<<name<<" shape: "<<shape<<" args: "<<args<<std::endl;
    //first appearance;

    std::string tmpStr;
    std::vector<size_t> shapeArray;
    std::vector<Expr> argsArray;
    int length = shape.length();
    int j = 0;
    for(int i = 0; i < length; i++)
    {
        j = 0;
        while(isdigit(shape[i + j])&&i + j < length)
            j++;
        tmpStr = shape.substr(i,j);
        shapeArray.push_back(std::stoi(tmpStr));
        i = i + j + 1;
    }
    length = args.length();
    j = 0;
    int count = 0;
    for(int i = 0; i < length; i++)
    {
        j = 0;
        while(args[i+j]!=','&&i + j < length)
            j++;
        tmpStr = args.substr(i,j);
        //std::cout<<"ind"<<tmpStr<<" "<<i<<" "<<j<<std::endl;
        i = i + j + 1;
        argsArray.push_back(makeIndex(tmpStr, shapeArray[count]));
        count++;
    }
    return Var::make(data_type, name, argsArray, shapeArray);
}
Expr makeVar(std::string name, std::string shape, std::string args)
{
    //std::cout<<"Var: name: "<<name<<" shape: "<<shape<<" args: "<<args<<std::endl;
    //first appearance;
    std::map<std::string,Expr>::iterator iter;
    iter = varList.find(name);
    if(iter == varList.end())
        varList.insert(std::map<std::string,Expr>::value_type(name,makeVarFirst(name,shape,shape)));

    std::string tmpStr;
    std::vector<size_t> shapeArray;
    std::vector<Expr> argsArray;
    int length = shape.length();
    int j = 0;
    for(int i = 0; i < length; i++)
    {
        j = 0;
        while(isdigit(shape[i + j])&&i + j < length)
            j++;
        tmpStr = shape.substr(i,j);
        shapeArray.push_back(std::stoi(tmpStr));
        i = i + j + 1;
    }
    length = args.length();
    j = 0;
    int count = 0;
    for(int i = 0; i < length; i++)
    {
        j = 0;
        while(args[i+j]!=','&&i + j < length)
            j++;
        tmpStr = args.substr(i,j);
        //std::cout<<"ind"<<tmpStr<<" "<<i<<" "<<j<<std::endl;
        i = i + j + 1;
        argsArray.push_back(makeIndex(tmpStr, shapeArray[count]));
        count++;
    }
    return Var::make(data_type, name, argsArray, shapeArray);
}
// scan the kernel expression, construct Var and Index
// form an expression tree
Expr makeTree(std::string kernel)
{
    //std::cout<<"Expression: "<<kernel<<std::endl;
    int length = kernel.length();
    std::stack<Expr> opnd;
    std::stack<char> optr;
    for(int i = 0; i < length; i++)
    {
        // identifier begins with alpha or _
        if(isalpha(kernel[i])||kernel[i] == '_')
        {
            std::string name,shape,args;
            std::map<std::string,Expr>::iterator iter;
            int j = 0;
            while((isalpha(kernel[i+j])||isdigit(kernel[i+j])||kernel[i+j] == '_')&& i+j<length)
                j++;
            name = kernel.substr(i,j);
            /*iter = varList.find(name);
            if(iter == varList.end())
            {
                std::cout<<"Unknown identifier: "<<name<<std::endl;
                exit(0);
            }*/
            i = i + j;
            j = 0;
            if(kernel[i] == '<')
            {
                while(kernel[i+j] != '>')
                    j++;
                shape = kernel.substr(i+1,j-1);
                i = i + j + 1;
                j = 0;
            }
            if(kernel[i] == '[')
            {
                while(kernel[i+j] != ']')
                    j++;
                args = kernel.substr(i+1,j-1);
                i = i + j;
                j = 0;
            }
            opnd.push(makeVar(name,shape,args));
        }
        // Imm number
        else if(isdigit(kernel[i]))
        {
            std::string tmpStr;
            bool isInt = true;
            int j = 0;
            while((isdigit(kernel[i+j])||kernel[i+j] == '.')&&i+j<length)
            {
                j++;
                if(kernel[i+j]=='.')
                    isInt = false;
            }
            tmpStr = kernel.substr(i,j);
            //std::cout<<"ImmNumber"<<tmpStr<<std::endl;
            if(isInt)
                opnd.push(IntImm::make(Type::int_scalar(32), std::stoi(tmpStr)));
            else
                opnd.push(FloatImm::make(Type::float_scalar(32), std::stof(tmpStr)));
            i = i + j;
        }
        // deal with operator
        else if(kernel[i] != ' ')
        {
            //std::cout<<"Operator: "<<kernel[i]<<std::endl;
            if(kernel[i] == '/' && kernel[i + 1] == '/')
                i++;
            if(kernel[i] == '(')
                optr.push(kernel[i]);
            else if(kernel[i] == ')')
            {
                while(optr.top() != '(')
                {
                    Expr opnd1 = opnd.top();
                    opnd.pop();
                    Expr opnd2 = opnd.top();
                    opnd.pop();
                    opnd.push(cal(optr.top(),opnd1,opnd2));
                    optr.pop();
                }
                optr.pop();
            }
            else
            {
                if(optr.empty()||getProsity(optr.top())<getProsity(kernel[i]))
                    optr.push(kernel[i]);
                else
                {
                    while(!optr.empty()&&getProsity(optr.top())>=getProsity(kernel[i]))
                    {
                        Expr opnd1 = opnd.top();
                        opnd.pop();
                        Expr opnd2 = opnd.top();
                        opnd.pop();
                        opnd.push(cal(optr.top(),opnd1,opnd2));
                        optr.pop();
                    }
                    optr.push(kernel[i]);
                }
            }
        }
    }
    while(!optr.empty())
    {
        Expr opnd1 = opnd.top();
        opnd.pop();
        Expr opnd2 = opnd.top();
        opnd.pop();
        opnd.push(cal(optr.top(),opnd1,opnd2));
        optr.pop();
    }
    assert(opnd.size() == 1);
    Expr expression = opnd.top();
    opnd.pop();
    return expression;
}
Stmt makeStmt(std::string kernel)
{
    //std::cout<<"Sentence: "<<kernel<<std::endl;
    indexList.clear();
    indexRange.clear();
    LHSindex.clear();
    RHSindex.clear();
    int length = kernel.length();
    std::size_t begin = 0;

    // find the LHS
    std::string name,shape,args;
    std::string tmpStr;
    std::map<std::string,Expr>::iterator iter;
    int i = 0;
    int j = 0;
    while((isalpha(kernel[i+j])||isdigit(kernel[i+j])||kernel[i+j] == '_')&& i+j<length)
        j++;
    name = kernel.substr(i,j);
    /*iter = varList.find(name);
    if(iter == varList.end())
    {
        std::cout<<"Unknown identifier: "<<name<<std::endl;
        exit(0);
    }*/
    i = i + j;
    j = 0;
    if(kernel[i] == '<')
    {
        while(kernel[i+j] != '>')
            j++;
        shape = kernel.substr(i+1,j-1);
        i = i + j + 1;
        j = 0;
    }
    if(kernel[i] == '[')
    {
        while(kernel[i+j] != ']')
            j++;
        args = kernel.substr(i+1,j-1);
        i = i + j + 1;
        j = 0;
    }

    length = args.length();
    j = 0;
    //std::cout<<"LHSargs: "<<args<<std::endl;
    for(int k = 0; k < length; k++)
    {
        j = 0;
        while(args[k+j]!=','&&k + j < length)
            j++;
        tmpStr = args.substr(k,j);
        //std::cout<<tmpStr<<"|";
        k = k + j + 1;
        LHSindex.push_back(tmpStr);
        indexList.insert(std::map<std::string,Expr>::value_type(tmpStr,Index::make(index_type, tmpStr, default_dom, IndexType::Spatial)));
        indexRange[tmpStr] = INF;
    }
    //std::cout<<std::endl;
    i++;
    Expr LHS = makeVar(name,shape,args);
    tmpNumber++;
    Expr TMP = makeVar("tmp"+std::to_string(tmpNumber),shape,args);
    //Stmt declare = Declare::make(data_type, TMP);
    std::vector<Stmt> stmtList;
    std::vector<Expr> loop;
    //stmtList.push_back(declare);
    Stmt tmpStmt, emptyStmt;
    emptyStmt = Move::make(TMP,0,MoveType::MemToMem);
    //tmp value set 0
    tmpStmt = Move::make(TMP,0,MoveType::MemToMem);
    stmtList.push_back(tmpStmt);
    int flag = 0;
    j = i;
    length = kernel.length();
    for(i; i < length; i++)
    {
        if(kernel[i] == '['||kernel[i] == '(')
            flag++;
        if(kernel[i] == ']'||kernel[i] == ')')
            flag--;
        // outer range + - 
        if(flag == 0)
        {
            if(kernel[i] == '+' || kernel[i] == '-' || kernel[i] == ';')
            {
                condition.clear();
                tmpStr = kernel.substr(j + 1,i - j - 1);
                Expr tmpExp = makeTree(tmpStr);
                if(kernel[j] == '+' || kernel[j] == '=')
                    tmpStmt = Move::make(TMP, Binary::make(data_type, BinaryOpType::Add, TMP, tmpExp), MoveType::MemToMem);
                else
                    tmpStmt = Move::make(TMP, Binary::make(data_type, BinaryOpType::Add, TMP, tmpExp), MoveType::MemToMem);
                // if stmt
                for (std::map<std::string, int>::iterator it = condition.begin(); it!=condition.end(); it++)
                {
                    Expr cond1 = Compare::make(index_type,CompareOpType::GE,indexList[it->first],IntImm::make(Type::int_scalar(32), 0));
                    tmpStmt = IfThenElse::make(cond1, tmpStmt, emptyStmt);
                    Expr cond2 = Compare::make(index_type,CompareOpType::LE,indexList[it->first],IntImm::make(Type::int_scalar(32), it->second));
                    tmpStmt = IfThenElse::make(cond2, tmpStmt, emptyStmt);
                }
                // loop nest
                loop.clear();
                //std::cout<<"innerloop: ";
                for (int k = 0; k < RHSindex.size(); k++)
                {
                    std::string ind = RHSindex[k];
                    //std::cout<<ind<<" ";
                    loop.push_back(Index::make(index_type,ind,Dom::make(index_type,0,indexRange[ind]),IndexType::Spatial));
                    //indexList[ind]->set_dom(Dom::make(index_type,0,indexRange[ind]));
                }
                //std::cout<<std::endl;
                tmpStmt = LoopNest::make(loop, {tmpStmt});
                stmtList.push_back(tmpStmt);
                j = i + 1;
            }
        }
    }
    ///stmtList.push_back(Move::make(LHS,TMP,MoveType::MemToMem));
    // loop nest
    loop.clear();
    //std::cout<<"outerloop: ";
    for (int k = 0; k < LHSindex.size(); k++)
    {
        std::string ind = LHSindex[k];
        //std::cout<<ind<<" "<<indexRange[ind]<<" |";
        loop.push_back(Index::make(index_type,ind,Dom::make(index_type,0,indexRange[ind]),IndexType::Spatial));
        //indexList[ind]->set_dom(Dom::make(index_type,0,indexRange[ind]));
    }
    //std::cout<<std::endl;
    tmpStmt = LoopNest::make(loop, stmtList);
    Stmt moveStmt = LoopNest::make(loop, {Move::make(LHS,TMP,MoveType::MemToMem)});
    //tmp value declaration
    Expr _TMP = makeVar("tmp"+std::to_string(tmpNumber),shape,shape);
    Stmt finalStmt = LoopNest::make({},{Move::make(_TMP,0,MoveType::Declaration),tmpStmt,moveStmt});
    return finalStmt;
}
// divide into sentences and build the Group
void parseKernel(std::string s)
{
    tmpNumber = 0;
    int length = s.length();
    std::string tmpStr;
    size_t begin = 0;
    size_t end = 0;
    std::vector<Stmt> stmtList;
    std::vector<Expr> inputs;
    std::vector<Expr> outputs;
    while(end!=s.npos)
    {
        end = s.find(';',begin);
        if(end != s.npos)
        {
            tmpStr = s.substr(begin, end-begin + 1);
            begin = end + 2;
            //std::cout<<tmpStr;
            stmtList.push_back(makeStmt(tmpStr));
        }
    }
    std::set<std::string> names;
    for (int i = 0; i < root["ins"].size();i++)
    {
        names.insert(root["ins"][i].asString());
        inputs.push_back(varList[root["ins"][i].asString()]);
    }
    std::set<std::string>::iterator iter;
    for (int i = 0; i < root["outs"].size();i++)
    {
        iter = names.find(root["outs"][i].asString());
        if(iter == names.end())
            outputs.push_back(varList[root["outs"][i].asString()]);
    }
    Group kernel = Kernel::make(root["name"].asString(), inputs, outputs, stmtList, KernelType::CPU);
    varList.clear();
    // visitor
    IRVisitor visitor;
    kernel.visit_group(&visitor);

    //std::cout<<"debug!!!!"<<std::endl;
    // mutator
    IRMutator mutator;
    kernel = mutator.mutate(kernel);

    // printer
    IRPrinter printer(root["data_type"].asString());
    std::string code = printer.print(kernel);
    std::string outputfilename = "./kernels/" + root["name"].asString() + ".cc";
    std::ofstream ofile(outputfilename);
    ofile<<code;
    //std::cout<<code;
    ofile.close();
}
std::string format(std::string s)
{
    size_t pos;
    while(1)
    {
        pos = s.find(' ');
        if(pos == s.npos)
            break;
        s = s.erase(pos,1);
    }
    int length = s.length();
    std::string str;
    for(int i = 0; i < length; i++)
    {
        if(s[i] == ',')
        {
            str.push_back(s[i]);
            str.push_back(' ');
        }
        else if(s[i] == ';')
        {
            str.push_back(s[i]);
            str.push_back(' ');
        }
        else if (s[i] == '=')
        {
            str.push_back(' ');
            str.push_back(s[i]);
            str.push_back(' ');
        }
        else if (s[i] == '+')
        {
            str.push_back(' ');
            str.push_back(s[i]);
            str.push_back(' ');
        }
        else if (s[i] == '-')
        {
            str.push_back(' ');
            str.push_back(s[i]);
            str.push_back(' ');
        }
        else if (s[i] == '*')
        {
            str.push_back(' ');
            str.push_back(s[i]);
            str.push_back(' ');
        }
        else if (s[i] == '/')
        {
            if(s[i+1] != '/')
            {
            str.push_back(' ');
            str.push_back(s[i]);
            str.push_back(' ');
            }
            else
            {
            str.push_back(' ');
            str.push_back(s[i]);
            str.push_back(s[i]);
            str.push_back(' ');
            }
            
        }
        else if (s[i] == '%')
        {
            str.push_back(' ');
            str.push_back(s[i]);
            str.push_back(' ');
        }
        else
        {
            str.push_back(s[i]);
        }
    }
    return str;
}
// parse json file
void parse(std::ifstream& ifile)
{
    if (!reader.parse(ifile,root))
    {
        std::cout<<"failed to parse json file";
    }
    else
    {
        /*std::cout<<root["name"].asString()<<std::endl;
        for (int i = 0; i < root["ins"].size();i++)
        {
            std::cout<<root["ins"][i].asString()<<" ";
            // add input var
            //varList[root["ins"][i].asString()] = NULL;
        }
        std::cout<<std::endl;
        for (int i = 0; i < root["outs"].size();i++)
        {
            std::cout<<root["outs"][i].asString()<<" ";
            // add output var
            //varList[root["outs"][i].asString()] = NULL;
        }
        std::cout<<std::endl;
        std::cout<<root["data_type"].asString()<<std::endl;*/
        if(root["data_type"].asString()[0] == 'i')
            data_type = Type::int_scalar(32);
        else
            data_type = Type::float_scalar(32);
        //std::cout<<root["kernel"].asString()<<std::endl;

        std::string kernel = root["kernel"].asString();
        kernel = format(kernel);
        //std::cout<<kernel<<std::endl;
        //std::cout<<std::endl<<"----------------------"<<std::endl;
        parseKernel(kernel);
    }
}
int main() 
{
    //std::cout<<"Begin!"<<std::endl;
    for(int i = 1; i <= 10; i++)
    {
        std::string inputfilename = (std::string)"./cases/case" + std::to_string(i) + (std::string)".json";
        std::ifstream ifile(inputfilename);
        if (!ifile.is_open())
        {
            std::cout<<"failed to open case " + std::to_string(i)<<std::endl;
            continue;
        }
        else 
        {
            std::cout<<"open case " + std::to_string(i)<<std::endl;
        }
        parse(ifile);
        ifile.close();
    }
    return 0;
}
