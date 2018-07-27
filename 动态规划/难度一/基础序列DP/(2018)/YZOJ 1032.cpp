#include <bits/stdc++.h>
#define MAXM 510
using namespace std;

int n, m1, a1[MAXM], m2, a2[MAXM], dp[2][MAXM], *f, *g, *h, ans;

inline void cmax(register int &f, register int g) {
    (f < g) && (f = g);
}

int main() {
    for (scanf("%d", &n); n; --n) {
        memset(dp, 0, sizeof(dp)); f = dp[0]; g = dp[1]; ans = 0;
        scanf("%d", &m1);
        for (register int i = 1; i <= m1; ++i)
            scanf("%d", &a1[i]);
        scanf("%d", &m2);
        for (register int i = 1; i <= m2; ++i)
            scanf("%d", &a2[i]);
        for (register int i = 1; i <= m1; ++i) {
            int g_max = 0;
            for (register int j = 1; j <= m2; ++j) {
                g[j + 1] = f[j + 1];
                (a1[i] > a2[j]) && (cmax(g_max, g[j + 1]), 1);
                (a1[i] == a2[j]) && (g[j + 1] = g_max + 1);
                cmax(ans, g[j + 1]);
            }
            h = f; f = g; g = h;
        }
        printf("%d\n", ans);
    }
    return 0;
}
