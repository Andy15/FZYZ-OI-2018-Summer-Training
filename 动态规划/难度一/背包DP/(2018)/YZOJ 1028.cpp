#include <bits/stdc++.h>
#define MAXM 10010
using namespace std;

int m, n, v, w, dp[MAXM];

inline void cmax(register int &a, register int b) {
    (a < b) && (a = b);
}

int main() {
    for (scanf("%d%d", &m, &n); n; --n) {
        scanf("%d%d", &v, &w);
        for (register int i = w; i <= m; ++i)
            cmax(dp[i], dp[i - w] + v);
    }
    printf("%d\n", dp[m]);
    return 0;
}
