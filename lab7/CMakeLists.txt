cmake_minimum_required(VERSION 3.24)
project(lab7)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab7 main.cpp knapsack.cpp)
add_executable(benchmark benchmark.cpp knapsack.cpp)
