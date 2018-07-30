#include <bits/stdc++.h>
#define MAXM 2010
using namespace std;

int n, m, x, a, b, c, dp[MAXM];

inline void cmax(register int &a, register int b) {
    (a < b) && (a = b);
}

int main() {
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &x, &a, &b);
        switch (x) {
            case 1 :
                for (register int j = m, j_lim = b / a; j > j_lim; --j)
                    for (register int k = 1; k <= j; ++k)
                        cmax(dp[j], dp[j - k] + a * k * k - b * k);
                break;
            case 2 :
                scanf("%d", &c);
                for (register int j = 1; j <= c; ++j)
                    for (register int k = m; k >= b; --k)
                        cmax(dp[k], dp[k - b] + a);
                break;
            case 3 :
                for (register int j = b; j <= m; ++j)
                    cmax(dp[j], dp[j - b] + a);
                break;
        }
    }
    printf("%d\n", dp[m]);
    return 0;
}
