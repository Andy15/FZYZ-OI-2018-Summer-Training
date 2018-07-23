#include <bits/stdc++.h>
#define MAXN 30010
#define MAXL 210
#define BASE 131
using namespace std;

int n, l, s, tmp, ans;
char str[MAXN][MAXL];
unsigned long long a[MAXN], power[MAXL], h[MAXN];

int main() {
    power[0] = 1;
    for (register int i = 1; i <= 200; ++i)
        power[i] = power[i - 1] * BASE;
    scanf("%d%d%d", &n, &l, &s);
    for (register int i = 1; i <= n; ++i)
        scanf("%s", str[i] + 1);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= l; ++j)
            h[i] = h[i] * BASE + str[i][j];
    for (register int j = 1; j <= l; ++j) {
        for (register int i = 1; i <= n; ++i)
            a[i] = h[i] - str[i][j] * power[l - j];
        sort(a + 1, a + 1 + n);
        for (register int i = 1, i_lim = n + 1; i <= i_lim; ++i)
            (a[i] == a[i - 1]) ? (++tmp) : (ans += (tmp * (tmp - 1)) >> 1, tmp = 1);
        ans += (tmp * (tmp - 1)) >> 1, tmp = 1;
    }
    printf("%d\n", ans);
    return 0;
}
