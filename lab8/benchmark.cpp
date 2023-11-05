#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include "coin_exchange.hpp"

const std::string DURATION_PREFIX = "us";

uint32_t coinExchangeDP(std::vector<uint64_t>& nominal, uint32_t m) {
    uint32_t n = nominal.size();
    std::vector<uint32_t> dp(m+1, uint32_t(-1)-1);
    for (uint32_t j = 0; j < n; ++j) {
        if (nominal[j] > m)
            break;
        dp[nominal[j]] = 1;
    }
    for (uint32_t i = 1; i <= m; ++i) {
        for (uint32_t j = 0; j < n; ++j) {
            if (nominal[j] >= i)
                break;
            if (dp[i] > dp[i-nominal[j]]+1)
                dp[i] = dp[i-nominal[j]]+1;
        }
    }
    return dp[m];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t n, p;
    uint32_t m;
    std::cin >> n >> p >> m;
    std::vector<uint64_t> nominal(n);
    for (size_t i = 0; i < n; ++i) {
        nominal[i] = std::pow(p, i);
    }

    std::string action;
    std::chrono::time_point<std::chrono::system_clock> startTs, endTs;

    startTs = std::chrono::system_clock::now();
    std::vector<uint32_t> nominalNumbers = coinExchange(nominal, m);
    endTs = std::chrono::system_clock::now();
    uint32_t greedyAnswer = 0;
    for (auto v: nominalNumbers)
        greedyAnswer += v;
    uint64_t greedyTime = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    startTs = std::chrono::system_clock::now();
    uint32_t DPAnswer = coinExchangeDP(nominal, m);
    endTs = std::chrono::system_clock::now();
    uint64_t DPTime = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    std::cout << "greedy time: " << greedyTime << DURATION_PREFIX << '\n';
    std::cout << "DP time: " << DPTime << DURATION_PREFIX << '\n';
    if (greedyAnswer != DPAnswer)
        std::cout << "Wrong answer!\n";
}
