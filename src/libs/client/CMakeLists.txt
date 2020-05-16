cmake_minimum_required(VERSION 3.5)

project(client)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -I /usr/include/postgresql/ -lpq")


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    include/client.hpp
)

set(SRC
    source/client.cpp
)

add_library(client STATIC
    ${SRC})

target_include_directories(client
    PUBLIC
        "include"
        "../controllers/include"
        "../unit_of_work/include"
        "../serialize/include"
        "../models/include"
        "../repositories/include"
)
