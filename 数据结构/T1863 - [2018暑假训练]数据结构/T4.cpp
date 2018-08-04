#include <bits/stdc++.h>
#define MAXN 222222
#define LOGN 22
using namespace std;

int n, v[MAXN], lson[MAXN], rson[MAXN], fa[MAXN][LOGN], lans[MAXN], rans[MAXN];

int main() {
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i)
        scanf("%d", &v[i]);
    for (register int i = 1; i <= n; ++i) {
        scanf("%d%d", &lson[i], &rson[i]);
        fa[lson[i]][0] = fa[rson[i]][0] = i;
    }
    for (register int j = 1; (1 << j) <= n; ++j)
        for (register int i = 2; i <= n; ++i)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
    for (register int i = 2; i <= n; ++i) {
        register int cur = i;
        for (register int pos = 0, step = v[i] - 1; step && cur; ++pos, step >>= 1) {
            if (!(step & 1))
                continue;
            cur = fa[cur][pos];
        }
        if (!cur || !fa[cur][0])
            continue;
        lson[fa[cur][0]] == cur && ++lans[fa[cur][0]]; rson[fa[cur][0]] == cur && ++rans[fa[cur][0]];
    }
    for (register int i = 1; i <= n; ++i)
        printf("%d %d\n", lans[i], rans[i]);
    return 0;
}
