CXX = g++
CXXFLAGS = -std=c++2a -pedantic -Wall -Wextra -Werror

all: lab2 lab2_profiler benchmark

lab2: main.cpp patricia.cpp custom_exception.hpp
	$(CXX) $(CXXFLAGS) patricia.cpp main.cpp -o lab2.out

lab2_profiler: main.cpp patricia.cpp custom_exception.hpp
	$(CXX) $(CXXFLAGS) -pg patricia.cpp main.cpp -o lab2_profiler

benchmark: benchmark.cpp patricia.cpp custom_exception.hpp
	$(CXX) $(CXXFLAGS) patricia.cpp benchmark.cpp -o benchmark.out

clean:
	rm -f lab2 lab2_profiler benchmark benchmark_profiler *.o