#include <iostream>
#include <vector>

uint32_t knapsack(size_t n, size_t m, std::vector<uint32_t>& w, std::vector<uint32_t>& c, std::vector<int>& answerPath) {
    // dp[i][j][k] = максимальная стоимость в рюкзаке вместимости k, если можно взять j предметов из первых i
    std::vector<std::vector<std::vector<uint32_t>>> dp(n+1, std::vector<std::vector<uint32_t>>(n+1, std::vector<uint32_t>(m+1, 0)));
    for (size_t i = 1; i <= n; ++i) {
        for (size_t k = 1; k <= m; ++k) {
            dp[i][1][k] = dp[i-1][1][k];
            if (w[i-1] <= k) {
                uint32_t tmp = dp[i-1][1][k-w[i-1]] + c[i-1];
                if (tmp > dp[i][1][k]) {
                    dp[i][1][k] = tmp;
                }
            }
        }
    }
    for (size_t i = 2; i <= n; ++i) {
        for (size_t j = 2; j <= i; ++j) {
            for (size_t k = 1; k <= m; ++k) {
                dp[i][j][k] = dp[i-1][j][k];
                if (w[i-1] <= k && dp[i-1][j-1][k-w[i-1]] > 0) {
                    uint32_t tmp = (dp[i-1][j-1][k-w[i-1]] / (j-1) + c[i-1]) * j;
                    if (tmp > dp[i][j][k]) {
                        dp[i][j][k] = tmp;
                    }
                }
            }
        }
    }
    size_t i = n, j = 0, k = m;
    size_t maxValue = 0;
    for (size_t jj = 0; jj <= n; ++jj) {
        if (dp[i][jj][k] > maxValue) {
            j = jj;
            maxValue = dp[i][jj][k];
        }
    }
    while (dp[i][j][k] > 0) {
        if (dp[i][j][k] == dp[i-1][j][k]) {
            --i;
        } else {
            k -= w[i-1];
            --j;
            answerPath.push_back(i--);
        }
    }
    return maxValue;
}
