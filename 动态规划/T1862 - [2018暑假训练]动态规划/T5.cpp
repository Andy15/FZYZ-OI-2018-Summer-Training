#include <bits/stdc++.h>
#define MAXN 100010
#define BIN 16
#define add(u, v, w) (nxt[++edge] = first[u], first[u] = edge, to[edge] = v, val[edge] = w)
using namespace std;

int n, m, f[MAXN][BIN], g[MAXN], h[BIN];
int edge, first[MAXN], to[MAXN << 1], nxt[MAXN << 1], val[MAXN << 1];

void dfs1(register int cur, register int fa) {
    register int *f_cur = f[cur], *g_cur = &g[cur];
    for (register int i = first[cur], *f_son, son, val_cur; i; i = nxt[i]) {
        if ((son = to[i]) == fa)
            continue;
        f_son = &f[son][0];
        dfs1(son, cur);
        ++f_cur[(val_cur = val[i]) & 15]; *g_cur += g[son] + (val_cur >> 4);
        for (register int j = 0, k = val_cur; j < BIN; ++j, ++k, ++f_son) {
            f_cur[k & 15] += *f_son; *g_cur += (k >> 4) * *f_son;
        }
    }
}

void dfs2(register int cur, register int fa) {
    register int *f_cur = f[cur], *g_cur = &g[cur];
    for (register int i = first[cur], g_tmp, son, son_val, *f_son_1, *f_son_2, *g_son; i; i = nxt[i]) {
        if ((son = to[i]) == fa)
            continue;
        f_son_1 = f_son_2 = &f[son][0]; g_son = &g[son];
        g_tmp = *g_cur - *g_son;
        for (register int j = 0, k = (son_val = val[i]); j < BIN; ++j, ++k, ++f_son_1) {
            g_tmp -= (k >> 4) * *f_son_1; h[k & 15] = f_cur[k & 15] - *f_son_1;
        }
        ++f_son_2[son_val & 15]; *g_son += g_tmp; --h[son_val & 15];
        for (register int j = 0, k = son_val, *h_son = h; j < BIN; ++j, ++k, ++h_son) {
            f_son_2[k & 15] += *h_son; *g_son += (k >> 4) * *h_son;
        }
        dfs2(to[i], cur);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (register int i = 1; i < n; ++i) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c); add(a, b, c);
    }
    dfs1(1, 0); dfs2(1, 0);
    for (register int i = 1, *dp; i <= n; ++i) {
		register long long ans = g[i] << 4; dp = f[i];
		for (register int j = 0; j < BIN; ++j)
            ans += (j ^ m) * dp[j];
		printf("%lld\n", ans);
	}
    return 0;
}
