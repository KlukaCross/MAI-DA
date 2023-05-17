#include <iostream>
#include <string>
#include <deque>
#include "boyer_moore_search.hpp"

uint64_t WordsParsing(const std::string& words, std::deque<std::string>& d) {
    std::string buf;
    uint64_t size = 0;
    for (auto w: words) {
        if (w == ' ') {
            if (!buf.empty()) {
                d.push_back(buf);
                ++size;
                buf.clear();
            }
        } else {
            buf += tolower(w);
        }
    }
    if (!buf.empty()) {
        d.push_back(buf);
        ++size;
    }
    return size;
}

void EraseLine(uint64_t& lineInfoShift, std::deque<std::pair<uint64_t, uint64_t>>& linesInfo, uint64_t& startK,
               std::deque<std::string>& text) {
    lineInfoShift += linesInfo[0].second;
    for (uint64_t i = 0; i < linesInfo[0].second; ++i) {
        text.pop_front();
    }
    startK -= linesInfo[0].second;
    linesInfo.pop_front();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::deque<std::string> pattern;
    std::deque<std::string> text;
    std::string words;

    std::getline(std::cin, words);
    WordsParsing(words, pattern);
    BoyerMooreSearch bms(pattern);
    uint64_t n = pattern.size();

    uint64_t lineCount = 0;
    std::deque<std::pair<uint64_t, uint64_t>> linesInfo;
    uint64_t startK = n;
    while (std::getline(std::cin, words)) {
        uint64_t lineSize = WordsParsing(words, text);
        ++lineCount;
        if (lineSize == 0) {
            continue;
        }
        linesInfo.emplace_back(lineCount, lineSize);
        auto [positions, lastK] = bms.Search(text, startK);
        startK = lastK;

        uint64_t lineInfoShift = 0;
        for (uint64_t entryPos: positions) {
             while (lineInfoShift + linesInfo[0].second <= entryPos) {
                 EraseLine(lineInfoShift, linesInfo, startK, text);
             }
             std::cout << linesInfo[0].first << ", " << entryPos - lineInfoShift + 1 << '\n';
        }
        while (!linesInfo.empty() && lineInfoShift + linesInfo[0].second <= lastK - n) {
            EraseLine(lineInfoShift, linesInfo, startK, text);
        }
    }
    return 0;
}
