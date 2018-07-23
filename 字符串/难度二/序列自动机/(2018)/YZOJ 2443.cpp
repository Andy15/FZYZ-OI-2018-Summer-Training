#include <bits/stdc++.h>
#define MAXS 5010
#define SIGMA_SIZE 26
#define MOD 1000000007
#define idx(o) (o - 'a')
using namespace std;

char s[MAXS];
int n, next1[MAXS][SIGMA_SIZE], next2[MAXS][SIGMA_SIZE], dp[MAXS][MAXS];

int dfs(register int a, register int b) {
    if (dp[a][b])
        return dp[a][b];
    for (register int i = 0; i < SIGMA_SIZE; ++i)
        if (next1[a][i] && next2[b][i]) {
            if (next1[a][i] + next2[b][i] > n + 1)
                continue;
            next1[a][i] + next2[b][i] < n + 1 && ++dp[a][b];
            dp[a][b] = (dp[a][b] + dfs(next1[a][i], next2[b][i])) % MOD;
        }
    return ++dp[a][b];
}

int main() {
    scanf("%s", s + 1); n = strlen(s + 1);
    for (register int i = n; i; --i) {
        for (register int j = 0; j < SIGMA_SIZE; ++j)
            next1[i - 1][j] = next1[i][j];
        next1[i - 1][idx(s[i])] = i;
    }
    reverse(s + 1, s + 1 + n);
    for (register int i = n; i; --i) {
        for (register int j = 0; j < SIGMA_SIZE; ++j)
            next2[i - 1][j] = next2[i][j];
        next2[i - 1][idx(s[i])] = i;
    }
    printf("%d\n", dfs(0, 0));
    return 0;
}
