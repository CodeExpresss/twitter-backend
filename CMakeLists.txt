cmake_minimum_required(VERSION 3.8)

project(app)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(src/libs/client)
add_subdirectory(src/libs/controllers)
add_subdirectory(src/libs/data_base)
add_subdirectory(src/libs/models)
add_subdirectory(src/libs/repositories)
add_subdirectory(src/libs/server)
add_subdirectory(src/libs/unit_of_work)

add_subdirectory(src/test)

#enable_testing()
#add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gtest)
#add_definitions(-fprofile-arcs -ftest-coverage)
#target_link_libraries(my_gmock -fprofile-arcs)

set(SRC
    src/test/source/main.cpp)

add_executable(tests
    ${SRC})

target_include_directories(test
    PUBLIC
        "src/libs/client/include"
        "src/libs/controllers/include"
        "src/libs/data_base/include"
        "src/libs/models/include"
        "src/libs/repositories/include"
        "src/libs/server/include"
        "src/libs/unit_of_work/include"
)

target_link_libraries(tests
    client
    controllers
    data_base
    models
    repositories
    server
    unit_of_work
)

#target_link_libraries(test ${GTEST_LIBRARIES} pthread)
#target_link_libraries(tests_gtest study_std_lib)
#target_link_libraries(test -lgmock)
