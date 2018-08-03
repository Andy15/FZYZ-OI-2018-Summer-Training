#include <bits/stdc++.h>
#define MAXN 160
using namespace std;

int n, a[MAXN][MAXN], b[MAXN], c[MAXN][MAXN], top, cur, l[MAXN], r[MAXN], ans;

inline void cmax(register int &a, register int b) {
    (a < b) && (a = b);
}

int main() {
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= n; ++j)
            scanf("%d", &c[i][j]);
    /*
    srand(1626);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= n; ++j)
            c[i][j] = ((rand() & 7) > 0);
    */
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= n; ++j) {
            if (!c[i][j])
                continue;
            a[i][j] = a[i][j - 1] + 1;
        }
    for (register int i = 1, *x = a[1]; i <= n; ++i, x = a[i]) {
        top = 0;
        for (register int j = 1, j_lim = n + 1; j <= j_lim; ++j) {
            while (x[cur = b[top--]] > x[i])
                r[cur] = i;
            l[i] = b[top];
            b[++top] = i;
        }
        for (register int i = 1; i <= n; ++i)
            cmax(ans, x[i] * (r[i] - l[i] - 1));
    }
    printf("%d\n", ans);
    return 0;
}
