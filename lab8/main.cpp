#include <iostream>
#include <vector>
#include "coin_exchange.hpp"
#include <cmath>

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
    std::vector<uint32_t> nominalNumbers = coinExchange(nominal, m);
    for (auto nom: nominalNumbers) {
        std::cout << nom << '\n';
    }
    return 0;
}
