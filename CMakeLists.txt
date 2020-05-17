cmake_minimum_required(VERSION 2.8.3)
project(ADT)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)
set(CMAKE_BUILD_TYPE Debug)

include_directories(src)

add_subdirectory(test)