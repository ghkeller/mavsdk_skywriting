cmake_minimum_required(VERSION 2.8.12)

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

include_directories(../include)

add_library(LetterWaypointLib STATIC
    LetterWaypoint.cpp)


target_link_libraries(LetterWaypointLib
    MAVSDK::mavsdk_offboard
    MAVSDK::mavsdk
)

add_library(MissionVectorLib STATIC
    MissionVector.cpp)


target_link_libraries(MissionVectorLib
    LetterWaypointLib

    MAVSDK::mavsdk_action
    MAVSDK::mavsdk_telemetry
    MAVSDK::mavsdk_offboard
    MAVSDK::mavsdk
)

add_library(TrajectoryLib STATIC
    Trajectory.cpp)

target_link_libraries(TrajectoryLib

    MAVSDK::mavsdk_offboard
    MAVSDK::mavsdk_telemetry
)
