cmake_minimum_required(VERSION 3.13)

project(mavsdk_skywriting)
#add_subdirectory(src)
#add_subdirectory(test)

if(MINGW)
    add_definitions("-D_USE_MATH_DEFINES") # For M_PI
endif()

if(MSVC)
    add_definitions("-std=c++11 -WX -W2")
    add_definitions("-D_USE_MATH_DEFINES") # For M_PI
else()
    add_definitions("-std=c++11 -Wall -Wextra")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{HOME}/MAVSDK)

message(CMAKE_MODULE_PATH="${CMAKE_MODULE_PATH}")

find_package(MAVSDK REQUIRED IMPORTED)

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()


include_directories(include ${MAVSDK_DIR}/include)

add_executable(offboard_skywriting
    src/offboard_skywriting_main.cpp
)

target_link_libraries(offboard_skywriting
    LetterWaypointLib
    MissionVectorLib
    TrajectoryLib
    ${MAVSDK_DIR}/install/lib
    #mavsdk::mavsdk
    #mavsdk::plugins

)
