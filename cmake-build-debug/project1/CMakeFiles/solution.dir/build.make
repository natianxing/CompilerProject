# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug

# Include any dependencies generated for this target.
include project1/CMakeFiles/solution.dir/depend.make

# Include the progress variables for this target.
include project1/CMakeFiles/solution.dir/progress.make

# Include the compile flags for this target's objects.
include project1/CMakeFiles/solution.dir/flags.make

project1/CMakeFiles/solution.dir/solution/solution.cc.obj: project1/CMakeFiles/solution.dir/flags.make
project1/CMakeFiles/solution.dir/solution/solution.cc.obj: project1/CMakeFiles/solution.dir/includes_CXX.rsp
project1/CMakeFiles/solution.dir/solution/solution.cc.obj: ../project1/solution/solution.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object project1/CMakeFiles/solution.dir/solution/solution.cc.obj"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\project1 && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\solution.dir\solution\solution.cc.obj -c C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\project1\solution\solution.cc

project1/CMakeFiles/solution.dir/solution/solution.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/solution/solution.cc.i"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\project1 && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\project1\solution\solution.cc > CMakeFiles\solution.dir\solution\solution.cc.i

project1/CMakeFiles/solution.dir/solution/solution.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/solution/solution.cc.s"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\project1 && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\project1\solution\solution.cc -o CMakeFiles\solution.dir\solution\solution.cc.s

# Object files for target solution
solution_OBJECTS = \
"CMakeFiles/solution.dir/solution/solution.cc.obj"

# External object files for target solution
solution_EXTERNAL_OBJECTS =

project1/solution.exe: project1/CMakeFiles/solution.dir/solution/solution.cc.obj
project1/solution.exe: project1/CMakeFiles/solution.dir/build.make
project1/solution.exe: libboost.dll.a
project1/solution.exe: lib/libjsoncpp.a
project1/solution.exe: project1/CMakeFiles/solution.dir/linklibs.rsp
project1/solution.exe: project1/CMakeFiles/solution.dir/objects1.rsp
project1/solution.exe: project1/CMakeFiles/solution.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable solution.exe"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\project1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\solution.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project1/CMakeFiles/solution.dir/build: project1/solution.exe

.PHONY : project1/CMakeFiles/solution.dir/build

project1/CMakeFiles/solution.dir/clean:
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\project1 && $(CMAKE_COMMAND) -P CMakeFiles\solution.dir\cmake_clean.cmake
.PHONY : project1/CMakeFiles/solution.dir/clean

project1/CMakeFiles/solution.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\project1 C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\project1 C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\project1\CMakeFiles\solution.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : project1/CMakeFiles/solution.dir/depend

