cmake_minimum_required(VERSION 3.15)
project(dthread)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -Wall -lpthread")

add_executable(dthread
        main.cpp
        dthread.h
        dthread.cpp
        ../gtest/gtest-all.cc
        ../gtest/gtest.h
        ../gtest/gtest_main.cc
        )

target_link_libraries(dthread -lpthread)

