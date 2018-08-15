#include <bits/stdc++.h>
#define MAXN 10010
#define LOGN 20
#define MAXM 50010

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

using namespace std;
using namespace MirAc1e;

int n, m, q;

struct Edge_MST {
	int u, v, w;
    bool vis;

	inline bool operator < (const Edge_MST &ano) const {
		return w < ano.w;
	}
} a[MAXM];

struct Union_Find_Set {
	int fa[MAXN];

	int find(register int &x) {
		return fa[x] != x ? fa[x] = find(fa[x]) : x;
	}

	void join(register int &p, register int &q) {
		fa[find(p)] = find(q);
	}
} orz_night;

struct Edge {
    int to, val;
    Edge *nxt;
};

struct Graph {
    Edge *first[MAXN], e[MAXN], *ptr = e;

    /*
    Graph() {
        memset(first, 0, sizeof(first)); memset(e, 0, sizeof(0)); ptr = e;
    }
    */

    inline void insert(register int &u, register int &v, register int &w) {
        *ptr = (Edge) {v, w, first[u]}; first[u] = ptr++;
    }
} orz_night;

int main() {
    scan(&n); scan(&m);
    for (register int i = 1; i <= m; ++i) {
        scan(&a[i].u); scan(&a[i].v); scan(&a[i].w);
    }
    sort(a + 1, a + 1 + m);
    for (register int i = 1; i <= m; ++i)
        (orz_night.find(a[i].u) != orz_night.find(a[i].v)) && (orz_night.join(a[i].u, a[i].v), a[i].vis = 1);
	return 0;
}
