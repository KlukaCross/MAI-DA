#include <iostream>
#include <chrono>
#include <vector>
#include "knapsack.hpp"

const std::string DURATION_PREFIX = "us";

std::vector<std::vector<int>> getSubsets(std::vector<int>& set) {
    std::vector<std::vector<int>> ans, tmp{{}};
    for (auto x: set) {
        for (auto t: tmp) {
            ans.push_back(t);
        }
        size_t tmp_size = tmp.size();
        for (size_t i = 0; i < tmp_size; ++i) {
            std::vector<int> tmp_copy;
            std::copy(tmp[i].begin(), tmp[i].end(), std::back_inserter(tmp_copy));
            tmp_copy.push_back(x);
            tmp.push_back(tmp_copy);
        }
    }
    for (auto t: tmp) {
        ans.push_back(t);
    }
    return ans;
}

size_t primitiveEnumeration(std::vector<int> &answer_indexes, uint16_t n, uint16_t m, std::vector<uint32_t>& w, std::vector<uint32_t>& c) {
    std::vector<int> range(n);
    for (int i = 0; i < n; ++i) {
        range[i] = i;
    }
    std::vector<std::vector<int>> subsets = getSubsets(range);

    size_t answer = 0;
    for (auto s: subsets) {
        int tmp_w = 0;
        int tmp_c = 0;
        for (int ind: s) {
            tmp_w += w[ind];
            tmp_c += c[ind];
        }
        if (tmp_w > m)
            break;
        if (answer < tmp_c*s.size()) {
            answer = tmp_c*s.size();
            answer_indexes = s;
        }
    }
    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint16_t n, m;
    std::cin >> n >> m;
    std::vector<uint32_t> w(n), c(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> w[i] >> c[i];
    }
    std::vector<int> path;

    std::string action;
    std::chrono::time_point<std::chrono::system_clock> startTs, endTs;

    startTs = std::chrono::system_clock::now();
    knapsack(n, m, w, c, path);
    endTs = std::chrono::system_clock::now();
    uint64_t dpTime = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    startTs = std::chrono::system_clock::now();
    primitiveEnumeration(path, n, m, w, c);
    endTs = std::chrono::system_clock::now();
    uint64_t primitiveTime = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    std::cout << "DP time: " << dpTime << DURATION_PREFIX << '\n';
    std::cout << "Primitive enumeration time: " << primitiveTime << DURATION_PREFIX << '\n';
}
