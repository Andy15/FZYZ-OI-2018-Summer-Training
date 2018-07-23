#include <bits/stdc++.h>
#define MAXN 110
using namespace std;

struct Edge {
    double x1, x2, y;
    int val;

    inline bool operator < (const Edge &ano) const {
        return y < ano.y;
    }
} a[MAXN << 1];

int n, m, ql, qr, qx;
double b[MAXN << 1], ans;

struct SegTree {
    double c[MAXN << 3];
    int tag[MAXN << 3];

    inline void pushup(register int o, register int l, register int r) {
        (tag[o]) ? (c[o] = b[r + 1] - b[l]) : (c[o] = (l == r) ? (0) : (c[o << 1] + c[o << 1 | 1]));
    }

    void modify(register int o, register int l, register int r) {
        //printf("DEBUG3: %d %d %d.\n", o, l, r);
        if (ql <= l && r <= qr) {
            tag[o] += qx; pushup(o, l, r);
            return;
        }
        register int mid = (l + r) >> 1; (ql <= mid) && (modify(o << 1, l, mid), 1); (qr > mid) && (modify(o << 1 | 1, mid + 1, r), 1);
        pushup(o, l, r);
    }
} c;

int main() {
    for (register int T = 1; scanf("%d", &n) && n; ++T) {
        for (register int i = 1; i <= n; ++i) {
            register double x1, x2, y1, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            a[i] = (Edge) {x1, x2, y1, 1}; a[i + n] = (Edge) {x1, x2, y2, -1};
            b[i] = x1; b[i + n] = x2;
        }
        n <<= 1; sort(a + 1, a + n + 1); sort(b + 1, b + n + 1); m = unique(b + 1, b + 1 + n) - b - 1;
        ans = 0; memset(c.c, 0, sizeof(c.c)); memset(c.tag, 0, sizeof(c.tag));
        for (register int i = 1; i < n; ++i) {
            ql = lower_bound(b + 1, b + 1 + m, a[i].x1) - b;
            qr = lower_bound(b + 1, b + 1 + m, a[i].x2) - b - 1;
            qx = a[i].val;
            //printf("DEBUG1: %d %d %d.\n", ql, qr + 1, qx);
            (ql < qr + 1) && (c.modify(1, 1, m), 1);
            ans += c.c[1] * (a[i + 1].y - a[i].y);
            //printf("DEBUG2: %lf %lf %lf.\n", c.c[1], a[i + 1].y, a[i].y);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n", T, ans);
    }
    return 0;
}
