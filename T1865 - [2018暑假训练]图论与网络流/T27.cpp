#include <bits/extc++.h>
#define MAXN 20010
#define MAXM 40010
using namespace std;
using namespace __gnu_pbds;

namespace MirAc1e {
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
    //#define cmax(a, b) ((a) > (b) && ((a) = (b)))
    //#define dmax(a, b) ((a) > (b) ? (a) : (b))
    //#define cmin(a, b) ((a) < (b) && ((a) = (b)))
    //#define dmin(a, b) ((a) > (b) ? (a) : (b))
    //#define xabs(o) ((o) < 0 ? -(o) : (o))
    #define INF 0x3f3f3f3f
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
    int to, val;
    Edge *nxt;
};

struct Graph {
    int graph;
    Edge *first[MAXN], e[MAXM], *ptr = e;

    inline void insert(register int &u, register int &v, register int &w) {
	    *ptr = (Edge) {v, w, first[u]}; first[u] = ptr++;
    }

	/*
	inline void clr() {
		graph = 0; ptr = e;
		memset(first, 0, sizeof(first)); memset(e, 0, sizeof(0));
	}
	*/
} orz_night;

int n, m, s, t, u, v, w, dis[MAXN];
__gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int> >, thin_heap_tag> que;

int main() {
	for (MirAc1e::scan(&n), MirAc1e::scan(&m), MirAc1e::scan(&s), MirAc1e::scan(&t); m; --m) {
		MirAc1e::scan(&u); MirAc1e::scan(&v); MirAc1e::scan(&w);
		orz_night.insert(u, v, w);
	}
	memset(dis, INF, sizeof(dis)); dis[s] = 0; que.push(make_pair(0, s));
	while (!que.empty()) {
		register int id = que.top().second, val; int son; que.pop();
		for (register Edge *i = orz_night.first[id]; i; i = i -> nxt)
			(dis[(son = i -> to)] > dis[id] + (val = i -> val)) && (que.push(make_pair(dis[son] = dis[id] + val, son)), 1);
	}
	printf("%d", dis[t]);
	return 0;
}
