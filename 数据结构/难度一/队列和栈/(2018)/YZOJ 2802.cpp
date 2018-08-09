#include <bits/stdc++.h>
#define MAXQ 7100010
#define INF 0x3f3f3f3f
using namespace std;

int n, m, q, u, v, t;
long long que[3][MAXQ], head[3], tail[3];

int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &t);
    for (register int i = 1, i_lim = n + m; i <= i_lim; ++i)
        que[0][i] = que[1][i] = que[2][i] = -INF;
    for (register int i = 1; i <= n; ++i)
        scanf("%lld", &que[0][i]);
    sort(que[0] + 1, que[0] + 1 + n, greater<int>());
    head[0] = head[1] = head[2] = 1;
    for (register int i = 1; i <= m; ++i) {
        register long long tmp1 = -INF, tmp3, tmp4, tmp5;
        register int tmp2;
        for (register int j = 0; j <= 2; ++j)
            (tmp1 < que[j][head[j]]) && (tmp1 = que[j][head[j]], tmp2 = j);
        tmp3 = tmp1 + (i - 1) * q; ++head[tmp2];
        !(i % t) && printf("%lld ", tmp3);
        tmp4 = tmp3 * u / v; tmp5 = tmp3 - tmp4;
        que[1][++tail[1]] = tmp4 - i * q; que[2][++tail[2]] = tmp5 - i * q;
    }
    putchar('\n');
    for (register int i = 1, i_lim = n + m; i <= i_lim; ++i) {
        register long long tmp1 = -INF, tmp3;
        register int tmp2;
        for (register int j = 0; j <= 2; ++j)
            (tmp1 < que[j][head[j]]) && (tmp1 = que[j][head[j]], tmp2 = j);
        tmp3 = tmp1 + m * q; ++head[tmp2];
        !(i % t) && printf("%lld ", tmp3);
    }
    putchar('\n');
    return 0;
}
