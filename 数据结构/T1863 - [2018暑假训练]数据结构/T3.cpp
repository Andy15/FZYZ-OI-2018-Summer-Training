#include <bits/stdc++.h>
#define MAXN 5555
using namespace std;

int n, a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN], d[MAXN], e[MAXN], top, ans;

int main() {
    scanf("%d", &n);
    srand(1626);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= n; ++j)
            a[i][j] = ((rand() & 7) > 0);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= n; ++j)
            b[i][j] = a[i][j] ? b[i][j - 1] + 1 : 0;
    for (register int j = 1; j <= n; ++j) {
        top = 0;
        for (register int i = 1; i <= n; ++i) {
            if (!b[i][j]) {
                top = d[i] = 0;
                continue;
            }
            d[i] = 1;
            while (top && b[i][j] <= b[c[top]][j])
                d[i] += d[c[top--]];
            c[++top] = i;
        }
        top = 0;
        for (register int i = n; i; --i) {
            if (!b[i][j]) {
                top = e[i] = 0;
                continue;
            }
            e[i] = 1;
            while (top && b[i][j] < b[c[top]][j])
                e[i] += e[c[top--]];
            c[++top] = i;
            ans += d[i] * e[i] * b[i][j];
        }
    }
    printf("%d\n", ans);
    return 0;
}
