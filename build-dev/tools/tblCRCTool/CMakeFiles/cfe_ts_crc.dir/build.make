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

# Include any dependencies generated for this target.
include tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/depend.make

# Include the progress variables for this target.
include tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/progress.make

# Include the compile flags for this target's objects.
include tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/flags.make

tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.o: tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/flags.make
tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.o: /cfs/tools/tblCRCTool/cfe_ts_crc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cfs/build-dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.o"
	cd /cfs/build-dev/tools/tblCRCTool && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.o   -c /cfs/tools/tblCRCTool/cfe_ts_crc.c

tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.i"
	cd /cfs/build-dev/tools/tblCRCTool && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cfs/tools/tblCRCTool/cfe_ts_crc.c > CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.i

tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.s"
	cd /cfs/build-dev/tools/tblCRCTool && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cfs/tools/tblCRCTool/cfe_ts_crc.c -o CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.s

# Object files for target cfe_ts_crc
cfe_ts_crc_OBJECTS = \
"CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.o"

# External object files for target cfe_ts_crc
cfe_ts_crc_EXTERNAL_OBJECTS =

tools/tblCRCTool/cfe_ts_crc: tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/cfe_ts_crc.c.o
tools/tblCRCTool/cfe_ts_crc: tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/build.make
tools/tblCRCTool/cfe_ts_crc: tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cfs/build-dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cfe_ts_crc"
	cd /cfs/build-dev/tools/tblCRCTool && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cfe_ts_crc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/build: tools/tblCRCTool/cfe_ts_crc

.PHONY : tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/build

tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/clean:
	cd /cfs/build-dev/tools/tblCRCTool && $(CMAKE_COMMAND) -P CMakeFiles/cfe_ts_crc.dir/cmake_clean.cmake
.PHONY : tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/clean

tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/depend:
	cd /cfs/build-dev && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cfs/cfe /cfs/tools/tblCRCTool /cfs/build-dev /cfs/build-dev/tools/tblCRCTool /cfs/build-dev/tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/tblCRCTool/CMakeFiles/cfe_ts_crc.dir/depend

