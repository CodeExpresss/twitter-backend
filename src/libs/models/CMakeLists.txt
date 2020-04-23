cmake_minimum_required(VERSION 3.8)

project(models)

#set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
#set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
#set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

set(INC
    include/profile.hpp
    include/subscription.hpp
    include/tag.hpp
    include/tweet.hpp
    include/user.hpp
    include/vote.hpp
)

set(SRC
   source/profile.cpp
   source/subscription.cpp
   source/tag.cpp
   source/tweet.cpp
   source/user.cpp
   source/vote.cpp
)

#add_executable(my_gmock
    #${INC}
    #source/test.cpp
    #${SRC})
#enable_testing()
#add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gtest)
#add_definitions(-fprofile-arcs -ftest-coverage)
#target_link_libraries(my_gmock -fprofile-arcs)

add_library(models SHARED
    ${SRC})

target_include_directories(models
    PUBLIC
        "include"
)

#target_link_libraries(my_gmock ${GTEST_LIBRARIES} pthread)
#target_link_libraries(tests_gtest study_std_lib)
#target_link_libraries(my_gmock -lgmock)
