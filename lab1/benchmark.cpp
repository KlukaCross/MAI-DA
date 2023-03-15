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

    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();
    radix_sort(input);
    auto end_ts = std::chrono::system_clock::now();
    uint64_t radix_sort_ts = std::chrono::duration_cast<std::chrono::microseconds>(end_ts - start_ts ).count();

    start_ts = std::chrono::system_clock::now();
    std::stable_sort(input_stl.Begin(), input_stl.End(), cmp);
    end_ts = std::chrono::system_clock::now();

    uint64_t stl_sort_ts = std::chrono::duration_cast<std::chrono::microseconds>( end_ts - start_ts ).count();
    std::cout << "Radix sort time: " << radix_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "STL stable sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;
}