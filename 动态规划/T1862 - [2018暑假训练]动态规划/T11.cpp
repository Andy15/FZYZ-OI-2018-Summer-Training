#include <bits/stdc++.h>
#define MAXN 1010
#define MAXC 1010
#define C_LIM 1000
using namespace std;

int n, q, p[MAXN], b[MAXN], a, c, dp[MAXN][MAXC];

inline void cmax(register int &a, register int b) {
    (a < b) && (a = b);
}

int main() {
    scanf("%d%d", &n, &q);
    for (register int i = 1; i <= n; ++i)
        scanf("%d%d", &p[i], &b[i]);
    for (register int o = 1; o <= n; ++o) {
        for (register int i = 1; i <= n; ++i) {
            if (i == o)
                continue;
            for (register int j = C_LIM, w = p[i], v = b[i]; j >= w; --j)
                cmax(dp[o][j], dp[o][j - w] + v);
        }
    }
    while (q--) {
        scanf("%d%d", &a, &c);
        printf("%d\n", dp[a][c]);
    }
    return 0;
}
