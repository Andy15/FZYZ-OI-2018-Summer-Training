#include <bits/stdc++.h>
#define MAXN 30
#define abs(o) ((o) < 0 ? -(o) : (o))
#define max(a, b) ((a) > (b) ? (a) : (b))
using namespace std;

int d, n, ans, cnt, x[MAXN], y[MAXN], k[MAXN];

int main() {
	scanf("%d%d", &d, &n);
	for (register int i = 1; i <= n; ++i)
		scanf("%d%d%d", &x[i], &y[i], &k[i]);
	for (register int i = 0; i <= 128; ++i)
		for (register int j = 0; j <= 128; ++j) {
			register int tmp = 0;
			for (register int o = 1; o <= n; ++o)
				(max(abs(i - x[o]), abs(j - y[o])) <= d) && (tmp += k[o]);
			(tmp > ans) ? (ans = tmp, cnt = 1) : (tmp == ans && ++cnt);
		}
	printf("%d %d", cnt, ans);
	return 0;
}
