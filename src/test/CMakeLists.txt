cmake_minimum_required(VERSION 3.5)

project(tests_gmock)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS " -g -O0 -Wall -fprofile-arcs -ftest-coverage -I /usr/include/postgresql/ -lpq -lpthread")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SRC
    source/main.cpp)
    #source/repositories_gmock.cpp)
    #source/unit_of_work_gmock.cpp)

add_executable(tests_gmock
    ${SRC})

enable_testing()
add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gtest)
add_definitions(-fprofile-arcs -ftest-coverage)
target_link_libraries(tests_gmock -fprofile-arcs)

target_link_libraries(tests_gmock
    models
    data_base
    repositories
    unit_of_work
    client
    controllers
    server
)

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

target_link_libraries(tests_gmock ${GTEST_LIBRARIES} pthread)
target_link_libraries(tests_gmock -lgmock)

add_executable(test_news_feed source/test_news_feed.cpp)
target_link_libraries(test_news_feed -fprofile-arcs -lpq)

target_link_libraries(test_news_feed
    models
    data_base
    repositories
    unit_of_work
    client
    controllers
    server
)

target_include_directories(test_news_feed
        PUBLIC
        "include"
        "../libs/controllers/include"
        "../libs/serialize/include"
        "../libs/client/include"
        "../libs/repositories/include"
        "../libs/models/include"
        "../libs/unit_of_work/include"
        "../libs/server/include"
        )

target_link_libraries(test_news_feed ${GTEST_LIBRARIES} pthread -lgmock)

add_executable(test_session source/session_feature_test.cpp)
target_link_libraries(test_session -fprofile-arcs -lpq)

target_link_libraries(test_session
        models
        client
        controllers
        data_base
        repositories
        server
        unit_of_work
        )

target_include_directories(test_session
        PUBLIC
        "include"
        "../libs/models/include"
        "../libs/repositories/include"
        "../libs/unit_of_work/include"
        "../libs/controllers/include"
        "../libs/serialize/include"
        "../libs/client/include"
        )

target_link_libraries(test_session ${GTEST_LIBRARIES} pthread -lgmock)
