cmake_minimum_required(VERSION 3.24)
project(audiosearch)

set(CMAKE_CXX_STANDARD 23)

add_executable(audiosearch main.cpp audiosearch.hpp database.hpp tools.hpp tools.cpp database.cpp audiosearch.cpp)
