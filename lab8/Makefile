CXX = g++
CXXFLAGS = -std=c++2a -pedantic -Wall -Wextra -Werror

all: lab8 benchmark

lab8: main.cpp coin_exchange.cpp
	$(CXX) $(CXXFLAGS) main.cpp coin_exchange.cpp -o lab8.out

benchmark: benchmark.cpp coin_exchange.cpp
	$(CXX) $(CXXFLAGS) benchmark.cpp coin_exchange.cpp -o benchmark.out

clean:
	rm -f lab8.lab benchmark.out *.o
