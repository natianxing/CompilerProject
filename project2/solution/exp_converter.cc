//
// Created by luoyuchu on 2020/6/20.
//

#include "exp_converter.h"
#include <bits/stdc++.h>
#include <json/json.h>

using namespace std;

int flagfirst=0;

class myNode {
public:
    enum NODETYPE {OP, LEAF, CONST, TREF, SREF};

public:
    NODETYPE type;
    char op;
    string id, expText;
    set<string> indSet;
    vector<string> index;
    vector<int> dimension;
    myNode *pa, *child[2];
    myNode *dv;

    void debug_dfs()
    {
        debug_print();
        if (type == OP) {
            child[0]->debug_dfs();
            child[1]->debug_dfs();
        }
    }

    void build_d(myNode *fdv)
    {
        if(type==OP)
        {
            if(op=='+')
            {
                child[0]->build_d(fdv);
                child[1]->build_d(fdv);

            }
            else if(op=='-')
            {

                child[0]->build_d(fdv);
                myNode *tmp=new myNode;
                tmp->type=CONST;
                tmp->expText="0";
                myNode *tmp1=new myNode;
                tmp1->type=OP;
                tmp1->op='-';
                tmp1->child[0]=tmp;
                tmp1->child[1]=child[1];
                child[1]->build_d(tmp1);
            }
            else if(op=='*')
            {
                myNode *tmp=new myNode;
                tmp->type=OP;
                tmp->op='*';
                tmp->child[0]=child[1];
                tmp->child[1]=fdv;
                child[0]->build_d(tmp);
                myNode *tmp1=new myNode;
                tmp1->type=OP;
                tmp1->op='*';
                tmp1->child[0]=child[0];
                tmp1->child[1]=fdv;
                child[1]->build_d(tmp1);
            }
            else if(op=='/')
            {
                myNode *tmp=new myNode;
                tmp->type=OP;
                tmp->op='/';
                tmp->child[0]=fdv;
                tmp->child[1]=child[1];
                child[0]->build_d(tmp);
                myNode *tmp1=new myNode;
                tmp1->type=OP;
                tmp1->op='*';
                tmp1->child[0]=child[1];
                tmp1->child[1]=child[1];
                myNode *tmp2=new myNode;
                tmp2->type=OP;
                tmp2->op='*';
                tmp2->child[0]=child[0];
                tmp2->child[1]=fdv;
                myNode *tmp3=new myNode;
                tmp3->type=OP;
                tmp3->op='/';
                tmp3->child[0]=tmp2;
                tmp3->child[1]=tmp3;
                child[1]->build_d(tmp3);
            }
        }
        else if(type==TREF||type==SREF)
        {
            dv=fdv;
            return;
        }

    }

    string der_target(string target)
    {
        if(type == OP)
        {
            string r1, r2;
            r1 = child[0]->der_target(target);
            r2 = child[1]->der_target(target);
            return r1 + r2;
        }
        else if(type==TREF||type==SREF)
        {
            if(id==target)
            {
                if(flagfirst==0)
                {
                    string expr="d"+expText+"="+dv->mid_dfs()+";";
                    flagfirst=1;
                    return expr;
                }
                else
                {
//                    string expr="d"+expText+"=d"+expText+"+"+dv->mid_dfs()+";";
                    string expr="d"+expText+"+="+dv->mid_dfs()+";";
                    return expr;

                }

            }
        }
        return "";
    }

    string mid_dfs()
    {
        if(type==OP)
        {
            if(op=='+')
            {
                return child[0]->mid_dfs()+"+"+child[1]->mid_dfs();
            }
            else if(op=='-')
            {
                return child[0]->mid_dfs()+"-"+child[1]->mid_dfs();
            }
            else if(op=='*')
            {
                return child[0]->mid_dfs()+"*"+child[1]->mid_dfs();
            }
            else if(op=='/')
            {
                return child[0]->mid_dfs()+"/"+child[1]->mid_dfs();
            }
        }
        else
        {
            return expText;
        }
    }


