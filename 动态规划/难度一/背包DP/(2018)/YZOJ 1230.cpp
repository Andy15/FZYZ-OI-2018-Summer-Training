#include <bits/stdc++.h>
#define MAXM 10
#define MAXV 1000010
#define idx(a, b, c, d, e) (a + b * base1 + c * base2 + d * base3 + e * base4)
using namespace std;

int n, m, v[MAXM], w[MAXM], dp[MAXV];

inline void cmax(register int &a, register int b) {
    (a < b) && (a = b);
}

int main() {
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= m; ++i)
        scanf("%d", &v[i]);
    register int base1 = v[1] + 1, base2 = base1 * (v[2] + 1), base3 = base2 * (v[3] + 1), base4 = base3 * (v[4] + 1);
    for (register int i = 1; i <= n; ++i) {
        int v_cur; scanf("%d", &v_cur);
        for (register int j = 1; j <= m; ++j)
            scanf("%d", &w[j]);
        for (register int a = v[1], a_lim = w[1]; a >= a_lim; --a)
            for (register int b = v[2], b_lim = w[2]; b >= b_lim; --b)
                for (register int c = v[3], c_lim = w[3]; c >= c_lim; --c)
                    for (register int d = v[4], d_lim = w[4]; d >= d_lim; --d)
                        for (register int e = v[5], e_lim = w[5]; e >= e_lim; --e)
                            cmax(dp[idx(a, b, c, d, e)], dp[idx((a - w[1]), (b - w[2]), (c - w[3]), (d - w[4]), (e - w[5]))] + v_cur);
    }
    printf("%d\n", dp[idx(v[1], v[2], v[3], v[4], v[5])]);
    return 0;
}
