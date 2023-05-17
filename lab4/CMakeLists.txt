project(lab4)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab4 main.cpp boyer_moore_search.hpp boyer_moore_search.cpp)
add_executable(benchmark benchmark.cpp boyer_moore_search.hpp boyer_moore_search.cpp)