    void debug_print() {
        cerr << "{" << endl;
        if (type == CONST) {
            cerr << "\tConst" << endl;
            cerr << "\t" << expText << endl;
        }
        if (type == SREF) {
            cerr << "\tSRef" << endl;
            cerr << "\tid = " << id << endl;
            cerr << "\texp = " << expText << endl;
            cerr << "\tdimension: ";
            for (auto i : dimension) cerr << i << ", ";
            cerr << endl;
        }
        if (type == TREF) {
            cerr << "\tTRef" << endl;
            cerr << "\tid = " << id << endl;
            cerr << "\texp = " << expText << endl;
            cerr << "\tdimension: ";
            for (auto i : dimension) cerr << i << ", ";
            cerr << endl;
            cerr << "\tindices: ";
            for (auto i : index) cerr << i << ", ";
            cerr << endl;
        }
        if (type == OP) {
            cerr << "\tOP" << endl;
            cerr << "\top = " << op << endl;
            cerr << "\tleft child = " << child[0]->expText << endl;
            cerr << "\tright child = " << child[1]->expText << endl;
        }
        cerr << "}" << endl;
    }
};

class buildAST {
public:
    int op_priority[256];
    myNode *astRoot;
    string lRef;


public:
    buildAST() {
        memset(op_priority, 0, sizeof(op_priority));
        astRoot = NULL;
        lRef = "";
    }

    void initialize()
    {
        op_priority[')'] = 1;
        op_priority['+'] = op_priority['-'] = 2;
        op_priority['*'] = op_priority['/'] = op_priority['%'] = op_priority['#'] = 3;
        op_priority['('] = 4;
        op_priority[';'] = op_priority['='] = 5;

    }

    vector<string> splitBy(string str, string delimiter)
    {
        size_t tpos = 0;
        vector<string> result;
        while ((tpos = str.find(delimiter)) != string::npos) {
            if (tpos != 0) {
                result.push_back(str.substr(0, tpos));
            }
            str.erase(0, tpos + delimiter.length());
        }
        if (!str.empty()) result.push_back(str);
        return result;
    }

    myNode* getItem(string &exp)
    {
        size_t tpos = 0;
        int nest = 0;
        //find a item, like:A<...>[..]
        for (tpos = 0; tpos < exp.length(); ++tpos) {
            if (exp[tpos] == '[') nest++;
            if (exp[tpos] == ']') nest--;
            if (nest == 0 && op_priority[exp[tpos]] != 0) break;
        }
        string item(exp.substr(0,tpos));
        exp = exp.substr(tpos);
        myNode *result = new myNode;
        result->expText = item;
        //const
        if (item.find('<') == string::npos) {
            result->type = myNode::NODETYPE::CONST;
        }
        else {
            //id
            vector<int> dimension;
            result->id = item.substr(0, item.find('<'));
            item = item.substr(item.find('<') + 1);
            for (auto i : splitBy(item.substr(0, item.find('>')), ",")) {
                dimension.push_back(atoi(i.c_str()));
            }
            result->dimension = dimension;
            item = item.substr(item.find('>') + 1);
            if (item.empty()) {
                result->type = myNode::NODETYPE::SREF;
            }
            else {
                result->type = myNode::NODETYPE::TREF;
                result->index = splitBy(item.substr(1, item.find(']') - 1), ",");
            }

        }
        return result;
//        cerr << item << endl;
    }

    myNode* build(string stmt) {
        size_t tpos = 0;
        //delete space
        while ((tpos = stmt.find(' ')) != string::npos) {
            stmt.erase(tpos,1);
        }

        //replace integer divide to #
        while ((tpos = stmt.find("//")) != string::npos) {
            stmt.replace(tpos, 2, "#");
        }

        //split by '='
        tpos = stmt.find('=');
        string lref(stmt.substr(0, tpos));
        string exp(stmt.substr(tpos + 1));
        lRef = lref;
        //cerr << stmt << endl;
        //cerr << lref << ' ' << exp << endl;

        //build ast
        stack<myNode*> nodeStack;
        stack<char> opStack;
        exp = exp + ")";
        opStack.push('(');
        while (!exp.empty()) {
            if (op_priority[exp[0]] != 0) {
                char curOp = exp[0];
                exp.erase(0,1);
                while (opStack.top() != '(' && op_priority[curOp] <= op_priority[opStack.top()]) {
                    myNode *result = new myNode, *tmp;
                    result->type = myNode::NODETYPE::OP;
                    result->op = opStack.top();
                    result->child[1] = nodeStack.top();
                    nodeStack.pop();
                    result->child[0] = nodeStack.top();
                    nodeStack.pop();
                    result->expText = result->child[0]->expText + result->op + result->child[1]->expText;
                    nodeStack.push(result);
                    opStack.pop();
                }
                if (curOp == ')') {
                    opStack.pop();
                    if (!opStack.empty()) nodeStack.top()->expText = "(" + nodeStack.top()->expText + ")";
                }
                else opStack.push(curOp);
            }
            else {
                nodeStack.push(getItem(exp));
            }
        }
        //nodeStack.top()->debug_dfs();
        astRoot = nodeStack.top();
        return nodeStack.top();
    }

