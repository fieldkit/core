cmake_minimum_required(VERSION 3.5)
project(core)

set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})

add_subdirectory(firmware/test)
add_subdirectory(firmware/core)
