project(lab2)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab2 main.cpp patricia.hpp patricia.cpp custom_exception.hpp)
add_executable(benchmark benchmark.cpp patricia.hpp patricia.cpp custom_exception.hpp)
