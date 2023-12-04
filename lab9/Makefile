CXX = g++
CXXFLAGS = -std=c++2a -pedantic -Wall -Wextra -Werror

all: lab9 benchmark

lab9: main.cpp johnson.cpp bellman_ford.cpp dijkstra.cpp
	$(CXX) $(CXXFLAGS) main.cpp johnson.cpp bellman_ford.cpp dijkstra.cpp -o lab9.out

benchmark: benchmark.cpp johnson.cpp bellman_ford.cpp dijkstra.cpp
	$(CXX) $(CXXFLAGS) benchmark.cpp johnson.cpp bellman_ford.cpp dijkstra.cpp -o benchmark.out

clean:
	rm -f lab9.lab benchmark.out *.o
