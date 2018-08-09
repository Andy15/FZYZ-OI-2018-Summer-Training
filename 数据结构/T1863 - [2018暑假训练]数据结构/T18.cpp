#include <bits/stdc++.h>
#define MAXN 100010
#define swap(a, b) (a ^= b ^= a ^= b)
#define max(a, b) (a > b ? a : b)
using namespace std;

int n, m, b, c[MAXN], l[MAXN], i;
long long ans;

struct Edge {
    int to;
    Edge *nxt;
};

struct Graph {
    int graph, root[MAXN];
    long long sum[MAXN], siz[MAXN];
    Edge *first[MAXN];

    inline void insert(register int &u, register int &v) {
        static Edge e[MAXN], *ptr = e;
	    *ptr = (Edge) {v, first[u]};
        first[u] = ptr++;
    }
} orz_yrt;

struct Skew_Heap {
    int l[MAXN], r[MAXN], val[MAXN];

    int merge(register int &x, register int &y) {
        if (!x || !y)
            return x + y;
        (val[x] < val[y]) && (swap(x, y));
        r[x] = merge(r[x], y);
        swap(l[x], r[x]);
        return x;
    }

    inline void pop(register int &x) {
        x = merge(l[x], r[x]);
    }

    inline int top(register int &x) {
        return val[x];
    }
} orz_night;

void dfs(register int x) {
    orz_yrt.root[x] = ++orz_yrt.graph;
    orz_yrt.siz[x] = 1;
    orz_yrt.sum[x] = orz_night.val[orz_yrt.graph] = c[x];
    for (register Edge *i = orz_yrt.first[x]; i; i = i -> nxt) {
        register int son = i -> to;
        dfs(son);
        orz_yrt.sum[x] += orz_yrt.sum[son];
        orz_yrt.siz[x] += orz_yrt.siz[son];
        orz_yrt.root[x] = orz_night.merge(orz_yrt.root[x], orz_yrt.root[son]);
    }
    while (orz_yrt.sum[x] > m) {
        orz_yrt.sum[x] -= orz_night.top(orz_yrt.root[x]);
        orz_night.pop(orz_yrt.root[x]);
        --orz_yrt.siz[x];
    }
    ans = max(ans, orz_yrt.siz[x] * l[x]);
}

int main() {
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d%d", &b, &c[i], &l[i]);
        orz_yrt.insert(b, i);
    }
    dfs(1);
    printf("%lld\n", ans);
    return 0;
}
