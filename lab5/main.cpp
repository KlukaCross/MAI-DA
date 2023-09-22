#include <iostream>
#include <string>
#include "suffix_tree.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    size_t n = s.size();
    s = s + s;
    TSuffixTree st(s);
    int suf = st.FindMinimumLineSectionSuffixNumber(n);
    std::cout << s.substr(suf, n) << '\n';
    return 0;
}
