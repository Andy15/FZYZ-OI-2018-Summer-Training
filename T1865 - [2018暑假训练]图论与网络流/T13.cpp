#include <bits/stdc++.h>
#define MAXP 2000010
using namespace std;

int n, m, k, ans_scc, ans_siz;

struct Graph {
    int head, tail = -1, que[MAXP], deg[MAXP], scc_index, siz[MAXP], scc[MAXP];
    bool vis[MAXP], select[MAXP];

    struct Edge {
        int to;
        Edge *nxt;
    } *first[MAXP], e[MAXP], *ptr = e;

    inline void insert(register int &u, register int &v) {
        *ptr = (Edge) {v, first[u]}; first[u] = ptr++; ++deg[v];
    }

    void toposort() {
        for (register int i = 1; i <= n; ++i)
            deg[i] < k && (que[++tail] = i, vis[i] = 1);
        while (head <= tail) {
            register int o = que[head++], son;
            for (register Edge *i = first[o]; i; i = i -> nxt)
                (--deg[son = i -> to] < k && !vis[son]) && (que[++tail] = son, vis[son] = 1);
        }
    }

    void floodfill(register int o, register int index) {
        register int son; select[o] = 1; ++siz[index]; scc[o] = index;
        for (register Edge *i = first[o]; i; i = i -> nxt) {
            if (vis[son = i -> to] || select[son])
                continue;
            floodfill(son, index);
        }
    }
} g;

int main() {
    for (scanf("%d%d%d", &n, &m, &k); m; --m) {
        int x, y; scanf("%d%d", &x, &y);
        g.insert(x, y); g.insert(y, x);
    }
    g.toposort();
    for (register int i = 1; i <= n; ++i)
        (!g.vis[i] && !g.select[i]) && (g.floodfill(i, ++g.scc_index), 1);
    for (register int i = 1, i_lim = g.scc_index, siz_cur; i <= i_lim; ++i)
        ans_siz < (siz_cur = g.siz[i]) && (ans_scc = i, ans_siz = siz_cur);
    if (!ans_siz) {
        puts("NIE");
        return 0;
    }
    printf("%d\n", ans_siz);
    for (register int i = 1; i <= n; ++i)
        (!g.vis[i] && g.scc[i] == ans_scc) && printf("%d ", i);
    return 0;
}
