#include <bits/stdc++.h>
#define MAXN 2010
#define MAXM 2010
#define MAXV 310
#define INF 0x3f3f3f3f
#define min(a, b) (a < b ? a : b)
using namespace std;

int n, m, v, e, c[MAXN], d[MAXN], a, b, w, dis[MAXV][MAXV];
double k[MAXN], dp[MAXN][MAXM][2];

int main() {
    memset(dis, INF, sizeof(dis));
    scanf("%d%d%d%d", &n, &m, &v, &e);
    for (register int i = 1; i <= v; ++i)
        dis[i][i] = dis[i][0] = dis[0][i] = 0;
    for (register int i = 1; i <= n; ++i)
        scanf("%d", &c[i]);
    for (register int i = 1; i <= n; ++i)
        scanf("%d", &d[i]);
    for (register int i = 1; i <= n; ++i)
        scanf("%lf", &k[i]);
    for (register int i = 1; i <= e; ++i) {
        scanf("%d%d%d", &a, &b, &w);
        (dis[a][b] > w) && (dis[a][b] = dis[b][a] = w);
    }
    for (register int k = 1, now; k <= v; k++)
        for (register int i = 1; i <= v; i++)
            for (register int j = 1; j <= v; j++)
                (dis[i][j] > (now = dis[i][k] + dis[k][j])) && (dis[i][j] = now);
    for (register int i = 1; i <= n; ++i) {
        dp[i][0][0] = dp[i - 1][0][0] + dis[c[i - 1]][c[i]];
        dp[i][0][1] = INF;
        for (register int j = 1, j_lim = min(m, n); j <= j_lim; ++j) {
            dp[i][j][0] = min(dp[i - 1][j][0]
                            + dis[c[i - 1]][c[i]], // t4 // (0, 0)
                              dp[i - 1][j][1]
                            + dis[d[i - 1]][c[i]] * k[i - 1] // t3
                            + dis[c[i - 1]][c[i]] * (1 - k[i - 1]) // t4 // (1, 0)
                             );
            dp[i][j][1] = min(dp[i - 1][j - 1][0]
                            + dis[c[i - 1]][d[i]] * k[i] // t2
                            + dis[c[i - 1]][c[i]] * (1 - k[i]), // t4 // (0, 1)
                              dp[i - 1][j - 1][1]
                            + dis[d[i - 1]][d[i]] * k[i - 1] * k[i] // t1
                            + dis[c[i - 1]][d[i]] * (1 - k[i - 1]) * k[i] // t2
                            + dis[d[i - 1]][c[i]] * k[i - 1] * (1 - k[i]) // t3
                            + dis[c[i - 1]][c[i]] * (1 - k[i - 1]) * (1 - k[i]) // t4 // (1, 1)
                             );
        }
    }
    register double ans = INF, now;
    for (register int i = 0; i <= m; ++i)
        (ans > (now = min(dp[n][i][0], dp[n][i][1]))) && (ans = now);
    printf("%.2f", ans);
    return 0;
}
