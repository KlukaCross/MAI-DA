CXX = g++
CXXFLAGS = -std=c++2a -pedantic -Wall -Wextra -Werror

all: lab5 benchmark

lab5: main.cpp suffix_tree.cpp
	$(CXX) $(CXXFLAGS) suffix_tree.cpp main.cpp -o lab5.out

benchmark: benchmark.cpp suffix_tree.cpp
	$(CXX) $(CXXFLAGS) suffix_tree.cpp benchmark.cpp -o benchmark.out

clean:
	rm -f lab5.lab benchmark.out *.o