cmake_minimum_required(VERSION 3.5)

project(data_base)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -I /usr/include/postgresql/")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(INC
    include/DBConnection.hpp
    include/DBController.hpp
)

set(SRC
    source/DBConnection.cpp
    source/DBController.cpp
)

if(APPLE)
    find_package(PostgreSQL REQUIRED)
    target_include_directories(data_base PRIVATE ${PostgreSQL_INCUDE_DIRS})
    target_link_libraries(data_base PRIVATE ${PostgreSQL_LIBRARIES})
endif()

add_library(data_base SHARED
    ${SRC})

target_include_directories(data_base
    PUBLIC
        "include"
)
