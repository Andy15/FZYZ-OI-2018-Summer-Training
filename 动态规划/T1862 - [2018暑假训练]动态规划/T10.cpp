#include <bits/stdc++.h>
#define MAXP 10
using namespace std;

int T, n, m, a[MAXP][MAXP], ans;
bool vis[MAXP][MAXP];

inline void cmax(register int &a, register int b) {
    (a < b) && (a = b);
}

void dfs(register int x, register int y, register int cur) {
    if (x > n) {
        cmax(ans, cur);
        return;
    }
    register int x_nxt = x, y_nxt = y + 1;
    (y_nxt > m) && (++x_nxt, y_nxt = 1);
    if (!vis[x - 1][y] && !vis[x][y - 1] && !vis[x - 1][y - 1] && !vis[x - 1][y + 1]) {
        vis[x][y] = 1;
        dfs(x_nxt, y_nxt, cur + a[x][y]);
        vis[x][y] = 0;
    }
    dfs(x_nxt, y_nxt, cur);
}

int main() {
    for (scanf("%d", &T); T; --T) {
        scanf("%d%d", &n, &m);
        for (register int i = 1; i <= n; ++i)
            for (register int j = 1; j <= m; ++j)
                scanf("%d", &a[i][j]);
        ans = 0; dfs(1, 1, 0); printf("%d\n", ans);
    }
    return 0;
}
