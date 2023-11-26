cmake_minimum_required(VERSION 2.8.12)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../include )

find_package(MAVSDK REQUIRED)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTrajectoryTests trajectory_tests.cpp)
target_link_libraries(runTrajectoryTests ${GTEST_LIBRARIES} pthread
    skywriting_lib
    MAVSDK::mavsdk
)
