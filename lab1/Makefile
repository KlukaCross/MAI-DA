CC=g++
FLAGS=-std=c++2a -Wall -Wextra -Wno-unused-variable
OUTPUT=solution

all: kv_struct.o sort.o parser.o lab1.cpp vector.hpp
	$(CC) $(FLAGS) kv_struct.o parser.o sort.o vector.hpp lab1.cpp -o $(OUTPUT)
kv_struct.o: kv_struct.hpp kv_struct.cpp vector.hpp
	$(CC) $(FLAGS) -c kv_struct.hpp kv_struct.cpp vector.hpp
sort.o: kv_struct.o sort.cpp sort.hpp vector.hpp
	$(CC) $(FLAGS) -c kv_struct.o sort.cpp vector.hpp
parser.o: kv_struct.o parser.cpp parser.hpp vector.hpp
	$(CC) $(FLAGS) -c kv_struct.o parser.cpp parser.hpp vector.hpp
benchmark: kv_struct.o parser.o sort.o vector.hpp benchmark.cpp
	$(CC) $(FLAGS) kv_struct.o parser.o sort.o benchmark.cpp vector.hpp -o benchmark
clean:
	rm *.o *.gch $(OUTPUT)
