cmake_minimum_required(VERSION 3.8)

project(tests_gmock)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

#add_subdirectory(../libs/client)
#add_subdirectory(../libs/controllers)
#add_subdirectory(../libs/data_base)
#add_subdirectory(../libs/models)
#add_subdirectory(../libs/repositories)
#add_subdirectory(../libs/server)
#add_subdirectory(../libs/unit_of_work)

set(SRC
    source/main.cpp)

add_executable(tests_gmock
    ${SRC})

#enable_testing()
#add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gtest)
#add_definitions(-fprofile-arcs -ftest-coverage)
#target_link_libraries(test -fprofile-arcs)

target_link_libraries(tests_gmock
    client
    controllers
    data_base
    models
    repositories
    server
    unit_of_worck)

target_include_directories(tests_gmock
    PUBLIC
        "../libs/client/include"
        "../libs/controllers/include"
        "../libs/data_base/include"
        "../libs/models/include"
        "../libs/repositories/include"
        "../libs/server/include"
        "../libs/unit_of_work/include"
)

#target_link_libraries(tests_gmock ${GTEST_LIBRARIES} pthread)
#target_link_libraries(tests_gtest study_std_lib)
#target_link_libraries(tests_gmock -lgmock)
