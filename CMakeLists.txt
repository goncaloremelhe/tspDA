cmake_minimum_required(VERSION 3.26)
project(Headers)

set(CMAKE_CXX_STANDARD 17)

add_executable(Headers main.cpp
        Headers/Graph.h
        Sources/Salesperson.cpp
        Headers/Salesperson.h
        Sources/Menu.cpp
        Headers/MutablePriorityQueue.h)
