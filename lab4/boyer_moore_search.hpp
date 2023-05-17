#ifndef LAB4_BOYER_MOORE_SEARCH_HPP
#define LAB4_BOYER_MOORE_SEARCH_HPP

#include <tuple>
#include <deque>
#include <vector>
#include <string>
#include <unordered_map>

using Tchar = std::string;

class BoyerMooreSearch {
// variables
private:
    std::unordered_map<Tchar, std::vector<uint64_t>> badCharPositions;
    std::vector<uint64_t> goodSuffixShiftsA, goodSuffixShiftsB;
    std::deque<Tchar> pattern;
// methods
private:
    void BadCharPositionsFill();
    void GoodSuffixShiftAFill();
    void GoodSuffixShiftBFill();
    uint64_t BadCharRuleShift(const std::deque<Tchar>& text, uint64_t i, uint64_t j);
    uint64_t GoodSuffixRuleShift(uint64_t i);
    std::vector<uint64_t> ZFunction(const std::deque<Tchar>& s);
    std::deque<Tchar> ReversePattern();
public:
    BoyerMooreSearch(const std::deque<Tchar>& pattern);
    std::tuple<std::vector<uint64_t>, uint64_t> Search(std::deque<Tchar>& text, uint64_t startK);
};

#endif //LAB4_BOYER_MOORE_SEARCH_HPP
