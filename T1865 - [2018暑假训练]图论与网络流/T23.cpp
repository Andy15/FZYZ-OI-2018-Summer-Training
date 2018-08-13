#include <bits/stdc++.h>
#define MAXN 20010
using namespace std;

namespace MirAc1e {
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
    //#define cmax(a, b) ((a) > (b) && ((a) = (b)))
    //#define dmax(a, b) ((a) > (b) ? (a) : (b))
    //#define cmin(a, b) ((a) < (b) && ((a) = (b)))
    //#define dmin(a, b) ((a) > (b) ? (a) : (b))
    //#define xabs(o) ((o) < 0 ? -(o) : (o))
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

int T, n;
long long ans;

struct Union_Find_Set {
	int fa[MAXN], siz[MAXN];

	int find(register int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}

	void join(register int p, register int q) {
		p = find(p); q = find(q);
		fa[p] = q; siz[q] += siz[p];
	}

	inline void clr(register int &n) {
		memset(fa, 0, sizeof(fa)); memset(siz, 0, sizeof(siz));
		for (register int i = 1; i <= n; ++i) {
			fa[i] = i; siz[i] = 1;
		}
	}
} orz_night;

struct Edge {
    int u, v, w;

    inline bool operator < (const Edge &ano) const {
        return w < ano.w;
    }
} a[MAXN];

int main() {
    for (MirAc1e::scan(&T); T; --T) {
        MirAc1e::scan(&n);
	    ans = 0;
		orz_night.clr(n);
		memset(a, 0, sizeof(a));
        for (register int i = 1; i < n; ++i) {
            MirAc1e::scan(&a[i].u);
			MirAc1e::scan(&a[i].v);
			MirAc1e::scan(&a[i].w);
			ans += a[i].w;
        }
        sort(a + 1, a + n);
        for (register int i = 1, x, y, z; i < n; ++i) {
            x = orz_night.find(a[i].u);
			y = orz_night.find(a[i].v);
			z = a[i].w;
            ans += ((long long) orz_night.siz[x] * orz_night.siz[y] - 1) * (z + 1);
			orz_night.join(a[i].u, a[i].v);
        }
        MirAc1e::print(ans);
		putchar('\n');
    }
    return 0;
}
