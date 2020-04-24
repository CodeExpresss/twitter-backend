cmake_minimum_required(VERSION 3.8)

project(repositories)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
   include/profile_repository.hpp
   include/subscription_repository.hpp
   include/tag_repository.hpp
   include/tweet_repository.hpp
   include/user_repository.hpp
   include/vote_repository.hpp
)

set(SRC
   source/profile_repository.cpp
   source/subscription_repository.cpp
   source/tag_repository.cpp
   source/tweet_repository.cpp
   source/user_repository.cpp
   source/vote_repository.cpp
)

add_library(repositories SHARED
    ${SRC})

target_include_directories(repositories
    PUBLIC
        "include"
)
