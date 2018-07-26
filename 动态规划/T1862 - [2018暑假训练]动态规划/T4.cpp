#include <bits/stdc++.h>
#define MAXN 100010
#define dmax(a, b) (a < b ? b : a)
#define add(u, v) (nxt[++edge] = first[u], first[u] = edge, to[edge] = v)
using namespace std;

int n, k, f[MAXN], g[MAXN];
int edge, first[MAXN], nxt[MAXN << 1], to[MAXN << 1];

void dfs1(register int cur, register int fa) {
	for (register int i = first[cur], son; i; i = nxt[i]) {
		if ((son = to[i]) == fa)
            continue;
		dfs1(son, cur);
		f[cur] += g[son]; g[cur] += dmax(f[son], g[son]);
	}
	++f[cur];
}

void dfs2(register int cur, register int fa, register int grdfa) {
	register int g_son = 0;
	for (register int i = first[cur], son; i; i = nxt[i]) {
		if ((son = to[i]) == fa)
            continue;
		dfs2(son, cur, fa);
		g[cur] += g[son]; g_son = dmax(g_son, f[son] - g[son]);
		for (register int j = first[son], grdson; j; j = nxt[j]) {
			if ((grdson = to[j]) == cur || grdson == grdfa)
                continue;
			f[cur] += g[grdson];
		}
	}
	++f[cur]; g[cur] += g_son;
}

int main() {
    scanf("%d %d", &n, &k);
	for (register int i = 1, u, v; i < n; ++i) {
        scanf("%d %d", &u, &v);
		add(u, v); add(v, u);
	}
    (k == 1) ? (dfs1(1, 0), 1) : (dfs2(1, 0, 0), 1);
	printf("%d\n", dmax(f[1], g[1]));
	return 0;
}
