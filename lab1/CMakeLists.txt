cmake_minimum_required(VERSION 3.24)
project(LAB1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 lab1.cpp vector.hpp kv_struct.hpp sort.hpp parser.hpp parser.cpp sort.cpp kv_struct.cpp)
add_executable(benchmark benchmark.cpp vector.hpp kv_struct.cpp kv_struct.hpp sort.cpp sort.hpp parser.cpp)