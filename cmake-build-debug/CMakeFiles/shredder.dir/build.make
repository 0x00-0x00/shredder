# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/shemhazai/IDE/clion-2016.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/shemhazai/IDE/clion-2016.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/shemhazai/Goldstick/Projects/C/shredder

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/shemhazai/Goldstick/Projects/C/shredder/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/shredder.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shredder.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shredder.dir/flags.make

CMakeFiles/shredder.dir/main.c.o: CMakeFiles/shredder.dir/flags.make
CMakeFiles/shredder.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/shemhazai/Goldstick/Projects/C/shredder/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shredder.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shredder.dir/main.c.o   -c /media/shemhazai/Goldstick/Projects/C/shredder/main.c

CMakeFiles/shredder.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shredder.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/shemhazai/Goldstick/Projects/C/shredder/main.c > CMakeFiles/shredder.dir/main.c.i

CMakeFiles/shredder.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shredder.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/shemhazai/Goldstick/Projects/C/shredder/main.c -o CMakeFiles/shredder.dir/main.c.s

CMakeFiles/shredder.dir/main.c.o.requires:

.PHONY : CMakeFiles/shredder.dir/main.c.o.requires

CMakeFiles/shredder.dir/main.c.o.provides: CMakeFiles/shredder.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/shredder.dir/build.make CMakeFiles/shredder.dir/main.c.o.provides.build
.PHONY : CMakeFiles/shredder.dir/main.c.o.provides

CMakeFiles/shredder.dir/main.c.o.provides.build: CMakeFiles/shredder.dir/main.c.o


# Object files for target shredder
shredder_OBJECTS = \
"CMakeFiles/shredder.dir/main.c.o"

# External object files for target shredder
shredder_EXTERNAL_OBJECTS =

shredder: CMakeFiles/shredder.dir/main.c.o
shredder: CMakeFiles/shredder.dir/build.make
shredder: CMakeFiles/shredder.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/shemhazai/Goldstick/Projects/C/shredder/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable shredder"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shredder.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shredder.dir/build: shredder

.PHONY : CMakeFiles/shredder.dir/build

CMakeFiles/shredder.dir/requires: CMakeFiles/shredder.dir/main.c.o.requires

.PHONY : CMakeFiles/shredder.dir/requires

CMakeFiles/shredder.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shredder.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shredder.dir/clean

CMakeFiles/shredder.dir/depend:
	cd /media/shemhazai/Goldstick/Projects/C/shredder/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/shemhazai/Goldstick/Projects/C/shredder /media/shemhazai/Goldstick/Projects/C/shredder /media/shemhazai/Goldstick/Projects/C/shredder/cmake-build-debug /media/shemhazai/Goldstick/Projects/C/shredder/cmake-build-debug /media/shemhazai/Goldstick/Projects/C/shredder/cmake-build-debug/CMakeFiles/shredder.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shredder.dir/depend

