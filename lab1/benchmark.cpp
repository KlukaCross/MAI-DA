#include <iostream>
#include <chrono>

#include "sort.hpp"
#include "vector.hpp"
#include "parser.hpp"

const std::string DURATION_PREFIX = "us";

bool cmp(TMD5String* lhs, TMD5String* rhs) {
    return lhs->GetIntKey() < rhs->GetIntKey();
}

int main()
{
    TVector<TMD5String*> input;
    Parser(input);
    TVector<TMD5String*> input_stl(input);

    std::cout << "Count of lines is " << input.Size() << std::endl;

    std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
    RadixSort(input);
    std::chrono::time_point endTs = std::chrono::system_clock::now();
    uint64_t radixSortTs = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    startTs = std::chrono::system_clock::now();
    std::stable_sort(input_stl.Begin(), input_stl.End(), cmp);
    endTs = std::chrono::system_clock::now();

    uint64_t stlSortTs = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();
    std::cout << "Radix sort time: " << radixSortTs << DURATION_PREFIX << std::endl;
    std::cout << "STL stable sort time: " << stlSortTs << DURATION_PREFIX << std::endl;
}