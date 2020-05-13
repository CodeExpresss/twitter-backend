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
    client
    controllers
    data_base
    models
    repositories
    server
    unit_of_work)

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

#add_executable(tests_gmock_repositories source/repositories_gmock.cpp)
#target_link_libraries(tests_gmock_repositories -lpq  -fprofile-arcs)

#target_link_libraries(tests_gmock_repositories
    #data_base
    #models
#)

#target_include_directories(tests_gmock_repositories
    #PUBLIC
        #"include"
        #"../libs/repositories/include"
        #"../libs/unit_of_work/include"
        #"../libs/models/include"
        #"../libs/data_base/include"
#)

#target_link_libraries(tests_gmock_repositories ${GTEST_LIBRARIES} pthread -lgmock)


#add_executable(tests_gmock_database source/test_database.cpp)
#target_link_libraries(tests_gmock_database -lpq  -fprofile-arcs)

#target_link_libraries(tests_gmock_database
    #data_base
    #models
    #repositories)

#target_include_directories(tests_gmock_database
    #PUBLIC
        #"../libs/data_base/include"
        #"../libs/models/include"
        #"../libs/repositories/include"
#)

#target_link_libraries(tests_gmock_database ${GTEST_LIBRARIES} pthread -lgmock)

#add_executable(tests_gmock_unit_of_work source/unit_of_work_gmock.cpp)
#target_link_libraries(tests_gmock_unit_of_work -lpq  -fprofile-arcs)

#target_link_libraries(tests_gmock_unit_of_work
    #data_base
    #models
#)

#target_include_directories(tests_gmock_unit_of_work
    #PUBLIC
        #"include"
        #"../libs/repositories/include"
        #"../libs/controllers/include"
        #"../libs/unit_of_work/include"
        #"../libs/models/include"
        #"../libs/data_base/include"
#)

#target_link_libraries(tests_gmock_unit_of_work ${GTEST_LIBRARIES} pthread -lgmock)

#add_executable(tests_gmock_server source/test_server.cpp)
#target_link_libraries(tests_gmock_server -lpq  -fprofile-arcs)

#target_link_libraries(tests_gmock_server
#)

#target_include_directories(tests_gmock_server
    #PUBLIC
        #"include"
        #"../libs/controllers/include"
        #"../libs/client/include"
        #"../libs/repositories/include"
        #"../libs/models/include"
        #"../libs/unit_of_work/include"
#)

#target_link_libraries(tests_gmock_server ${GTEST_LIBRARIES} pthread -lgmock)

add_executable(tests_gmock_server source/test_server_run.cpp)
target_link_libraries(tests_gmock_server -lpq  -fprofile-arcs)

target_link_libraries(tests_gmock_server
)

target_include_directories(tests_gmock_server
    PUBLIC
        "include"
        "../libs/controllers/include"
        "../libs/serialize/include"
        "../libs/client/include"
        "../libs/repositories/include"
        "../libs/models/include"
        "../libs/unit_of_work/include"
)

target_link_libraries(tests_gmock_server ${GTEST_LIBRARIES} pthread -lgmock)


