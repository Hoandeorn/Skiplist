cmake_minimum_required(VERSION 3.21)
project(Skiplist)

set(CMAKE_CXX_STANDARD 14)

add_executable(Skiplist main.cpp Node.h Skiplist.h tools.h)
