#include <bits/stdc++.h>
#define MAXX 310
using namespace std;

int m, n, p, tmp, dp[MAXX][MAXX][MAXX];
char a[MAXX], b[MAXX], c[MAXX];

inline void cmax(register int &a, register int b) {
    (a < b) && (a = b);
}

inline int dmax(register int &a, register int &b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d%d%d%s%s%s", &m, &n, &p, a + 1, b + 1, c + 1);
    for (register int i = 1; i <= m; ++i)
        for (register int j = 1; j <= n; ++j)
                for (register int k = 1; k <= p; ++k) {
                    tmp = dmax(dp[i - 1][j][k], dp[i][j - 1][k]);
                    (dp[i - 1][j - 1][k] > 0) && (cmax(tmp, dp[i - 1][j - 1][k] + (a[i] == b[j])), 1);
                    ((a[i] == b[j] && b[j] == c[k]) && (dp[i - 1][j - 1][k - 1] > 0 || k == 1)) && (cmax(tmp, dp[i - 1][j - 1][k - 1] + 1), 1);
                    dp[i][j][k] = tmp;
                    //printf("Answer of %d %d %d: %d.\n", i, j, k, tmp);
                }
    printf("%d\n", dp[m][n][p] ? dp[m][n][p] : -1);
    return 0;
}
