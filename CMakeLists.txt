cmake_minimum_required(VERSION 2.8.12)

project(offboard_skywriting_project)
add_subdirectory(src)
add_subdirectory(test)

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

include_directories(include)

add_executable(offboard_skywriting
    src/offboard_skywriting_main.cpp
)

target_link_libraries(offboard_skywriting
    LetterWaypointLib
    MissionVectorLib
    TrajectoryLib

    MAVSDK::mavsdk_action
    MAVSDK::mavsdk_offboard
    MAVSDK::mavsdk_telemetry
    MAVSDK::mavsdk
)
