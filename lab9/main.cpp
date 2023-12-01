#include <iostream>
#include <climits>

#include "types.hpp"
#include "johnson.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    TGraph g;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        if (g.find(u-1) == g.end()) {
            g[u-1] = std::vector<TNode>();
        }
        g[u-1].emplace_back(v-1, w);
    }

    try {
        TGraph answer = Johnson(g, n);
        std::vector<std::vector<long>> matrix(n, std::vector<long>(n, LONG_MAX));
        for (int i = 0; i < n; ++i) {
            for (TNode &p: answer[i]) {
                matrix[i][p.v] = p.w;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == LONG_MAX)
                    std::cout << "inf ";
                else
                    std::cout << matrix[i][j] << " ";
            }
            std::cout << '\n';
        }
    } catch (TNegativeCycle &e) {
        std::cout << "Negative cycle\n";
    }
    return 0;
}