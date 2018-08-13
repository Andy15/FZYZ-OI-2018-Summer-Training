#include <bits/stdc++.h>
#define MAXP 100010
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

struct Edge {
    int to;
    Edge *nxt;
};

struct Graph {
    int graph, deg[MAXP];
    Edge *first[MAXP], e[MAXP], *ptr = e;

    inline void insert(register int &u, register int &v) {
	    *ptr = (Edge) {v, first[u]}; first[u] = ptr++; ++deg[v];
    }

	/*
	inline void clr() {
		graph = 0; ptr = e;
		memset(first, 0, sizeof(first)); memset(e, 0, sizeof(0));
	}
	*/
} orz_night;

int n, m, a, b, ans1, ans2[MAXP];
priority_queue<int, vector<int>, greater<int> > heap;

int main() {
    for (MirAc1e::scan(&n), MirAc1e::scan(&m); m; --m) {
        MirAc1e::scan(&a); MirAc1e::scan(&b); orz_night.insert(a, b);
    }
    for (int i = 1; i <= n; ++i)
        (!orz_night.deg[i]) && (heap.push(i), 1);
    while (!heap.empty()) {
        register int cur = ans2[++ans1] = heap.top(); int son; heap.pop();
        for (register Edge *i = orz_night.first[cur]; i; i = i -> nxt)
            !(--orz_night.deg[son = i -> to]) && (heap.push(son), 1);
    }
    if (n != ans1) {
        puts("-1");
        return 0;
    }
    for (register int i = 1; i <= ans1; ++i) {
        MirAc1e::print(ans2[i]); putchar(' ');
    }
    putchar('\n');
    return 0;
}
