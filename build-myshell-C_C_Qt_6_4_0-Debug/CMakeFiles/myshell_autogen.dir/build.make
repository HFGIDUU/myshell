# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/mkbk/myshell/myshell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/mkbk/myshell/build-myshell-C_C_Qt_6_4_0-Debug

# Utility rule file for myshell_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/myshell_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/myshell_autogen.dir/progress.make

CMakeFiles/myshell_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/mkbk/myshell/build-myshell-C_C_Qt_6_4_0-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target myshell"
	/usr/bin/cmake -E cmake_autogen /root/mkbk/myshell/build-myshell-C_C_Qt_6_4_0-Debug/CMakeFiles/myshell_autogen.dir/AutogenInfo.json Debug

myshell_autogen: CMakeFiles/myshell_autogen
myshell_autogen: CMakeFiles/myshell_autogen.dir/build.make
.PHONY : myshell_autogen

# Rule to build all files generated by this target.
CMakeFiles/myshell_autogen.dir/build: myshell_autogen
.PHONY : CMakeFiles/myshell_autogen.dir/build

CMakeFiles/myshell_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myshell_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myshell_autogen.dir/clean

CMakeFiles/myshell_autogen.dir/depend:
	cd /root/mkbk/myshell/build-myshell-C_C_Qt_6_4_0-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/mkbk/myshell/myshell /root/mkbk/myshell/myshell /root/mkbk/myshell/build-myshell-C_C_Qt_6_4_0-Debug /root/mkbk/myshell/build-myshell-C_C_Qt_6_4_0-Debug /root/mkbk/myshell/build-myshell-C_C_Qt_6_4_0-Debug/CMakeFiles/myshell_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myshell_autogen.dir/depend

