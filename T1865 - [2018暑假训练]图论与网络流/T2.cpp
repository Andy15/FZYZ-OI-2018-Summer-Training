#pragma GCC optimize(3) // You can't see me.
#include <bits/stdc++.h>
#define MAXN 600010
#define MAXM 300010

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
    	while (ch = getc(), ch >= '0' && ch <= '9' ) *o = *o * 10 + ch - '0';
    	//!f && (*o = -*o); // Signed
    }

    /*
    template<typename P>
    void print(register P o) {
        //o < 0 && (putchar('-'), o = -o); // Signed
        o > 9 && (print(o / 10), 0);
        putchar(o % 10 + '0');
    }
    */

    // Unsigned
    // Call 'fwrite(U, 1, O - U, stdout);' at the end of main().
    template<typename P>
    void print(register P o) {
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

int n, m, cnt, res;

struct Edge {
    int to, val;
    Edge *nxt;
};

struct Graph {
    int graph, fa[MAXN], top[MAXN], dep[MAXN], siz[MAXN], son[MAXN], dis[MAXN], val[MAXN], cnt[MAXN];
    Edge *first[MAXN], e[MAXN], *ptr = e;

    /*
    Graph() {
        graph = 0; ptr = e; memset(first, 0, sizeof(first)); memset(e, 0, sizeof(0));
    }
    */

    inline void insert(register int &u, register int &v, register int &w) {
        *ptr = (Edge) {v, w, first[u]}; first[u] = ptr++;
    }

    void dfs1(register int o) {
        register int nxt, *f = &fa[o], *s = &son[o], *d = &dis[o];
        dep[o] = dep[*f] + 1; siz[o] = 1;
        for (register Edge *i = first[o]; i; i = i -> nxt)
        if (*f != (nxt = i -> to) && !fa[nxt]) {
            fa[nxt] = o; dis[nxt] = *d + i -> val; val[nxt] = i -> val; dfs1(nxt); siz[o] += siz[nxt]; (siz[*s] < siz[nxt]) && (*s = nxt);
        }
    }

    void dfs2(register int o) {
        register int *f = &fa[o];
        o == son[*f] ? top[o] = top[*f] : top[o] = o;
        register int nxt;
        for (register Edge *i = first[o]; i; i = i -> nxt)
            (fa[(nxt = i -> to)] == o) && (dfs2(nxt), 1);
    }

    int query(register int x, register int y) {
        register int a, b;
        while ((a = top[x]) != (b = top[y]))
            dep[a] > dep[b] ? x = fa[a] : y = fa[b];
        return dep[x] < dep[y] ? x : y;
    }
} orz_night;

struct Query {
    int u, v, dis, lca;

    inline bool operator < (const Query &ano) const {
        return dis < ano.dis;
    }
} q[MAXM];

void dfs(register int o) {
    register int *f = &orz_night.fa[o], son, *c = &orz_night.cnt[o];
    for (register Edge *i = orz_night.first[o]; i; i = i -> nxt)
        if ((son = i -> to) != *f) {
            dfs(son); *c += orz_night.cnt[son];
        }
    (*c == cnt) && (cmax(res, orz_night.val[o]), 1);
}

bool check(register int &o) {
    memset(orz_night.cnt, 0, sizeof(orz_night.cnt));
    register int *dis_max = &q[m].dis, i = 0, mid, right = m; cnt = res = 0;
    if (*dis_max <= o)
        return 0;
    while (i <= right)
        q[mid = (i + right) >> 1].dis <= o ? i = mid + 1 : right = mid - 1;
    for (cnt = m - i + 1; i <= m; ++i) {
        ++orz_night.cnt[q[i].u]; ++orz_night.cnt[q[i].v]; orz_night.cnt[q[i].lca] -= 2;
    }
    dfs(1);
    if (!res || *dis_max - res > o)
        return 0;
    return 1;
}

int main() {
    register int left = 0, right = 0; int mid;
    scan(&n); scan(&m);
    for (register int i = 1; i < n; ++i) {
        int a, b, t;
        scan(&a); scan(&b); scan(&t);
        orz_night.insert(a, b, t); orz_night.insert(b, a, t);
        cmax(left, t);
    }
    orz_night.dfs1(1); orz_night.dfs2(1);
    for (register int i = 1; i <= m; ++i) {
        int *u = &q[i].u, *v = &q[i].v, *d = &q[i].dis;
        scan(u); scan(v);
        if (*u == *v) {
            --m;
            continue;
        }
        *d = orz_night.dis[*u] + orz_night.dis[*v] - (orz_night.dis[q[i].lca = orz_night.query(*u, *v)] << 1);
        cmax(right, *d);
    }
    if (!m) {
        putchar('0'); putchar('\n');
        return 0;
    }
    sort(q + 1, q + 1 + m);
    while (left <= right)
        check(mid = (left + right) >> 1) ? right = mid - 1 : left = mid + 1;
    print(left);
    fwrite(U, 1, O - U, stdout);
    return 0;
}
