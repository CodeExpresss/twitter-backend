cmake_minimum_required(VERSION 3.8)

project(serialize)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    "include/serialize.hpp"
)

set(SRC
    "source/serialize.cpp"
)

add_library(serialize STATIC
    ${SRC})

target_include_directories(serialize
    PUBLIC
        "include"
        "../models/include"
)
