cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(skywriting_project)

find_package(MAVSDK REQUIRED)

add_library(skywriting_lib SHARED
    MissionVector.cpp
    LetterWaypoint.cpp
    Trajectory.cpp
    Primipherals/Primipheral.cpp
    )

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

target_include_directories(skywriting_lib PRIVATE
    ../include  /usr/local/include/mavsdk
    )

target_link_libraries(skywriting_lib
    MAVSDK::mavsdk
    )

#target_include_directories(skywriting_lib PRIVATE
#    ../include ${MAVSDK_INCLUDE_DIRS}
#    )
#
#target_link_libraries(skywriting_lib 
#    MAVSDK::mavsdk
#    MAVSDK::mavsdk_action
#    MAVSDK::mavsdk_telemetry
#    MAVSDK::mavsdk_mission
#    )
#
add_compile_options(skywriting_lib PRIVATE -l/usr/local/include/mavsdk)


