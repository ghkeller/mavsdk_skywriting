# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build

# Include any dependencies generated for this target.
include src/CMakeFiles/MissionVectorLib.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/MissionVectorLib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/MissionVectorLib.dir/flags.make

src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o: src/CMakeFiles/MissionVectorLib.dir/flags.make
src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o: ../src/MissionVector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o"
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o -c /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/src/MissionVector.cpp

src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.i"
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/src/MissionVector.cpp > CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.i

src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.s"
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/src/MissionVector.cpp -o CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.s

src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o.requires:

.PHONY : src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o.requires

src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o.provides: src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/MissionVectorLib.dir/build.make src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o.provides.build
.PHONY : src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o.provides

src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o.provides.build: src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o


# Object files for target MissionVectorLib
MissionVectorLib_OBJECTS = \
"CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o"

# External object files for target MissionVectorLib
MissionVectorLib_EXTERNAL_OBJECTS =

src/libMissionVectorLib.a: src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o
src/libMissionVectorLib.a: src/CMakeFiles/MissionVectorLib.dir/build.make
src/libMissionVectorLib.a: src/CMakeFiles/MissionVectorLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libMissionVectorLib.a"
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/src && $(CMAKE_COMMAND) -P CMakeFiles/MissionVectorLib.dir/cmake_clean_target.cmake
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MissionVectorLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/MissionVectorLib.dir/build: src/libMissionVectorLib.a

.PHONY : src/CMakeFiles/MissionVectorLib.dir/build

src/CMakeFiles/MissionVectorLib.dir/requires: src/CMakeFiles/MissionVectorLib.dir/MissionVector.cpp.o.requires

.PHONY : src/CMakeFiles/MissionVectorLib.dir/requires

src/CMakeFiles/MissionVectorLib.dir/clean:
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/src && $(CMAKE_COMMAND) -P CMakeFiles/MissionVectorLib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/MissionVectorLib.dir/clean

src/CMakeFiles/MissionVectorLib.dir/depend:
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/src /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/src /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/src/CMakeFiles/MissionVectorLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/MissionVectorLib.dir/depend

