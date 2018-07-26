#include <bits/stdc++.h>
#define MAXN 2010
#define add(u, v, w) (nxt[++edge] = first[u], first[u] = edge, to[edge] = v, val[edge] = w)
using namespace std;

int n, m, tmp, siz[MAXN];
int edge, first[MAXN], nxt[MAXN << 1], to[MAXN << 1], val[MAXN << 1];
long long dp[MAXN][MAXN];

inline void cmax(register long long &a, register long long b) {
    (a < b) && (a = b);
}

inline int dmin(register int &a, register int &b) {
    return a < b ? a : b;
}

void dfs(register int cur, register int fa, register long long cur_val) {
    register int *s = &siz[cur]; *s = 1;
    for (register int i = first[cur], son; i; i = nxt[i]) {
		if ((son = to[i]) == fa)
			continue;
		dfs(son, cur, val[i]);
		for (register int j = dmin(*s, m); ~j; --j) {
			register long long o = dp[cur][j]; int tmp = m - j;
			for (register int k = dmin(siz[son], tmp); ~k; --k)
				cmax(dp[cur][j + k], o + dp[son][k]);
		}
		*s += siz[son];
	}
    for (register int i = dmin(*s, m), o = tmp - *s; ~i; --i)
		dp[cur][i] += cur_val * (i * (m - i) + (*s - i) * (o + i));
}

int main() {
    scanf("%d%d", &n, &m); tmp = n - m;
    for (register int i = 1; i < n; ++i) {
        int x, y, d;
        scanf("%d%d%d", &x, &y, &d);
        add(x, y, d); add(y, x, d);
    }
    dfs(1, 0, 0);
    printf("%lld\n", dp[1][m]);
    return 0;
}
