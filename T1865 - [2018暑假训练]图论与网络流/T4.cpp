#include <bits/stdc++.h>
#define MAXN 10010
#define LOGN 20
#define MAXM 100010

namespace MirAc1e {
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
    //#define cmax(a, b) ((a) < (b) && ((a) = (b)))
    //#define dmax(a, b) ((a) > (b) ? (a) : (b))
    #define cmin(a, b) ((a) > (b) && ((a) = (b)))
    #define dmin(a, b) ((a) < (b) ? (a) : (b))
    //#define xabs(o) ((o) < 0 ? -(o) : (o))
    #define xswap(a, b) ((a) ^= (b) ^= (a) ^= (b))
    #define INF 0x3f3f3f3f
    //#define EPS 1e-6

    char B[1 << 26], *S = B, *T = B;
    char U[1 << 22], *O = U, stk[15];

    template<typename P>
    void scan(register P *o) {
    	//register char ch, f; // Signed
    	//while (ch = getc(), (ch < '0' || ch > '9') && ch != '-'); // Signed
        register char ch; // Unsigned
    	while (ch = getc(), ch < '0' || ch > '9'); // Unsigned
        *o = ch - '0'; // Unsigned
    	//ch == '-' ? *o = f = 0 : (*o = ch - '0', f = 1); // Signed
    	while (ch = getc(), ch >= '0' && ch <= '9') *o = *o * 10 + ch - '0';
    	//!f && (*o = -*o); // Signed
    }

    // Unsigned
    // Call 'fwrite(U, 1, O - U, stdout);' at the end of main().
    template<typename P>
    void print(register P o) {
        //(o < 0) && (o = -o, *O++ = '-'); // Signed
        if (o) {
            register int ts = 0;
            for ( ; o; o /= 10)
                stk[++ts] = o % 10;
            for ( ; ts; *O++ = '0' + stk[ts--]);
        }
        else
            *O++ = '0';
        *O++ = '\n';
    }
}

using namespace std;
using namespace MirAc1e;

int n, m, q;

struct Edge_MST {
	int u, v, w;

	inline bool operator < (const Edge_MST &ano) const {
		return w > ano.w;
	}
} a[MAXM];

struct Union_Find_Set {
	int fa[MAXN];

    void init(register int &siz) {
        for (register int i = 1; i <= siz; ++i)
            fa[i] = i;
    }

	int find(register int &x) {
		return fa[x] != x ? fa[x] = find(fa[x]) : x;
	}

	void join(register int &p, register int &q) {
		fa[find(p)] = find(q);
	}
} orz_night;

struct Graph {
    int dep[MAXN], fa[MAXN][LOGN], w_min[MAXN][LOGN];
    bool vis[MAXN];

    struct Edge {
        int to, val;
        Edge *nxt;
    } *first[MAXN], e[MAXM], *ptr = e;

    inline void insert(register int &u, register int &v, register int &w) {
	    *ptr = (Edge) {v, w, first[u]}; first[u] = ptr++;
    }

    void dfs(register int o) {
        register int son, *f = &fa[o][0]; vis[o] = 1;
        for (register Edge *i = first[o]; i; i = i -> nxt) {
            if ((son = i -> to) == *f)
                continue;
            dep[son] = dep[o] + 1; fa[son][0] = o; w_min[son][0] = i -> val; dfs(son);
        }
    }

    void init() {
        for (register int j = 1; (1 << j) <= n; ++j)
            for (register int i = 1; i <= n; ++i) {
                fa[i][j] = fa[fa[i][j - 1]][j - 1];
                w_min[i][j] = dmin(w_min[i][j - 1], w_min[fa[i][j - 1]][j - 1]);
            }
    }

    int lca(register int &a, register int &b) {
        (dep[a] > dep[b]) && (xswap(a, b));
        register int delta_dep = dep[b] - dep[a], w_min_ans = INF;
        for (register int i = 0; (1 << i) <= delta_dep; ++i)
            ((1 << i) & delta_dep) && (cmin(w_min_ans, w_min[b][i]), b = fa[b][i]);
        if (a == b)
            return w_min_ans;
        register int i = 0;
        for ( ; (1 << i) <= dep[a]; ++i);
        for (register int *fa_a, *fa_b; ~i; --i) {
            fa_a = &fa[a][i]; fa_b = &fa[b][i];
            (*fa_a != *fa_b) && (cmin(w_min_ans, w_min[a][i]), cmin(w_min_ans, w_min[b][i]), a = *fa_a, b = *fa_b);
        }
        cmin(w_min_ans, dmin(w_min[a][0], w_min[b][0]));
        return w_min_ans;
    }
} orz_yrt;

int main() {
    scan(&n); scan(&m);
    for (register int i = 1; i <= m; ++i) {
        scan(&a[i].u); scan(&a[i].v); scan(&a[i].w);
    }
    sort(a + 1, a + 1 + m); orz_night.init(n);
    for (register int i = 1; i <= m; ++i) {
        register int *u = &a[i].u, *v = &a[i].v, *w = &a[i].w;
        (orz_night.find(*u) != orz_night.find(*v)) && (orz_night.join(*u, *v),
        orz_yrt.insert(*u, *v, *w), orz_yrt.insert(*v, *u, *w), 1);
    }
    memset(orz_yrt.w_min, INF, sizeof(orz_yrt.w_min));
    for (register int i = 1; i <= n; ++i)
        (!orz_yrt.vis[i]) && (orz_yrt.dfs(i), 1);
    orz_yrt.init();
    for (scan(&q); q; --q) {
        int x, y; scan(&x); scan(&y);
        if (orz_night.find(x) != orz_night.find(y)) {
            *O++ = '-'; *O++ = '1'; *O++ = '\n';
            continue;
        }
        print(orz_yrt.lca(x, y));
    }
    fwrite(U, 1, O - U, stdout);
    return 0;
}
