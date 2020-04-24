cmake_minimum_required(VERSION 3.8)

project(controllers)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    include/create_tweet_controller.hpp
    include/get_profile_controller.hpp
    include/index_controller.hpp
    include/login_controller.hpp
    include/logout_controller.hpp
    include/profile_controller.hpp
    include/signup_controller.hpp
    include/subscription_controller.hpp
    include/tags_controller.hpp
    include/tweet_like_controller.hpp
    include/update_profile_controller.hpp
    include/update_user_controller.hpp
    include/user_controller.hpp
    include/vote_controller.hpp
)

set(SRC
    source/create_tweet_controller.cpp
    source/get_profile_controller.cpp
    source/index_controller.cpp
    source/login_controller.cpp
    source/logout_controller.cpp
    source/profile_controller.cpp
    source/signup_controller.cpp
    source/subscription_controller.cpp
    source/tags_controller.cpp
    source/tweet_like_controller.cpp
    source/update_profile_controller.cpp
    source/update_user_controller.cpp
    source/user_controller.cpp
    source/vote_controller.cpp
)

add_library(controllers SHARED
    ${SRC})

target_include_directories(controllers
    PUBLIC
        "include"
)
