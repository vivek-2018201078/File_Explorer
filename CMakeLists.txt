cmake_minimum_required(VERSION 3.12)
project(Final)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Final
        file_explorer.cpp
        global_variables.cpp
        global_variables.h
        list_directory.cpp
        list_directory.h
        raw_input.cpp
        raw_input.h)
