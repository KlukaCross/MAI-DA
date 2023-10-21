CXX = g++
CXXFLAGS = -std=c++2a -pedantic -Wall -Wextra -Werror

all: lab7 benchmark

lab7: main.cpp knapsack.cpp
	$(CXX) $(CXXFLAGS) main.cpp knapsack.cpp -o lab7.out

benchmark: benchmark.cpp knapsack.cpp
	$(CXX) $(CXXFLAGS) benchmark.cpp knapsack.cpp -o benchmark.out

clean:
	rm -f lab7.lab benchmark.out *.o
