cmake_minimum_required(VERSION 2.8.12)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../include)

if(MINGW)
    add_definitions("-D_USE_MATH_DEFINES") # For M_PI
endif()

if(MSVC)
    add_definitions("-std=c++11 -WX -W2")
    add_definitions("-D_USE_MATH_DEFINES") # For M_PI
else()
    add_definitions("-std=c++11 -Wall -Wextra")
endif()

find_package(MAVSDK REQUIRED)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTrajectoryTests trajectory_tests.cpp)
target_link_libraries(runTrajectoryTests ${GTEST_LIBRARIES} pthread
TrajectoryLib
MAVSDK::mavsdk_offboard
MAVSDK::mavsdk_telemetry
MAVSDK::mavsdk)