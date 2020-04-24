cmake_minimum_required(VERSION 3.8)

project(data_base)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    include/DBConnection.hpp
    include/DBController.hpp
)

set(SRC
    source/DBConnection.cpp
    source/DBController.cpp
)

add_library(data_base SHARED
    ${SRC})

target_include_directories(data_base
    PUBLIC
        "include"
)
