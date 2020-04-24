cmake_minimum_required(VERSION 3.8)

project(app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC
    source/main.cpp)

add_executable(app
    ${SRC})

target_link_libraries(app
    client
    controllers
    data_base
    models
    repositories
    server
    unit_of_work)

target_include_directories(app
    PUBLIC
        "../libs/client/include"
        "../libs/controllers/include"
        "../libs/data_base/include"
        "../libs/models/include"
        "../libs/repositories/include"
        "../libs/server/include"
        "../libs/unit_of_work/include"
)
