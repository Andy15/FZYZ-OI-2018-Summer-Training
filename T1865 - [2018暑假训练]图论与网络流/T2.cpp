#include <bits/stdc++.h>
#define MAXN 600010
#define MAXM 300010

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

int n, m, l, mid, r, cnt, res;

struct Graph {
    int fa[MAXN], val[MAXN], cnt[MAXN], dep[MAXN];
    bool vis[MAXN];

    struct Edge {
        int to, val;
        Edge *nxt;
    } *first[MAXN], e[MAXN], *ptr = e;

    inline void insert(register int &u, register int &v, register int &w) {
        *ptr = (Edge) {v, w, first[u]}; first[u] = ptr++;
    }
} g;

struct Query {
    struct Edge {
        int to, val;
        Edge *nxt;
    } *first[MAXM << 1], e[MAXM << 1], *ptr = e;

    struct Path {
        int s, t, lca, dis;

        inline bool operator < (const Path &ano) const {
            return dis < ano.dis;
        }
    } p[MAXM];

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
    for (register Graph::Edge *i = g.first[o]; i; i = i -> nxt) {
        if ((son = i -> to) == fa)
            continue;
        g.fa[son] = o;
        g.dep[son] = g.dep[o] + (g.val[son] = i -> val);
        tarjan(son, o);
        ufs.join(son, o);
    }
    for (register Query::Edge *i = q.first[o]; i; i = i -> nxt) {
        if (!g.vis[son = i -> to])
            continue;
        lca = ufs.find(son);
        register int id = i -> val, *d = &q.p[id].dis;
        q.p[id].lca = lca;
        *d = g.dep[son] + g.dep[o] - (g.dep[lca] << 1);
        cmax(r, *d);
    }
}

void dfs(register int o) {
    register int *f = &g.fa[o], son, *c = &g.cnt[o];
    for (register Graph::Edge *i = g.first[o]; i; i = i -> nxt)
        if ((son = i -> to) != *f) {
            dfs(son); *c += g.cnt[son];
        }
    (*c == cnt) && (cmax(res, g.val[o]), 1);
}

bool check(register int &o) {
    memset(g.cnt, 0, sizeof(g.cnt));
    register int *dis_max = &q.p[m].dis, i = 0, mid, right = m; cnt = res = 0;
    if (*dis_max <= o)
        return 0;
    while (i <= right)
        q.p[mid = (i + right) >> 1].dis <= o ? i = mid + 1 : right = mid - 1;
    for (cnt = m - i + 1; i <= m; ++i) {
        ++g.cnt[q.p[i].s]; ++g.cnt[q.p[i].t]; g.cnt[q.p[i].lca] -= 2;
    }
    dfs(1);
    if (!res || *dis_max - res > o)
        return 0;
    return 1;
}

int main() {
    scan(n); scan(m);
    for (register int i = 1; i < n; ++i) {
        int a, b, t;
        scan(a); scan(b); scan(t);
        g.insert(a, b, t); g.insert(b, a, t);
        cmax(l, t);
    }
    for (int i = 1; i <= m; ++i) {
        int *u = &q.p[i].s, *v = &q.p[i].t;
        scan(*u); scan(*v);
        if (*u == *v) {
            --m; --i;
            continue;
        }
        q.insert(*u, *v, i); q.insert(*v, *u, i);
    }
    g.dep[1] = 1; ufs.init(); tarjan(1, 0);
    if (!m) {
        putchar('0'); putchar('\n');
        return 0;
    }
    sort(q.p + 1, q.p + 1 + m);
    while (l <= r)
        check(mid = (l + r) >> 1) ? r = mid - 1 : l = mid + 1;
    print(l);
    fwrite(U, 1, O - U, stdout);
    return 0;
}
