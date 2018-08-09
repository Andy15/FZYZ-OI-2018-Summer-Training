#include <bits/stdc++.h>
#define MAXN 2010
using namespace std;

int n, cnt;
bool vis[MAXN];
bitset<MAXN> f[MAXN];

int main() {
    scanf("%d", &n);
    for (register int i = 1, k; i <= n; ++i) {
        scanf("%d", &k);
        k & 1 && (f[i][i] = f[i][0] = 1);
        for (register int j = 1, t; j <= k; ++j) {
            scanf("%d", &t);
            f[i][t] = 1;
        }
    }
    for (register int i = 1; i <= n; ++i) {
        if (!f[i][i]) {
            for (register int j = i + 1; j <= n; ++j) {
                if (f[j][i]) {
                    swap(f[i], f[j]);
                    break;
                }
            }
        }
        for (register int j = i + 1; j <= n; ++j)
            f[j][i] && (f[j] ^= f[i], 0);
    }
    for (register int i = 1; i <= n; ++i)
        if (!f[i][i] && f[i][0]) {
            puts("Impossible");
            return 0;
        }
    for (register int i = n; ~i; --i) {
        (vis[i] = f[i][0]) && ++cnt;
        for (register int j = i; ~j; --j)
            f[j][i] && (f[j][0] = f[j][0] ^ vis[i]);
    }
    printf("%d\n", cnt);
    for (register int i = 1; i <= n; ++i)
        vis[i] && printf("%d ", i);
    return 0;
}
