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
include jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/depend.make

# Include the progress variables for this target.
include jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/progress.make

# Include the compile flags for this target's objects.
include jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/flags.make

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/flags.make
jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/includes_CXX.rsp
jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj: ../3rdparty/jsoncpp/src/lib_json/json_reader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\jsoncpp_lib.dir\json_reader.cpp.obj -c C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\3rdparty\jsoncpp\src\lib_json\json_reader.cpp

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.i"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\3rdparty\jsoncpp\src\lib_json\json_reader.cpp > CMakeFiles\jsoncpp_lib.dir\json_reader.cpp.i

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.s"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\3rdparty\jsoncpp\src\lib_json\json_reader.cpp -o CMakeFiles\jsoncpp_lib.dir\json_reader.cpp.s

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/flags.make
jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/includes_CXX.rsp
jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj: ../3rdparty/jsoncpp/src/lib_json/json_value.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\jsoncpp_lib.dir\json_value.cpp.obj -c C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\3rdparty\jsoncpp\src\lib_json\json_value.cpp

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib.dir/json_value.cpp.i"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\3rdparty\jsoncpp\src\lib_json\json_value.cpp > CMakeFiles\jsoncpp_lib.dir\json_value.cpp.i

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib.dir/json_value.cpp.s"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\3rdparty\jsoncpp\src\lib_json\json_value.cpp -o CMakeFiles\jsoncpp_lib.dir\json_value.cpp.s

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/flags.make
jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/includes_CXX.rsp
jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj: ../3rdparty/jsoncpp/src/lib_json/json_writer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\jsoncpp_lib.dir\json_writer.cpp.obj -c C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\3rdparty\jsoncpp\src\lib_json\json_writer.cpp

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.i"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\3rdparty\jsoncpp\src\lib_json\json_writer.cpp > CMakeFiles\jsoncpp_lib.dir\json_writer.cpp.i

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.s"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\3rdparty\jsoncpp\src\lib_json\json_writer.cpp -o CMakeFiles\jsoncpp_lib.dir\json_writer.cpp.s

# Object files for target jsoncpp_lib
jsoncpp_lib_OBJECTS = \
"CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj" \
"CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj" \
"CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj"

# External object files for target jsoncpp_lib
jsoncpp_lib_EXTERNAL_OBJECTS =

lib/libjsoncpp.a: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_reader.cpp.obj
lib/libjsoncpp.a: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_value.cpp.obj
lib/libjsoncpp.a: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/json_writer.cpp.obj
lib/libjsoncpp.a: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/build.make
lib/libjsoncpp.a: jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ..\..\..\lib\libjsoncpp.a"
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && $(CMAKE_COMMAND) -P CMakeFiles\jsoncpp_lib.dir\cmake_clean_target.cmake
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\jsoncpp_lib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/build: lib/libjsoncpp.a

.PHONY : jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/build

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/clean:
	cd /d C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json && $(CMAKE_COMMAND) -P CMakeFiles\jsoncpp_lib.dir\cmake_clean.cmake
.PHONY : jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/clean

jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\3rdparty\jsoncpp\src\lib_json C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json C:\Users\luoyuchu\Desktop\Currrent_Semester\CompilerProject-2020Spring\cmake-build-debug\jsoncpp-build\src\lib_json\CMakeFiles\jsoncpp_lib.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : jsoncpp-build/src/lib_json/CMakeFiles/jsoncpp_lib.dir/depend

