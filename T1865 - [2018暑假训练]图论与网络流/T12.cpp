#include <bits/stdc++.h>
#define MAXP 100010
using namespace std;

namespace MirAc1e {
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
    #define cmax(a, b) ((a) < (b) && ((a) = (b)))
    //#define dmax(a, b) ((a) > (b) ? (a) : (b))
    //#define cmin(a, b) ((a) > (b) && ((a) = (b)))
    //#define dmin(a, b) ((a) < (b) ? (a) : (b))
    //#define xabs(o) ((o) < 0 ? -(o) : (o))
    //#define xswap(a, b) ((a) ^= (b) ^= (a) ^= (b))
    //#define INF 0x3f3f3f3f
    //#define EPS 1e-6

    char B[1 << 15], *S = B, *T = B;

    template<typename P>
    void scan(register P *o) {
    	//register char ch, f; // Signed
    	//while (ch = getc(), (ch < '0' || ch > '9') && ch != '-'); // Signed
        register char ch; // Signed
    	while (ch = getc(), ch < '0' || ch > '9'); // Unsigned
        *o = ch - '0'; // Unsigned
    	//ch == '-' ? *o = f = 0 : (*o = ch - '0', f = 1); // Signed
    	while (ch = getc(), ch >= '0' && ch <= '9' ) *o = *o * 10 + ch - '0';
    	//!f && (*o = -*o); // Signed
    }

    template<typename P>
    void print(register P o) {
        //o < 0 && (putchar('-'), o = -o); // Signed
        o > 9 && (print(o / 10), 0);
        putchar(o % 10 + '0');
    }
}

int n, l, m, ans;
bool vis[MAXP];

struct Edge {
	int u, v, w, id;

	inline bool operator < (const Edge &ano) const {
		return w < ano.w;
	}
} a[MAXP << 1], b[MAXP];

struct Union_Find_Set {
	int fa[MAXP];

	int find(register int &x) {
		return fa[x] != x ? fa[x] = find(fa[x]) : x;
	}

	void join(register int &p, register int &q) {
		fa[find(p)] = find(q);
	}
} orz_night;

int main() {
	MirAc1e::scan(&n); MirAc1e::scan(&l); MirAc1e::scan(&m);
	for (register int i = 1; i <= m; ++i) {
		MirAc1e::scan(&a[i].u); MirAc1e::scan(&a[i].v); MirAc1e::scan(&a[i].w); MirAc1e::scan(&a[i + m].w);
		a[i].id = i; b[i] = a[i]; a[i + m].u = a[i].u; a[i + m].v = a[i].v;
	}
	for (register int i = 1; i <= n; ++i)
		orz_night.fa[i] = i;
	sort(a + 1, a + 1 + (m << 1)); sort(b + 1, b + 1 + m);
	register int cnt = 0;
	for (register int i = 1; cnt < l; ++i)
		orz_night.find(b[i].u) != orz_night.find(b[i].v) && (orz_night.join(b[i].u, b[i].v), cmax(ans, b[i].w), vis[b[i].id] = 1, ++cnt);
	for (register int i = 1, i_lim = m << 1; i <= i_lim; ++i) {
		if (vis[a[i].id])
			continue;
		orz_night.find(a[i].u) != orz_night.find(a[i].v) && (orz_night.join(a[i].u, a[i].v), cmax(ans, a[i].w), 1);
	}
	MirAc1e::print(ans); putchar('\n');
	return 0;
}
