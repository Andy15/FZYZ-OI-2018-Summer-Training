#include <bits/stdc++.h>
#define MAXN 1010
#define SIGMA_SIZE 26
using namespace std;

char str[MAXN], ans[MAXN];
int n, m, dp[MAXN][MAXN];
bool vis[MAXN][MAXN];

#define idx(o) (o - 'a')
struct Automaton {
    int next[MAXN][SIGMA_SIZE];

    void build(register char *s) {
        register int n = strlen(s + 1);
        memset(next[n], -1, sizeof(next[n]));
        for (register int i = n; i; --i) {
            memcpy(next[i - 1], next[i], sizeof(next[i]));
            next[i - 1][idx(s[i])] = i;
        }
    }
} a, b;

void cmax(register int &a, register int b) {
    (a < b) && (a = b);
}

int dfs(register int x, register int y) {
    if (vis[x][y])
        return dp[x][y];
    if (x + y > n)
        return dp[x][y] = (x + y <= n + 1);
    vis[x][y] = 1;
    register int ans = 0;
    for (register int i = 0; i < SIGMA_SIZE; ++i)
        (~a.next[x][i] && ~b.next[y][i]) && (cmax(ans, dfs(a.next[x][i], b.next[y][i])), 1);
    return dp[x][y] = ans + 2;
}

int main() {
    scanf("%s", str + 1); n = strlen(str + 1);
    a.build(str); reverse(str + 1, str + 1 + n); b.build(str);
    register int len = dfs(0, 0), x = 0, y = 0;
    for (register int i = len - 2; i > 0; i -= 2)
        for (register int c = 0; c < SIGMA_SIZE; ++c)
            if (~a.next[x][c] && ~b.next[y][c] && dp[a.next[x][c]][b.next[y][c]] == i) {
                x = a.next[x][c]; y = b.next[y][c]; ans[++m] = c + 'a';
                break;
            }
    for (register int i = 1; i <= m; ++i)
        putchar(ans[i]);
    for (register int i = m - (len & 1); i; --i)
        putchar(ans[i]);
    putchar('\n');
    return 0;
}
