# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cfs/cfe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cfs/build-dev

# Utility rule file for cfe-usersguide.

# Include the progress variables for this target.
include CMakeFiles/cfe-usersguide.dir/progress.make

CMakeFiles/cfe-usersguide:
	cd /cfs/build-dev/doc && doxygen cfe-usersguide.doxyfile

cfe-usersguide: CMakeFiles/cfe-usersguide
cfe-usersguide: CMakeFiles/cfe-usersguide.dir/build.make

.PHONY : cfe-usersguide

# Rule to build all files generated by this target.
CMakeFiles/cfe-usersguide.dir/build: cfe-usersguide

.PHONY : CMakeFiles/cfe-usersguide.dir/build

CMakeFiles/cfe-usersguide.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cfe-usersguide.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cfe-usersguide.dir/clean

CMakeFiles/cfe-usersguide.dir/depend:
	cd /cfs/build-dev && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cfs/cfe /cfs/cfe /cfs/build-dev /cfs/build-dev /cfs/build-dev/CMakeFiles/cfe-usersguide.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cfe-usersguide.dir/depend

