#include <climits>

#include "bellman_ford.hpp"


bool BellmanFord(TGraph &g, int n, int start, std::vector<long> &h) {
    h.resize(n, LONG_MAX);
    h[start] = 0;

    for (int i = 0; i < n-1; ++i) {
        for (int u = 0; u < n; ++u) {
            if (g.find(u) == g.end())
                continue;
            for (TNode &node: g[u]) {
                h[node.v] = std::min(h[node.v], h[u] == LONG_MAX ? h[u] : h[u] + node.w);  // relax
            }
        }
    }
    for (int u = 0; u < n; ++u) {
        if (g.find(u) == g.end())
            continue;
        for (TNode &node: g[u]) {
            if (h[node.v] > h[u] + node.w) {
                return false;
            }
        }
    }
    return true;
}