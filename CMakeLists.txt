cmake_minimum_required(VERSION 3.12)
project(web_cracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lpthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -DDEBUG")


set(REQ_FILES
        ../dthread/dthread.h
        ../dthread/dthread.cpp
        address.h
        address.cpp
        unique_fd.cpp
        unique_fd.h
        ipv4_exception.h
        io_api.cpp
        io_api.h
        socket.cpp
        socket.h
        getaddrinfo_server.cpp
        getaddrinfo_server.h
        timer.cpp
        timer.h
        )

add_executable(server main.cpp
        ${REQ_FILES})

add_executable(test test_main.cpp
        ../gtest/gtest-all.cc
        ../gtest/gtest.h
        ../gtest/gtest_main.cc
        ${REQ_FILES})

target_link_libraries(server -lpthread -lncurses)
target_link_libraries(test -lpthread -lncurses)
