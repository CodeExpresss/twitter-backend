cmake_minimum_required(VERSION 3.5)

project(unit_of_work)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    include/unit_of_work_header.hpp
    include/unit_of_work.hpp
)

set(SRC
    source/unit_of_work.cpp
)

add_library(unit_of_work STATIC
    ${SRC})

target_include_directories(unit_of_work
    PUBLIC
        "include"
        "../models/include"
        "../data_base/include"
        "../repositories/include"
)

