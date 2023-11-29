#include <iostream>
#include <climits>

#include "types.hpp"
#include "johnson.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    TMatrix g(n, std::vector<int>(n, INT_MAX));
    for (int i = 0; i < n; ++i) {
        g[i][i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        std::cin >> a >> b >> w;
        g[a][b] = w;
    }

    try {
        TMatrix answer = Johnson(g);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (answer[i][j] == INTMAX_MAX)
                    std::cout << "inf ";
                else
                    std::cout << answer[i][j] << " ";
            }
            std::cout << '\n';
        }
    } catch (TNegativeCycle &e) {
        std::cout << "Negative cycle\n";
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
