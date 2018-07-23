#include <bits/stdc++.h>
#define MAXN 110
#define EPS 1e-9
using namespace std;

int m, n, x, y, tot;
bool v[MAXN];
double d[MAXN], s[MAXN];

void dfs(register int t, register int k, register double sum) {
	if (!t && (sum > 0 ? sum : -sum) <= EPS)
		++tot;
	else if (s[m] - s[m - t] <= sum + EPS)
		for (register int x = k; x <= m - t + 1 && s[t + x - 1] - s[x - 1] >= sum - EPS; ++x)
		   	(v[x]) && (dfs(t - 1, x + 1, sum - d[x]), 1);
}

int main() {
	scanf("%d%d%d%d", &n, &m, &x, &y);
	for (register int i = 1; i <= m; ++i) {
		d[i] = (double) 1 / i; s[i] = s[i - 1] + d[i];
	}
	for (register int i = 2; i * i <= m; ++i)
		if (!v[i])
			for (register int j = i + i; j <= m; j += i)
				v[j] = 1;
	for (register int i = 1; i <= 11; ++i)
		v[i] = 1;
	v[25] = v[26] = v[27] = v[32] = v[34] = v[38] = v[39] = v[44] = v[46] = v[49] = v[50] = 0;
	dfs(n, 1, (double) x / y);
	printf("%d\n", tot);
	return 0;
}
