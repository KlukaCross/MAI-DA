cmake_minimum_required(VERSION 3.24)
project(lab8)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab8 main.cpp coin_exchange.cpp)
add_executable(benchmark benchmark.cpp coin_exchange.cpp)
