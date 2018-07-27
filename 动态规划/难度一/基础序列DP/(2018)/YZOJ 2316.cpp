#include <bits/stdc++.h>
#define MAXN 1010
#define MAXM 210
#define MOD 1000000007
using namespace std;

int n, m, k;
int dp[2][MAXM][MAXM][2] ;
char a[MAXN], b[MAXM];

int main() {
	scanf("%d%d%d%s%s", &n, &m, &k, a + 1, b + 1);
	dp[0][0][0][0] = dp[1][0][0][0] = 1;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			for (register int o = 1; o <= k; ++o) {
				dp[i & 1][j][o][1] = a[i] == b[j] ? ((dp[(i + 1) & 1][j - 1][o][1] + dp[(i + 1) & 1][j - 1][o - 1][0]) % MOD + dp[(i + 1) & 1][j - 1][o - 1][1]) % MOD : 0;
				dp[i & 1][j][o][0] = (dp[(i + 1) & 1][j][o][1] + dp[(i + 1) & 1][j][o][0]) % MOD;
			}
	printf("%d\n", (dp[n & 1][m][k][1] + dp[n & 1][m][k][0]) % MOD);
	return 0;
}
