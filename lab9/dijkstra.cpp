#include <climits>
#include <set>

#include "dijkstra.hpp"


std::vector<long> Dijkstra(TGraph &g, int n, int start) {
    std::set<std::pair<long, int>> pq;
    std::vector<long> h(n, LONG_MAX);
    h[start] = 0;

    pq.insert({h[start], start});
    std::vector<bool> visited(n);

    while (!pq.empty()) {
        std::pair<long, int> cur = *pq.begin();
        pq.erase(pq.begin());
        int u = cur.second;
        if (visited[u]) {
            continue;
        }
        for (TNode &node : g[u]) {
            if (h[u] == LONG_MAX) {
                continue;
            }
            if (h[u] + node.w < h[node.v]) {
                h[node.v] = h[u] + node.w;
                pq.insert({h[node.v], node.v});
            }
        }
    }
    return h;
}
