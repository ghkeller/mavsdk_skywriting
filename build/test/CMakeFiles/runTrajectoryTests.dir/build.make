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
include test/CMakeFiles/runTrajectoryTests.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/runTrajectoryTests.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/runTrajectoryTests.dir/flags.make

test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o: test/CMakeFiles/runTrajectoryTests.dir/flags.make
test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o: ../test/trajectory_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o"
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o -c /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/test/trajectory_tests.cpp

test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.i"
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/test/trajectory_tests.cpp > CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.i

test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.s"
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/test/trajectory_tests.cpp -o CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.s

test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o.requires:

.PHONY : test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o.requires

test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o.provides: test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/runTrajectoryTests.dir/build.make test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o.provides.build
.PHONY : test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o.provides

test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o.provides.build: test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o


# Object files for target runTrajectoryTests
runTrajectoryTests_OBJECTS = \
"CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o"

# External object files for target runTrajectoryTests
runTrajectoryTests_EXTERNAL_OBJECTS =

test/runTrajectoryTests: test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o
test/runTrajectoryTests: test/CMakeFiles/runTrajectoryTests.dir/build.make
test/runTrajectoryTests: /usr/lib/libgtest.a
test/runTrajectoryTests: src/libTrajectoryLib.a
test/runTrajectoryTests: /usr/local/lib/libmavsdk_offboard.so
test/runTrajectoryTests: /usr/local/lib/libmavsdk_telemetry.so
test/runTrajectoryTests: /usr/local/lib/libmavsdk.so
test/runTrajectoryTests: test/CMakeFiles/runTrajectoryTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable runTrajectoryTests"
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runTrajectoryTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/runTrajectoryTests.dir/build: test/runTrajectoryTests

.PHONY : test/CMakeFiles/runTrajectoryTests.dir/build

test/CMakeFiles/runTrajectoryTests.dir/requires: test/CMakeFiles/runTrajectoryTests.dir/trajectory_tests.cpp.o.requires

.PHONY : test/CMakeFiles/runTrajectoryTests.dir/requires

test/CMakeFiles/runTrajectoryTests.dir/clean:
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/test && $(CMAKE_COMMAND) -P CMakeFiles/runTrajectoryTests.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/runTrajectoryTests.dir/clean

test/CMakeFiles/runTrajectoryTests.dir/depend:
	cd /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/test /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/test /home/gordon/Documents/gitrepos/MAVSDK/example/offboard_skywriting_mode/build/test/CMakeFiles/runTrajectoryTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/runTrajectoryTests.dir/depend

