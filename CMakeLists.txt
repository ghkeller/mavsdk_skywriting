cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(skywriting_project)
add_subdirectory(lib)

find_package(MAVSDK REQUIRED)

add_executable(skywriting
    src/skywriting.cpp
    )

target_include_directories(skywriting PRIVATE
    include /usr/local/include/mavsdk
    )

target_link_libraries(skywriting
    MAVSDK::mavsdk
    skywriting_lib
)

if(NOT MSVC)
    add_compile_options(skywriting PRIVATE -Wall -Wextra -l/usr/local/include/mavsdk)
else()
    add_compile_options(skywriting PRIVATE -WX -W2)
endif()

if(MINGW OR MSVC)
    # For M_PI
    add_target_definitions(skywriting "-D_USE_MATH_DEFINES")
endif()
