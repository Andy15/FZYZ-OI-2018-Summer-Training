#include <bits/stdc++.h>
#define MAXN 3020
#define SIGMA 60
#define conchar(x) (x >= 'a' && x <= 'z') ? (x - 'a' + 26) : (x - 'A')
#define conint(x) (x < 26) ? (x + 'A') : (x - 26 + 'a')
using namespace std;

int m, n, k, nexta[MAXN][SIGMA], nextb[MAXN][SIGMA], anslen;
long long anscnt, dp[MAXN][MAXN];
char a[MAXN], b[MAXN], ans[MAXN];
bool vis[MAXN][MAXN];

void dfs1(register int a, register int b) {
    for (register int i = 1; i <= anslen; ++i)
        putchar(ans[i]);
    putchar('\n'); ++anscnt;
    for (register int i = 0; i < 52; ++i)
        if (nexta[a][i] && nextb[b][i]) {
            ans[++anslen] = conint(i);
            dfs1(nexta[a][i], nextb[b][i]);
            --anslen;
        }
}

long long dfs2(register int a, register int b) {
    if (vis[a][b]) return dp[a][b];
    register int dpnow = 1;
    vis[a][b] = 1;
    for (register int i = 0; i <= 52; ++i)
        (nexta[a][i] && nextb[b][i]) && (dpnow += dfs2(nexta[a][i], nextb[b][i]));
    return dp[a][b] = dpnow;
}

int main() {
    scanf("%d %d %s %s %d", &m, &n, a + 1, b + 1, &k);
    for (register int i = 0; i < m; ++i)
        for (register int j = i + 1; j <= m; ++j)
            (!nexta[i][conchar(a[j])]) && (nexta[i][conchar(a[j])] = j);
    for (register int i = 0; i < n; ++i)
        for (register int j = i + 1; j <= n; ++j)
            (!nextb[i][conchar(b[j])]) && (nextb[i][conchar(b[j])] = j);
    k ? dfs1(0, 0), printf("%lld", anscnt) : printf("%lld", dfs2(0, 0));
    return 0;
}
