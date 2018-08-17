#include <bits/stdc++.h>
#define MAXN 300010
#define N 300000

namespace MirAc1e {
    #define BUF_SIZ 20
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << BUF_SIZ, stdin), S == T) ? 0 : *S++)
    #define cmax(a, b) ((a) < (b) && ((a) = (b)))
    //#define dmax(a, b) ((a) > (b) ? (a) : (b))
    //#define cmin(a, b) ((a) > (b) && ((a) = (b)))
    //#define dmin(a, b) ((a) < (b) ? (a) : (b))
    //#define xabs(o) ((o) < 0 ? -(o) : (o))
    //#define xswap(a, b) ((a) ^= (b) ^= (a) ^= (b))
    //#define INF 0x3f3f3f3f
    //#define EPS 1e-6

    char B[1 << BUF_SIZ], *S = B, *T = B;
    char U[1 << BUF_SIZ], *O = U, K[BUF_SIZ];

    template<typename P>
    void scan(register P &o) {
    	//register char ch, f; // Signed
    	//while (ch = getc(), (ch < '0' || ch > '9') && ch != '-'); // Signed
      register char ch; // Unsigned
    	while (ch = getc(), ch < '0' || ch > '9'); // Unsigned
      o = ch - '0'; // Unsigned
    	//ch == '-' ? o = f = 0 : (o = ch - '0', f = 1); // Signed
    	while (ch = getc(), ch >= '0' && ch <= '9') o = o * 10 + ch - '0';
    	//!f && (o = -o); // Signed
    }

    // Call 'fwrite(U, 1, O - U, stdout);' at the end of main().
    template<typename P>
    void print(register P o) {
        // Commit when 'o != 0' always holds.
        if (!o) {
           *O++ = '0';
           return;
        }
        //(o < 0) && (o = -o, *O++ = '-'); // Signed
        register int T = 0;
        for ( ; o; o /= 10)
            K[++T] = o % 10;
        for ( ; T; *O++ = '0' + K[T--]);
    }
}

using namespace std;
using namespace MirAc1e;

int n, m, w[MAXN], ans[MAXN];
vector<int> query_tot[MAXN], query_up[MAXN], query_down[MAXN];

struct Graph {
    int dep[MAXN], dep_max = 0, tag_cnt[MAXN], tag_up[MAXN], tag_down[MAXN << 1];
    bool vis[MAXN];

    struct Edge {
        int to;
        Edge *nxt;
    } *first[MAXN << 1], e[MAXN << 1], *ptr = e;

    inline void insert(register int &u, register int &v) {
	    *ptr = (Edge) {v, first[u]}; first[u] = ptr++;
    }
} g;

struct Query {
    struct Edge {
        int to, val;
        Edge *nxt;
    } *first[MAXN << 1], e[MAXN << 1], *ptr = e;

    struct Path {
        int s, t, lca, dis;
    } p[MAXN];

    inline void insert(register int &u, register int &v, register int &w) {
	    *ptr = (Edge) {v, w, first[u]}; first[u] = ptr++;
    }
} q;

struct Union_Find_Set {
    int fa[MAXN];

    int find(register int o) {
        register int *f = &fa[o];
        return o == *f ? o : *f = find(*f);
    }

    inline void join(register int p, register int q) {
        fa[p] = q;
    }

    inline void init() {
        for (register int i = 1; i <= n; ++i)
            fa[i] = i;
    }
} ufs;

void tarjan(register int o, register int fa) {
    register int son, lca;
    g.vis[o] = 1;
    cmax(g.dep_max, g.dep[o]);
    for (register Graph::Edge *i = g.first[o]; i; i = i -> nxt) {
        if ((son = i -> to) == fa)
            continue;
        g.dep[son] = g.dep[o] + 1;
        tarjan(son, o);
        ufs.join(son, o);
    }
    for (register Query::Edge *i = q.first[o]; i; i = i -> nxt) {
        if (!g.vis[son = i -> to])
            continue;
        lca = ufs.find(son);
        register int id = i -> val;
        q.p[id].lca = lca;
        q.p[id].dis = g.dep[son] + g.dep[o] - (g.dep[lca] << 1);
    }
}

void dfs1(register int o, register int fa) {
    register int son, dep_son = g.dep[o] + w[o], dep_pre = 0;
    (dep_son <= g.dep_max) && (dep_pre += g.tag_up[dep_son]);
    for (register Graph::Edge *i = g.first[o]; i; i = i -> nxt) {
        if ((son = i -> to) == fa)
            continue;
        dfs1(son, o);
    }
    g.tag_up[g.dep[o]] += g.tag_cnt[o];
    (dep_son <= g.dep_max) && (ans[o] += g.tag_up[dep_son] - dep_pre);
    for (register int i = 0, i_lim = query_up[o].size(); i < i_lim; ++i)
        --g.tag_up[query_up[o][i]];
}

void dfs2(register int o, register int fa) {
    register int son, dep_son = w[o] - g.dep[o] + N, dep_pre = g.tag_down[dep_son];
    for (register Graph::Edge *i = g.first[o]; i; i = i -> nxt) {
        if ((son = i -> to) == fa)
            continue;
        dfs2(son, o);
    }
    for (register int i = 0, i_lim = query_down[o].size(); i < i_lim; ++i)
        ++g.tag_down[query_down[o][i]];
    ans[o] += g.tag_down[dep_son] - dep_pre;
    for (register int i = 0, i_lim = query_tot[o].size(); i < i_lim; ++i)
        --g.tag_down[query_tot[o][i]];
}

int main() {
    scan(n); scan(m);
    for (register int i = 1; i < n; ++i) {
        int x, y; scan(x); scan(y);
        g.insert(x, y); g.insert(y, x);
    }
    for (register int *i = w + 1, *i_lim = w + n; i <= i_lim; ++i)
        scan(*i);
    for (Query::Path *i = q.p + 1, *i_lim = q.p + m; i <= i_lim; ++i) {
        int s, t, id = i - q.p; scan(s); scan(t);
        i -> s = s; i -> t = t;
        q.insert(s, t, id); q.insert(t, s, id);
    }
    g.dep[1] = 1; ufs.init(); tarjan(1, 0);
    for (Query::Path *i = q.p + 1, *i_lim = q.p + m; i <= i_lim; ++i) {
        register int fa = i -> s;
        ++g.tag_cnt[fa]; query_up[i -> lca].push_back(g.dep[fa]);
    }
    dfs1(1, 0);
    for (Query::Path *i = q.p + 1, *i_lim = q.p + m; i <= i_lim; ++i) {
        register int son = i -> t; int val = i -> dis - g.dep[son] + N;
        query_down[son].push_back(val); query_tot[i -> lca].push_back(val);
    }
    dfs2(1, 0);
    for (Query::Path *i = q.p + 1, *i_lim = q.p + m; i <= i_lim; ++i) {
        register int lca = i -> lca;
        w[lca] + g.dep[lca] == g.dep[i -> s] && --ans[lca];
    }
    for (register int *i = ans + 1, *i_lim = ans + n; i <= i_lim; ++i) {
        print(*i); *O++ = ' ';
    }
    *O++ = '\n';
    fwrite(U, 1, O - U, stdout);
	return 0;
}
