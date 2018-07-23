#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

long long n, ans_min, num_max;
const long long p[11] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void solve(register long long p_now, register long long ans_now, register long long num_now) {
	if (p_now > 10)
		return;
	(num_now > num_max) && (num_max = num_now, ans_min = ans_now);
	(num_now == num_max && ans_now < ans_min) && (ans_min = ans_now);
	for (register int i = 1; ans_now * p[p_now] <= n; ++i) {
		ans_now *= p[p_now];
		solve(p_now + 1, ans_now, num_now * (i + 1));
	}
}

int main() {
	while (scanf("%lld", &n) != EOF) {
		ans_min = INF; num_max = -1;
		solve(1, 1, 1);
		printf("%lld\n", ans_min);
	}
	return 0;
}
