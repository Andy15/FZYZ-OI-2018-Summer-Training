#include <bits/stdc++.h>
#define MAXN 2010
using namespace std;

int t, k, n, m, C[MAXN][MAXN], ans[MAXN][MAXN];

int main() {
    scanf("%d%d", &t, &k);
    for (register int i = 0; i <= 2000; ++i)
        C[i][0] = 1;
    for (register int i = 1; i <= 2000; ++i) {
        for (register int j = 1; j <= i; ++j)
            ans[i][j] = !(C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % k) + ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1];
        for (register int j = i + 1; j <= 2000; ++j)
            ans[i][j] = ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1];
    }
    while (t--) {
        scanf("%d%d", &n, &m);
        printf("%d\n", ans[n][m]);
    }
    return 0;
}
