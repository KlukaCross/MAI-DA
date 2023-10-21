#include <iostream>
#include <vector>
#include "knapsack.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n, m;
    std::cin >> n >> m;
    std::vector<uint32_t> w(n), c(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> w[i] >> c[i];
    }
    std::vector<int> path;
    uint32_t res = knapsack(n, m, w, c, path);
    std::cout << res << '\n';
    for (int i = path.size()-1; i >= 0; --i) {
        std::cout << path[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}
