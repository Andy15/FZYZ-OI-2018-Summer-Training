#include <bits/stdc++.h>
#define MAXN 210
#define INF 0X3f3f3f3f
using namespace std;

int T, n, a, b[MAXN], sum, dp[MAXN][MAXN];

inline void cmin(register int &a, register int b) {
    (a > b) && (a = b);
}

int main() {
    scanf("%d", &T);
    for (register int xiaoT = 1; xiaoT <= T; ++xiaoT) {
        sum = 0; /*memset(dp, 0, sizeof(dp));*/ memset(b, 0, sizeof(b));
        scanf("%d", &n);
        for (register int i = 1; i <= n; ++i) {
            scanf("%d", &a); sum += a;
        }
        for (register int i = 1; i <= n; ++i)
            scanf("%d", &b[i]);
        for (register int len = 1; len <= n; ++len)
            for (register int l = 1, r = len; r <= n; ++l, ++r) {
                dp[l][r] = INF;
                for (register int k = l; k <= r; ++k)
                    cmin(dp[l][r], dp[l][k - 1] + dp[k + 1][r]);
                dp[l][r] += b[l - 1] + b[r + 1];
            }
        printf("Case #%d: %d\n", xiaoT, sum + dp[1][n]);
    }
    return 0;
}
