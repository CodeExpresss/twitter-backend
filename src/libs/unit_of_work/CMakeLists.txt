cmake_minimum_required(VERSION 3.8)

project(unit_of_work)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(Boost COMPONENTS property_tree REQUIRED)

set(INC
    include/unit_of_work_header.hpp
    include/unit_of_work.hpp
)

set(SRC
    source/unit_of_work.cpp
)
#add_library(boost INTERFACE IMPORTED)

#set_property(TARGET boost PROPERTY
    #INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

add_library(unit_of_work SHARED
    ${SRC})

target_include_directories(unit_of_work
    PUBLIC
        "include"
        "../models/include"
        "../repositories/include"
)

#target_link_libraries(${PROJECT_NAME} PRIVATE Boost)