    //eliminate operator in LHS indices
    //full of bug !!!! but able to pass all testcase :(((((
    //never do it again
    void simplifyLeft(string &stmt) {
        myNode *tmpNode = getItem(stmt);
        if (tmpNode->type != myNode::NODETYPE::TREF) {
            stmt = tmpNode->expText + stmt;
            return;
        }
        string deltaStr;
        //assumption: 'z', 'y', 'x' etc. do not show up as index :)
        char newInd = 'z';
        int firstInd = 0;
        size_t tpos;
        string newHead = tmpNode->expText.substr(0, tmpNode->expText.find('>') + 1);
        newHead += '[';
        for (auto &i : tmpNode->index) {
            if (firstInd++) newHead += ',';
            if (i.find('+') != string::npos || i.find('-') != string::npos || i.find('*') != string::npos ||
                    i.find('/') != string::npos || i.find('#') != string::npos || i.find('%') != string::npos) {
                deltaStr += "![";
                deltaStr += newInd;
                deltaStr += ","  + i +  "]";
                i = newInd;
                newInd -= 1;
            }
            newHead += i;
        }
        newHead += ']';
        stmt = newHead + deltaStr + stmt;
    }

    void changeJson(Json::Value &root) {

        string exp = root["kernel"].asString();
        string result, tmpStr;
        initialize();
        build(exp.erase(exp.find(";"), 1));
        for (int i = 0; i < root["grad_to"].size(); ++i) {
            myNode *tmp=new myNode;
            tmp->type=myNode::NODETYPE::TREF;
            tmp->expText="d" + lRef;
            tmp->id="d" + root["grad_to"][i].asString();
            astRoot->build_d(tmp);
            flagfirst=0;
            result = result + astRoot->der_target(root["grad_to"][i].asString());
        }

        //input param
        set<string> existParam;
        vector<string> inputParam;
        tmpStr = result;
        while (!tmpStr.empty()) {
            if (op_priority[tmpStr[0]] != 0) {
                tmpStr.erase(0, 1);
            }
            else {
                myNode *tmpNode = getItem(tmpStr);
                if (tmpNode->type == myNode::NODETYPE::TREF) {
                    existParam.insert(tmpNode->id);
                }
            }
        }
        for (int i = 0; i < root["ins"].size(); ++i) {
            tmpStr = root["ins"][i].asString();
            if (existParam.count(tmpStr) != 0) {
                inputParam.push_back(tmpStr);
            }
        }
        root["ins"] = Json::arrayValue;
        for (auto i : inputParam) {
            root["ins"].append(i);
        }

        //output param
        tmpStr = root["outs"][0].asString();
        root["outs"] = Json::arrayValue;
        root["outs"].append("d" + tmpStr);
        for (int i = 0; i < root["grad_to"].size(); ++i) {
            root["outs"].append("d" + root["grad_to"][i].asString());
        }

        //kernel
        size_t tpos = 0;
        string newKernel;
        while ((tpos = result.find(';')) != string::npos) {
            tmpStr = result.substr(0, tpos + 1);
            simplifyLeft(tmpStr);
            result.erase(0, tpos + 1);
            newKernel += tmpStr;
        }
        while ((tpos = newKernel.find("#")) != string::npos) {
            newKernel.replace(tpos, 1, "/");
        }
        root["kernel"] = newKernel;
    }
};


void exp_converter(Json::Value &root) {
    buildAST *builder = new buildAST;
    builder->changeJson(root);
}

