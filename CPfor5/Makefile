CXX = g++
CXXFLAGS = -std=c++2a -pedantic -Wall -Wextra -Werror

all: cp cp_profiler

cp: main.cpp minimp3.h minimp3_ex.h
	$(CXX) $(CXXFLAGS) main.cpp -o cp.out

cp_profiler: main.cpp minimp3.h minimp3_ex.h
	$(CXX) $(CXXFLAGS) -pg main.cpp -o cp_profiler.out

clean:
	rm -f cp.out cp_profiler.out *.o