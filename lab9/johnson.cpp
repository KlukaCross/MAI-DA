#include <climits>

#include "johnson.hpp"
#include "bellman_ford.hpp"
#include "dijkstra.hpp"


TMatrix Johnson(const TMatrix &g) {
    int n = g.size();
    TMatrix answer(n, std::vector<int>(n));
    TMatrix gd = g;
    std::vector<int> h(n+1, INT_MAX);
    gd.emplace_back(n, 0);

    bool negativeCycleExists = BellmanFord(gd, n, h);
    if (negativeCycleExists)
        throw TNegativeCycle();

    for (int i = 0; i < n+1; ++i) {
        for (int j = 0; j < n; ++j) {
            gd[i][j] += h[i] - h[j];
        }
    }
    for (int i = 0; i < n; ++i) {
        std::vector<int> delta = Dijkstra(gd, i);
        for (int j = 0; j < n; ++j) {
            answer[i][j] = delta[j] + h[j] - h[i];
        }
    }
    return answer;
}
