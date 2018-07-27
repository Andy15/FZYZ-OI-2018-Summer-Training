#include <bits/stdc++.h>
#define MAXS 110
using namespace std;

char t1[MAXS], t2[MAXS];
int n, m, dp[MAXS][MAXS];

inline int dmax(register int a, register int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%s%s", t1 + 1, t2 + 1); n = strlen(t1 + 1); m = strlen(t2 + 1);
    for (register int i = 1; i <= n; ++i)
        dp[i][0] = -(i << 1);
    for (register int j = 1; j <= m; ++j)
        dp[0][j] = -(j << 1);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j)
            dp[i][j] = dmax(dp[i - 1][j - 1] + (t1[i] == t2[j]), dmax(dp[i][j - 1] - 2, dp[i - 1][j] - 2));
    printf("%d\n", dp[n][m]);
    return 0;
}
