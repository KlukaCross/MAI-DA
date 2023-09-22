#include <iostream>
#include <chrono>
#include <vector>
#include "suffix_tree.hpp"

const std::string DURATION_PREFIX = "us";

std::string primitiveSearch(std::string &s) {
    std::string minSector = s;
    for (size_t i = 0; i < s.size(); ++i) {
        std::string tmp = s.substr(i)+s.substr(0, i);
        if (tmp < minSector) {
            minSector = tmp;
        }
    }
    return minSector;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, doubleS;
    std::cin >> s;
    size_t n = s.size();
    doubleS = s + s;

    std::string action;
    std::chrono::time_point<std::chrono::system_clock> startTs, endTs;

    startTs = std::chrono::system_clock::now();
    TSuffixTree *st = new TSuffixTree(doubleS);
    st->FindMinimumLineSectionSuffixNumber(n);
    endTs = std::chrono::system_clock::now();
    uint64_t suffixTreeTime = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    startTs = std::chrono::system_clock::now();
    primitiveSearch(s);
    endTs = std::chrono::system_clock::now();
    uint64_t primitiveSearchTime = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    std::cout << "Suffix tree search time: " << suffixTreeTime << DURATION_PREFIX << '\n';
    std::cout << "Primitive search time: " << primitiveSearchTime << DURATION_PREFIX << '\n';
}