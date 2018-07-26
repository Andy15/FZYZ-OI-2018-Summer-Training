#include <bits/stdc++.h>
#define MAXN 100010
#define BIN 16
#define add(u, v, w) (nxt[++edge] = first[u], first[u] = edge, to[edge] = v, val[edge] = w)
using namespace std;

int n, m, f[MAXN][BIN], g[MAXN], h[BIN];
int edge, first[MAXN], to[MAXN << 1], nxt[MAXN << 1], val[MAXN << 1];

void dfs1(register int cur, register int fa) {
    for (register int i = first[cur], son, son_val; i; i = nxt[i]) {
        if ((son = to[i]) == fa)
            continue;
        dfs1(son, cur);
        ++f[cur][(son_val = val[i]) & 15]; g[cur] += g[son] + (son_val >> 4);
        for (register int j = 0, k, o; j < BIN; ++j) {
            k = j + son_val; o = f[son][j];
            f[cur][k & 15] += o; g[cur] += (k >> 4) * o;
        }
    }
}

void dfs2(register int cur, register int fa) {
    for (register int i = first[cur], son, son_val, son_and, g_cur, *ff, *gg; i; i = nxt[i]) {
        if ((son = to[i]) == fa)
            continue;
        ff = &f[son][son_and = son_val & 15]; gg = &g[son]; g_cur = g[cur] - *gg;
        for (register int j = 0, k = son_val = val[i], o, p; j < BIN; ++j, ++k) {
            o = f[son][j]; p = k & 15;
            g_cur -= (k >> 4) * o; h[p] = f[cur][p] - o;
        }
        ++*ff; *gg += g_cur; --h[son_and];
        for (register int j = 0, k = son_val, tmp; j < BIN; ++j, ++k) {
            f[son][k & 15] += (tmp = h[j]); *gg += (k >> 4) * tmp;
        }
        dfs2(son, cur);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (register int i = 1; i < n; ++i) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c); add(a, b, c);
    }
    dfs1(1, 0); dfs2(1, 0);
    for (register int i = 1; i <= n; ++i) {
		register long long ans = g[i] << 4;
		for (register int j = 0; j < BIN; ++j)
            ans += (j ^ m) * f[i][j];
		printf("%lld\n", ans);
	}
    return 0;
}
