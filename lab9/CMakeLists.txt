cmake_minimum_required(VERSION 3.24)
project(lab9)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab9 main.cpp johnson.hpp johnson.cpp types.hpp bellman_ford.hpp bellman_ford.cpp dijkstra.hpp dijkstra.cpp)
add_executable(benchmark benchmark.cpp johnson.hpp johnson.cpp types.hpp bellman_ford.hpp bellman_ford.cpp dijkstra.hpp dijkstra.cpp)