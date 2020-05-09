cmake_minimum_required(VERSION 3.5)

project(server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    include/server.hpp
)

set(SRC
    source/server.cpp
)

add_library(server SHARED
    ${SRC})

target_include_directories(server
    PUBLIC
        "include"
)
