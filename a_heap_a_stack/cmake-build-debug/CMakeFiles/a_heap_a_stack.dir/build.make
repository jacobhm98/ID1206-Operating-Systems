# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/a_heap_a_stack.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a_heap_a_stack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a_heap_a_stack.dir/flags.make

CMakeFiles/a_heap_a_stack.dir/stack.c.o: CMakeFiles/a_heap_a_stack.dir/flags.make
CMakeFiles/a_heap_a_stack.dir/stack.c.o: ../stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/a_heap_a_stack.dir/stack.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/a_heap_a_stack.dir/stack.c.o   -c /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack/stack.c

CMakeFiles/a_heap_a_stack.dir/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/a_heap_a_stack.dir/stack.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack/stack.c > CMakeFiles/a_heap_a_stack.dir/stack.c.i

CMakeFiles/a_heap_a_stack.dir/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/a_heap_a_stack.dir/stack.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack/stack.c -o CMakeFiles/a_heap_a_stack.dir/stack.c.s

# Object files for target a_heap_a_stack
a_heap_a_stack_OBJECTS = \
"CMakeFiles/a_heap_a_stack.dir/stack.c.o"

# External object files for target a_heap_a_stack
a_heap_a_stack_EXTERNAL_OBJECTS =

a_heap_a_stack: CMakeFiles/a_heap_a_stack.dir/stack.c.o
a_heap_a_stack: CMakeFiles/a_heap_a_stack.dir/build.make
a_heap_a_stack: CMakeFiles/a_heap_a_stack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable a_heap_a_stack"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a_heap_a_stack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a_heap_a_stack.dir/build: a_heap_a_stack

.PHONY : CMakeFiles/a_heap_a_stack.dir/build

CMakeFiles/a_heap_a_stack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a_heap_a_stack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a_heap_a_stack.dir/clean

CMakeFiles/a_heap_a_stack.dir/depend:
	cd /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack/cmake-build-debug /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack/cmake-build-debug /Users/jacobmalm/Documents/KTH/bachelors/ID1206-Operating_Systems/a_heap_a_stack/cmake-build-debug/CMakeFiles/a_heap_a_stack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/a_heap_a_stack.dir/depend

