#include <climits>

#include "johnson.hpp"
#include "bellman_ford.hpp"
#include "dijkstra.hpp"


TGraph Johnson(const TGraph &g, int n) {
    TGraph answer;
    TGraph gd = g;
    std::vector<long> h;
    gd[n] = std::vector<TNode>(n);
    for (int i = 0; i < n; ++i) {
        gd[n][i].v = i;
        gd[n][i].w = 0;
    }

    bool negativeCycleNotExists = BellmanFord(gd, n+1, n, h);
    if (!negativeCycleNotExists)
        throw TNegativeCycle();

    for (int i = 0; i < n+1; ++i) {
        if (gd.find(i) == gd.end())
            continue;
        for (TNode &node: gd[i]) {
            node.w += h[i] - h[node.v];
        }
    }
    for (int i = 0; i < n; ++i) {
        std::vector<long> delta = Dijkstra(gd, n, i);
        answer[i] = std::vector<TNode>();
        for (int j = 0; j < n; ++j) {
            answer[i].emplace_back(j, delta[j] == LONG_MAX ? delta[j] : delta[j] + h[j] - h[i]);
        }
    }
    return answer;
}

