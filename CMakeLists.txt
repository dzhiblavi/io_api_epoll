cmake_minimum_required(VERSION 3.12)
project(web_cracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lpthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -DDEBUG")

set(REQ_FILES
        dthread/dthread.h
        dthread/dthread.cpp
        getaddrinfo_server.cpp
        getaddrinfo_server.h
        src/address.h
        src/address.cpp
        src/io_api.cpp
        src/io_api.h
        src/ipv4_error.h
        src/socket.cpp
        src/socket.h
        src/timer.h
        src/timer.cpp
        src/unique_fd.h
        src/poll.h
        src/poll.cpp)

add_executable(server main.cpp
        ${REQ_FILES})

add_executable(test test_main.cpp
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc
        ${REQ_FILES})

if (WIN32)
    target_link_libraries(server -lpthread Ws2_32 Mswsock AdvApi32)
    target_link_libraries(test -lpthread Ws2_32 Mswsock AdvApi32)
endif (WIN32)

if (UNIX)
    target_link_libraries(server -lpthread)
    target_link_libraries(test -lpthread)
endif (UNIX)
