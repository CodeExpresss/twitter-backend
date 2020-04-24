cmake_minimum_required(VERSION 3.8)

project(app)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(src/libs/client)
add_subdirectory(src/libs/controllers)
add_subdirectory(src/libs/data_base)
add_subdirectory(src/libs/models)
add_subdirectory(src/libs/repositories)
add_subdirectory(src/libs/server)
add_subdirectory(src/libs/unit_of_work)

add_subdirectory(src/test)
