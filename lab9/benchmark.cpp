#include <iostream>
#include <chrono>
#include <vector>
#include <climits>
#include "johnson.hpp"

const std::string DURATION_PREFIX = "us";

std::vector<std::vector<long>> FloydWarshall(const std::vector<std::vector<long>> &g, int n) {
    std::vector<std::vector<long>> distance(g);
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (distance[i][k] != LONG_MAX && distance[k][j] != LONG_MAX && (distance[i][k] + distance[k][j] < distance[i][j])) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
    return distance;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<long>> matrix(n, std::vector<long>(n, LONG_MAX));
    TGraph g;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        if (g.find(u-1) == g.end()) {
            g[u-1] = std::vector<TNode>();
        }
        g[u-1].emplace_back(v-1, w);
        matrix[u-1][v-1] = w;
    }

    std::chrono::time_point<std::chrono::system_clock> startTs, endTs;

    startTs = std::chrono::system_clock::now();
    Johnson(g, n);
    endTs = std::chrono::system_clock::now();
    uint64_t JohnsonTime = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    startTs = std::chrono::system_clock::now();
    FloydWarshall(matrix, n);
    endTs = std::chrono::system_clock::now();
    uint64_t FloydWarshallTime = std::chrono::duration_cast<std::chrono::microseconds>(endTs - startTs ).count();

    std::cout << "Johnson time: " << JohnsonTime << DURATION_PREFIX << '\n';
    std::cout << "FloydWarshall time: " << FloydWarshallTime << DURATION_PREFIX << '\n';
}