cmake_minimum_required(VERSION 3.8)

project(unit_of_work)

#set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
#set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
#set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

set(INC
    include/unit_of_work.hpp
)

set(SRC
    source/unit_of_work.cpp
)

add_library(unit_of_work SHARED
    ${SRC})

target_include_directories(unit_of_work
    PUBLIC
        "include"
)


