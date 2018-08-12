#include <bits/stdc++.h>
#define MAXN 20010
#define MAXM 50010
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

    /*
	template<typename P>
    void print(register P o) {
        o < 0 && (putchar('-'), o = -o);
        o > 9 && (print(o / 10), 0);
        putchar(o % 10 + '0');
    }
	*/
}

struct Edge {
    int to;
    Edge *nxt;
};

struct Graph {
    int graph;
    Edge *first[MAXN], e[MAXM], *ptr = e;

    inline void insert(register int &u, register int &v) {
	    *ptr = (Edge) {v, first[u]};
        first[u] = ptr++;
    }

	inline void clr() {
		graph = 0; ptr = e;
		memset(first, 0, sizeof(first)); memset(e, 0, sizeof(0));
	}
} orz_night;

int T, n, u, v, dfn[MAXN], low[MAXN], dfs_clock, scc_cnt, fa[MAXN], sta[MAXN];

bool find(register int x, register int a) {
	while (fa[x] != a) {
		++sta[x];
		if (sta[x] > 1)
			return 0;
		x = fa[x];
	}
	return 1;
}

bool tarjan(register int u) {
	dfn[u] = low[u] = ++dfs_clock;
	for (register Edge *i = orz_night.first[u]; i; i = i -> nxt) {
		if (dfn[v = i -> to]) {
			(low[u] > dfn[v]) && (low[u] = dfn[v]);
			if (!find(u, v))
				return 0;
		}
		else {
			fa[v] = u;
			if (!tarjan(v))
				return 0;
			(low[u] > low[v]) && (low[u] = low[v]);
		}
	}
	if (low[u] == dfn[u]) {
		++scc_cnt;
		if (scc_cnt > 1)
			return 0;
	}
	return 1;
}

int main() {
	for (MirAc1e::scan(&T); T; --T) {
		dfs_clock = scc_cnt = 0;
		orz_night.clr();
		memset(dfn, 0, sizeof(dfn)); memset(sta, 0, sizeof(sta));
		MirAc1e::scan(&n);
		while (1) {
			MirAc1e::scan(&u); MirAc1e::scan(&v);
			if (!u && !v)
				break;
			orz_night.insert(u, v);
		}
		register bool flag = 1;
		for (register int i = 0; i < n; ++i)
			if (!dfn[i] && !tarjan(i)) {
				puts("NO");
				flag = 0;
				break;
			}
		flag && puts(scc_cnt == 1 ? "YES" : "NO");
	}
	return 0;
}
