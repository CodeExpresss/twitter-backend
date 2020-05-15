cmake_minimum_required(VERSION 3.5)

project(models)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    include/models_header.hpp
    include/profile.hpp
    include/subscription.hpp
    include/tag.hpp
    include/tweet.hpp
    include/user.hpp
    include/vote.hpp
)

set(SRC
   source/profile.cpp
   source/subscription.cpp
   source/tag.cpp
   source/tweet.cpp
   source/user.cpp
   source/vote.cpp
)

add_library(models STATIC
    ${SRC})

target_include_directories(models
    PUBLIC
        "include"
)
