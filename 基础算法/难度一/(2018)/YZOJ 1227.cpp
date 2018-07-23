#include <bits/stdc++.h>
#define MAXN 2010
#define max(a, b) (a > b ? a : b)
using namespace std;

#define BASE 10000
#define L 10
struct BigInt {
    int num[L], len;

    BigInt(register int x = 0) { memset(num, 0, sizeof(num)); len = 1; num[1] = x;}

    BigInt operator + (BigInt b) {
        BigInt c; c.len = max(b.len, len);
        for (register int i = 1; i <= c.len; ++i) {
            c.num[i] += num[i] + b.num[i];
            c.num[i + 1] = c.num[i] / BASE;
            c.num[i] %= BASE;
        }
        c.num[c.len + 1] && ++c.len;
        return c;
    }

    void print() {
        printf("%d", num[len]);
        for (register int i = len - 1; i; --i)
            printf("%04d", num[i]);
    }
} dp[MAXN];

int n, m, pri[MAXN];
bool com[MAXN];

int main() {
    scanf("%d", &n); dp[0] = BigInt(1);
    for (register int i = 2; i <= n; ++i) {
		(!com[i]) && (pri[++m] = i);
		for (register int j = 1; j <= m && i * pri[j] <= n; ++j) {
			com[i * pri[j]] = 1;
			if (!(i % pri[j]))
				break;
		}
	}
    for (register int i = 1; i <= m; ++i)
        for (register int j = pri[i], k = j; j <= n; ++j)
            dp[j] = dp[j] + dp[j - k];
    dp[n].print();
    return 0;
}
