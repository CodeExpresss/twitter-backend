cmake_minimum_required(VERSION 3.5)

project(controllers)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    include/create_tweet_controller.hpp
    include/follow_controller.hpp
    include/get_profile_controller.hpp
    include/index_controller.hpp
    include/login_controller.hpp
    include/logout_controller.hpp
    include/update_profile_controller.hpp
    include/signup_controller.hpp
    include/subscription_controller.hpp
    include/tags_controller.hpp
    include/tweet_like_controller.hpp
    include/update_user_controller.hpp
    include/get_auth_user_controller.hpp
    include/vote_controller.hpp
)

set(SRC
    source/controller_header.cpp
)

add_library(controllers STATIC
    ${SRC})

target_include_directories(controllers
    PUBLIC
        "include"
        "../models/include"
        "../repositories/include"
        "../unit_of_work/include"
        "../serialize/include"
)
