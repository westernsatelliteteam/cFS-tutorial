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

# Utility rule file for native_default_cpu1-install.

# Include the progress variables for this target.
include CMakeFiles/native_default_cpu1-install.dir/progress.make

CMakeFiles/native_default_cpu1-install:
	cd /cfs/build-dev/native/default_cpu1 && $(MAKE) install

native_default_cpu1-install: CMakeFiles/native_default_cpu1-install
native_default_cpu1-install: CMakeFiles/native_default_cpu1-install.dir/build.make

.PHONY : native_default_cpu1-install

# Rule to build all files generated by this target.
CMakeFiles/native_default_cpu1-install.dir/build: native_default_cpu1-install

.PHONY : CMakeFiles/native_default_cpu1-install.dir/build

CMakeFiles/native_default_cpu1-install.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/native_default_cpu1-install.dir/cmake_clean.cmake
.PHONY : CMakeFiles/native_default_cpu1-install.dir/clean

CMakeFiles/native_default_cpu1-install.dir/depend:
	cd /cfs/build-dev && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cfs/cfe /cfs/cfe /cfs/build-dev /cfs/build-dev /cfs/build-dev/CMakeFiles/native_default_cpu1-install.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/native_default_cpu1-install.dir/depend
