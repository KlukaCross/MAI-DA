CXX = g++
CXXFLAGS = -std=c++2a -pedantic -Wall -Wextra -Werror

all: audiosearch

audiosearch: main.cpp minimp3.h minimp3_ex.h audiosearch.cpp database.cpp tools.cpp
	$(CXX) $(CXXFLAGS) main.cpp audiosearch.cpp database.cpp tools.cpp -o audiosearch.out

clean:
	rm -f audiosearch.out *.o
