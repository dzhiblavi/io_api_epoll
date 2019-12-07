cmake_minimum_required(VERSION 3.12)
project(web_cracker)

set(CMAKE_CXX_STANDARD 17)

set(REQ_FILES
        address.h
        address.cpp
        unique_fd.cpp
        unique_fd.h
        ipv4_exception.h
        io_api.cpp
        io_api.h
        socket.cpp
        socket.h
        echo_server.cpp
        echo_server.h)

add_executable(server main.cpp
        ${REQ_FILES})
