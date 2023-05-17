#include "boyer_moore_search.hpp"


BoyerMooreSearch::BoyerMooreSearch(const std::deque<Tchar>& pattern) {
    this->pattern = pattern;
    BadCharPositionsFill();
    GoodSuffixShiftAFill();
    GoodSuffixShiftBFill();
}

std::tuple<std::vector<uint64_t>, uint64_t> BoyerMooreSearch::Search(std::deque<Tchar>& text, uint64_t startK) {
    std::vector<uint64_t> answer;
    uint64_t n = pattern.size();
    uint64_t m = text.size();
    uint64_t k = startK;
    while (k <= m) {
        uint64_t i = n;
        uint64_t j = k;
        while (i > 0 && pattern[i-1] == text[j-1]) {
            --i;
            --j;
        }
        if (i == 0) {
            answer.push_back(j);
            k = k + n - goodSuffixShiftsB[1];
        } else {
            uint64_t badCharRuleShift = BadCharRuleShift(text, i-1, j-1);
            uint64_t goodSuffixRuleShift = GoodSuffixRuleShift(i-1);
            k += std::max(badCharRuleShift, goodSuffixRuleShift);
        }
    }
    return std::make_tuple(answer, k);
}

void BoyerMooreSearch::BadCharPositionsFill() {
    for (uint64_t i = 0; i < pattern.size(); ++i) {
        if (!badCharPositions.contains(pattern[i])) {
            std::vector<uint64_t> v;
            badCharPositions.insert({pattern[i], v});
        }
        std::vector<uint64_t>& v = badCharPositions[pattern[i]];
        v.push_back(i);
    }
}

void BoyerMooreSearch::GoodSuffixShiftAFill() {
    std::vector<uint64_t> z = ZFunction(ReversePattern()); // N is inverted Z
    uint64_t n = pattern.size();
    goodSuffixShiftsA.resize(n);
    for (uint64_t j = 0; j < n-1; ++j) {
        uint64_t i = n - z[n-j-1];
        if (i < n) {
            goodSuffixShiftsA[i] = j;
        }
    }
}

void BoyerMooreSearch::GoodSuffixShiftBFill() {
    std::vector<uint64_t> z = ZFunction(ReversePattern()); // N is inverted Z
    uint64_t n = pattern.size();
    goodSuffixShiftsB.resize(n);
    for (uint64_t j = 0; j < n-1; ++j) {
        if (z[n-j-1] == j + 1) {
            uint64_t i = n - j - 1;
            goodSuffixShiftsB[i] = j + 1;
        }
    }
    for (uint64_t j = 2; j <= n; ++j) {
        goodSuffixShiftsB[n-j] = std::max(goodSuffixShiftsB[n-j], goodSuffixShiftsB[n-j+1]);
    }
}

uint64_t BoyerMooreSearch::BadCharRuleShift(const std::deque<Tchar> &text, uint64_t i, uint64_t j) {
    if (!badCharPositions.contains(text[j])) {
        return i;
    }

    std::vector<uint64_t>& positions = badCharPositions[text[j]];
    uint64_t l = 0, r = positions.size() - 1;
    while (l < r) {
        uint64_t m = (l + r + 1) / 2;
        if (positions[m] < i) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    if (positions[l] >= i) {
        return 1;
    }
    return i-positions[l];
}

uint64_t BoyerMooreSearch::GoodSuffixRuleShift(uint64_t i) {
    if (i == pattern.size() - 1) {
        return 1;
    }
    return pattern.size() - (goodSuffixShiftsA[i+1] > 0 ? goodSuffixShiftsA[i+1] : goodSuffixShiftsB[i+1]) - 1;
}

std::vector<uint64_t> BoyerMooreSearch::ZFunction(const std::deque<Tchar>& s) {
    uint64_t n = s.size();
    std::vector<uint64_t> z(n);
    uint64_t l = 0, r = 0;
    for (uint64_t i = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r-l, z[i-l]);
        }
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            ++z[i];
        }
        if (i+z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

std::deque<Tchar> BoyerMooreSearch::ReversePattern() {
    uint64_t n = pattern.size();
    std::deque<Tchar> reversePattern(n);
    for (uint64_t i = 1; i <= n; ++i) {
        reversePattern[n - i] = pattern[i - 1];
    }
    return reversePattern;
}

