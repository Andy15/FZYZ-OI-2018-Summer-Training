#include <bits/stdc++.h>
#define MAXN 110
#define INF 0x3f3f3f3f
using namespace std;

int n, a[MAXN], pre[MAXN], dp[MAXN][MAXN], tmp, ans = INF;

inline void cmin(register int &a, register int b) {
    (a > b) && (a = b);
}

int main() {
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        pre[i] = pre[i - 1] + a[i];
    }
    for (register int o = 1; o < n; ++o) {
        pre[o] += a[o + 1] - a[o];
        memset(dp, 0, sizeof(dp));
        for (register int len = 2; len <= n; ++len)
            for (register int l = 1, r = len; r <= n; ++l, ++r) {
                dp[l][r] = INF; tmp = pre[r] - pre[l - 1];
                for (register int k = l; k < r; ++k)
                    cmin(dp[l][r], dp[l][k] + dp[k + 1][r] + tmp);
            }
        cmin(ans, dp[1][n]);
        pre[o] += a[o] - a[o + 1];
    }
    printf("%d\n", ans);
    return 0;
}
