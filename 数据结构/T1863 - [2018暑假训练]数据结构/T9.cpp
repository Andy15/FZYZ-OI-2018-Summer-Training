#include <bits/stdc++.h>
#define MAXN 200010
using namespace std;

namespace MirAc1e {
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
    //#define cmax(a, b) ((a) > (b) && ((a) = (b)))
    #define dmax(a, b) ((a) > (b) ? (a) : (b))
    //#define cmin(a, b) ((a) < (b) && ((a) = (b)))
    //#define dmin(a, b) ((a) > (b) ? (a) : (b))
    //#define abs(o) ((o) < 0 ? -o : o)
    //#define INF 0x3f3f3f3f
    //#define EPS 1e-6

    char B[1 << 15], *S = B, *T = B;

    template<typename P>
    void scan(register P *o) {
    	register char ch, f;
    	while (ch = getc(), (ch < '0' || ch > '9') && ch != '-');
    	ch == '-' ? *o = f = 0 : (*o = ch - '0', f = 1);
    	while (ch = getc(), ch >= '0' && ch <= '9' ) *o = *o * 10 + ch - '0';
    	!f && (*o = -*o);
    }

    template<typename P>
    void print(register P o) {
        o < 0 && (putchar('-'), o = -o);
        o > 9 && (print(o / 10), 0);
        putchar(o % 10 + '0');
    }
}

int n, a[MAXN], m, cmd, x, y;

struct Segment_Tree {
    struct Info {
        long long ans, sum, lef, rig;

        inline Info operator + (const Info &ano) const {
            return (Info) {dmax(dmax(ans, ano.ans), rig + ano.lef), sum + ano.sum, dmax(lef, sum + ano.lef), dmax(ano.rig, rig + ano.sum)};
        }
    } s[MAXN << 2];

    void build(register int o, register int l, register int r) {
        if (l == r) {
            s[o] = (Info) {a[l], a[l], a[l], a[l]};
            return;
        }
        register int mid = (l + r) >> 1;
        build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
        s[o] = s[o << 1] + s[o << 1 | 1];
    }

    /*
    void update(register int o, register int l, register int r) {
        if (l == r) {
            s[o] = (Info) {y, y, y, y};
            return;
        }
        register int mid = (l + r) >> 1;
        (x <= mid) ? (update(o << 1, l, mid), 1) : (update(o << 1 | 1, mid + 1, r), 1);
        s[o] = s[o << 1] + s[o << 1 | 1];
    }
    */

    Info query(register int o, register int l, register int r) {
        if (x <= l && r <= y)
            return s[o];
        register int mid = (l + r) >> 1;
        if (y <= mid)
            return query(o << 1, l, mid);
        else if (x > mid)
            return query(o << 1 | 1, mid + 1, r);
        else
            return query(o << 1, l, mid) + query(o << 1 | 1, mid + 1, r);
        /*
        static Info ans = (Info) {-INF, 0, -INF, -INF};
        (x <= mid) && (ans = ans + query(o << 1, l, mid), 1);
        (mid < y) && (ans = ans + query(o << 1 | 1, mid + 1, r), 1);
        return ans;
        */
    }
} orz_night;

int main() {
    MirAc1e::scan(&n);
    for (register int i = 1; i <= n; ++i)
        MirAc1e::scan(&a[i]);
    orz_night.build(1, 1, n);
    for (MirAc1e::scan(&m); m; --m) {
        MirAc1e::scan(&x); MirAc1e::scan(&y); MirAc1e::print(orz_night.query(1, 1, n).ans); putchar('\n');
    }
    return 0;
}
