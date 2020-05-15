cmake_minimum_required(VERSION 3.5)

project(repositories)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -I /usr/include/postgresql -L /usr/lib/postgresql/9.5/lib/ -lpq")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    include/repositories_header.hpp
    include/abstract_repository.hpp
    include/profile_repository.hpp
    include/subscription_repository.hpp
    include/tag_repository.hpp
    include/tweet_repository.hpp
    include/user_repository.hpp
    include/vote_repository.hpp
        include/news_feed_repository.hpp
)

set(SRC
    source/profile_repository.cpp
    source/subscription_repository.cpp
    source/tag_repository.cpp
    source/tweet_repository.cpp
    source/user_repository.cpp
    source/vote_repository.cpp
        source/news_feed_repository.cpp
)

add_library(repositories STATIC
    ${SRC})

target_include_directories(repositories
    PUBLIC
        "include"
        "../models/include"
        "../data_base/include"
)
