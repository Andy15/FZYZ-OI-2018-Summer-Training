#include <bits/stdc++.h>
#define MAXN 30
using namespace std;

int T, n, m, k, ans, vis[MAXN];
bool suc, sam[MAXN], vis2[MAXN];
struct P {
	int a, b;
} a[MAXN];

inline bool cmp(register P x, register P y) {
	return y.a * y.b < x.a * x.b || (y.a * y.b == x.a * x.b && x.a < y.a);
}

int get() {
	register int tmp = 0;
	for (register int i = 1; i <= n; ++i)
		(vis[i] != m && vis[i] != vis[i - 1]) && (++tmp);
	return tmp;
}

bool check() {
	for	(register int i = 1; i <= n; ++i)
		if (vis[i] != m)
			return 0;
	return 1;
}

void dfs(register int dep) {
	if (ans <= dep + get())
		return;
	if (check()) {
		suc = 1; ans = dep;
		return;
	}
	register int max_vis = vis[1], choose = 1, lm = 0;
	for (register int i = 2; i <= n; ++i)
		(vis[i] < max_vis) && (max_vis = vis[i], choose = i);
	for (register int i = choose; i <= n && vis[i] == max_vis; ++i)
		++lm;
	register int wm = m - max_vis;
	for (register int i = 0; i < k; ++i) {
		if (!vis2[i] && (!sam[i] || vis2[i - 1]) && a[i].a <= lm && a[i].b <= wm) {
			for (register int j = 0; j < a[i].a; ++j)
				vis[choose + j] += a[i].b;
			vis2[i] = 1;
			dfs(dep + 1);
			for(register int j = 0; j < a[i].a; ++j)
				vis[choose + j] -= a[i].b;
			vis2[i] = 0;
		}
	}
}

int main() {
	for (scanf("%d", &T); T; --T) {
		scanf("%d%d%d", &n, &m, &k);
		for (register int i = 0; i < k; ++i)
			scanf("%d%d", &a[i].a, &a[i].b);
		sort(a, a + n, cmp);
		for (register int i = 1; i < k; ++i)
			sam[i] = a[i].a == a[i - 1].a && a[i].b == a[i - 1].b;
		ans = k + 1; suc = 0; dfs(0);
		printf(suc ? "%d\n" : "-1\n", ans);
	}
	return 0;
}
