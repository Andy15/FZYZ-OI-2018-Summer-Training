#include <bits/stdc++.h>
#define MAXN 10010
#define MAXK 12010
#define MAXM 12010
using namespace std;

int n, k, m, fa[MAXN], siz[MAXN];
struct E {
	int u, v, w;

	inline bool operator < (const E &ano) const {
		return w < ano.w;
	}
} a[MAXK + MAXM];

int find(register int x) {
	return fa[x] != x ? fa[x] = find(fa[x]) : x;
}

void join(register int p, register int q) {
	p = find(p); q = find(q);
	if (p == q)
		return;
	if (siz[p] < siz[q]) {
		fa[p] = find(q);
		return;
	}
	siz[p] == siz[q] && ++siz[p];
	fa[q] = find(p);
}

int kruskal() {
	register int sum = 0;
	for (register int i = 0, i_lim = k + m; i < i_lim; ++i)
		find(a[i].u) != find(a[i].v) && (join(a[i].u, a[i].v), sum += a[i].w);
	return sum;
}

int main() {
	scanf("%d%d%d", &n, &k, &m);
	for (register int i = 0; i < k; ++i) {
		scanf("%d%d", &a[i].u, &a[i].v); a[i].w = 0;
	}
	for (register int i = k, i_lim = k + m; i < i_lim; ++i) {
		scanf("%d%d", &a[i].u, &a[i].v); a[i].w = 1;
	}
	for (register int i = 1; i <= n; ++i) {
		fa[i] = i;
		siz[i] = 1;
	}
	sort(a, a + k + m);
	printf("%d", kruskal());
	return 0;
}
