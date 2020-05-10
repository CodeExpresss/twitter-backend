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
)

add_library(controllers SHARED
    ${SRC})

target_include_directories(controllers
    PUBLIC
        "include"
        "../models/include"
)
