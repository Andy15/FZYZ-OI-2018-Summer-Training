#include <bits/stdc++.h>
#define MAXN 210
#define MAXA 50
#define A_LIM 40
using namespace std;

int n, a[MAXN], m;
bool dp[MAXN][MAXN >> 1][MAXN * MAXA >> 2];

inline int dmax(register int a, register int b) {
    return a > b ? a : b;
}

inline int dmin(register int a, register int b) {
    return a < b ? a : b;
}

inline int xabs(register int o) {
    return o < 0 ? -o : o;
}

int main() {
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]); m += a[i];
    }
    dp[0][0][0] = 1;
    for (register int i = 1; i <= n; ++i)
        for (register int j = 0, j_lim = dmin(n >> 1, i); j <= j_lim; ++j)
            for (register int k = 0, k_lim = j * A_LIM; k <= k_lim; ++k)
                ((dp[i - 1][j][k]) || (j && k >= a[i] && dp[i - 1][j - 1][k - a[i]])) && (dp[i][j][k] = 1);
    register int ans = 0;
    for (register int i = 1, tmp = n >> 1, i_lim = n * A_LIM; i <= i_lim; ++i)
        (dp[n][tmp][i] && xabs(m - (i << 1)) < xabs((ans << 1) - m)) && (ans = i);
    printf("%d %d\n", dmin(ans, m - ans), dmax(ans, m - ans));
    return 0;
}
