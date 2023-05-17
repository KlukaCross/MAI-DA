#include "boyer_moore_search.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <string>

const std::string DURATION_PREFIX = "us";

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

std::vector<uint64_t> Z(const std::vector<Tchar>& s) {
    uint64_t n = s.size();
    std::vector<uint64_t> z(n);
    uint64_t l = 0, r = 0;
    for (uint64_t i = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r-i, z[l-i]);
        }
        while (i + z[i] < n && s[z[i]] == s[i+z[i]]) {
            ++z[i];
        }
        if (i+z[i] > r) {
            r = i + z[i];
            l = i;
        }
    }
    return z;
}

std::vector<uint64_t> ZFunctionSearch(std::deque<Tchar>& p, std::deque<Tchar>& s) {
    std::vector<uint64_t> res;
    std::vector<Tchar> text;
    for (Tchar &ch: p) {
        text.push_back(ch);
    }
    text.emplace_back("$");
    for (Tchar &ch: s) {
        text.push_back(ch);
    }

    uint64_t n = p.size();
    std::vector<uint64_t> z = Z(text);
    for (uint64_t i = n+1; i < z.size(); ++i) {
        if (z[i] == n) {
            res.push_back(i);
        }
    }
    return res;
}

int main() {
    std::deque<std::string> pattern;
    std::deque<std::string> text;
    std::string words;

    std::getline(std::cin, words);
    WordsParsing(words, pattern);
    uint64_t n = pattern.size();

    while (std::getline(std::cin, words)) {
        WordsParsing(words, text);
    }

    uint64_t m = text.size();

    std::chrono::time_point<std::chrono::system_clock> startTs, endTs;
    uint64_t BMStime, ZFtime;

    startTs = std::chrono::system_clock::now();
    BoyerMooreSearch bms(pattern);
    bms.Search(text, n);
    endTs = std::chrono::system_clock::now();
    BMStime = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    startTs = std::chrono::system_clock::now();
    ZFunctionSearch(pattern, text);
    endTs = std::chrono::system_clock::now();
    ZFtime = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    std::cout << "Pattern size n = " << n << '\n';
    std::cout << "Text size m = " << m << '\n';
    std::cout << "Boyer-Moore search time: " << BMStime << DURATION_PREFIX << '\n';
    std::cout << "Z-function search time: " << ZFtime << DURATION_PREFIX << '\n';
}