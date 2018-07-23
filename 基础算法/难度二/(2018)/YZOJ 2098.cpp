#include <bits/stdc++.h>
#define MAXN 1010
#define SIGMA_SIZE 30
using namespace std;

char now[MAXN];
int n, pre[MAXN], to[MAXN];
long long cnt[SIGMA_SIZE][SIGMA_SIZE];

void solve(register int l, register int r, register long long x) {
	if (l > r)
		return;
	if (l == r) {
		cnt[now[l] - 'A' + 1][0] += x;
		return;
	}
	if (l + 1 == r && now[l] >= 'A' && now[l] <= 'Z' && now[r] >= 'a' && now[r] <= 'z') {
		cnt[now[l] - 'A' + 1][now[r] - 'a' + 1] += x;
		return;
	}
	if (now[l] >= '0' && now[l] <= '9') {
		register long long a = 0;
		register int i;
		for (i = l; now[i] >= '0' && now[i] <= '9'; i++)
			a = a * 10 + now[i] - '0';
		solve(i, r, x * a);
		return;
	}
	for (register int i = l; i <= r; ++i) {
		if (now[i] >= 'A' && now[i] <= 'Z') {
			register int last = i, j;
			register long long a = 0;
			(now[i + 1] >= 'a' && now[i + 1] <= 'z') && (++last);
			for (j = 1; now[last + j] >= '0' && now[last + j] <= '9'; j++)
				a = a * 10 + now[last + j] - '0';
			(j == 1) && (a = 1);
			solve(i, last, a * x);
			i = last + j - 1;
		}
		else if (now[i] == '(') {
			register int last = to[i], j;
			register long long a = 0;
			for (j = 1; now[last + j] >= '0' && now[last + j] <= '9'; j++)
				a = a * 10 + now[last + j] - '0';
			(j == 1 || !a) && (a = 1);
			solve(i + 1, last - 1, a * x);
			i = last + j - 1;
		}
	}
}

int main () {
	memset(pre, -1, sizeof(pre));
	scanf("%d\n", &n);
	for (register int i = 0; i < n; ++i)  {
		gets(now);
		memset(to, -1, sizeof(to));
		register int len = strlen(now), last = -1;
		for (register int i = 0; i < len; ++i) {
			(now[i] == '(') && (pre[i] = last, last = i);
			if (now[i] == ')') {
				to[last] = i;
				while (to[last] > 0)
					last = pre[last];
			}
		}
		solve(0, len - 1, 1);
	}
	for (register int i = 1; i < 27; ++i)
		cnt[i][0] > 0 && printf("%c=%lld\n", 'A' + i - 1, cnt[i][0]);
	for (register int i = 1; i < 27; ++i)
		for (register int j = 1; j < 27; ++j)
			cnt[i][j] > 0 && printf("%c%c=%lld\n", 'A' + i - 1, 'a' + j - 1, cnt[i][j]);
	return 0;
}
