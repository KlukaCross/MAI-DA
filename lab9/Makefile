CXX = g++
CXXFLAGS = -std=c++2a -pedantic -Wall -Wextra -Werror

all: lab9 benchmark

lab9: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o lab9.out

benchmark: benchmark.cpp
	$(CXX) $(CXXFLAGS) benchmark.cpp -o benchmark.out

clean:
	rm -f lab9.lab benchmark.out *.o
