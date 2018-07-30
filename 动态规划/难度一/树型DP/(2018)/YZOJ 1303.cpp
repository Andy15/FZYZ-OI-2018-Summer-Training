#include <bits/stdc++.h>
#define MAXN 100010
using namespace std;

int n, l[MAXN], r[MAXN], dp[MAXN][2], ans;

int dfs(register int now) {
    if (!now)
        return 0;
    register int ansl = dfs(l[now]), ansr = dfs(r[now]);
    (ansl + ansr + 1 > ans) && (ans = ansl + ansr + 1);
    return ansl > ansr ? ansl + 1 : ansr + 1;
}

int main() {
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i)
        scanf("%d%d", &l[i], &r[i]);
    dfs(1);
    printf("%d", ans - 1);
    return 0;
}
