#include <bits/stdc++.h>
#define MAXH 10010
using namespace std;

int n, h, dp[MAXH];
bool vis[MAXH];

inline void cmax(register int &a, register int b) {
    (a < b) && (a = b);
}

inline int dmin(register int &a, register int &b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d%d", &n, &h); vis[0] = 1;
    for (register int i = 1, e_cur, h_cur, cur; i <= n; ++i) {
        int hi, ei, ti, binary;
        scanf("%d%d%d", &hi, &ei, &ti); binary = 1;
        while (ti) {
            cur = dmin(ti, binary); h_cur = cur * hi; e_cur = cur * ei; ti -= cur; binary <<= 1;
            if (h < h_cur)
                break;
            for (register int j = h; j >= h_cur; --j) {
                cmax(dp[j], dp[j - h_cur] + e_cur);
                vis[j] |= vis[j - h_cur];
            }
        }
    }
    printf("%d\n%c\n", dp[h], vis[h] ? 'Y' : 'N');
    return 0;
}
