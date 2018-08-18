// Inspired by https://blog.csdn.net/Night2002/article/details/79732693
#warning orz_Night
#include <bits/stdc++.h>
#define MAXN 200010
#define MAXM 1000010
#define cmin(a, b) ((a) > (b) && ((a) = (b)))
using namespace std;

int n, m;

struct Graph {
    int dfn[MAXN], low[MAXN], dfn_index, scc_index, scc[MAXN], stack[MAXN], st;
    bool on_stack[MAXN];

    struct Edge {
        int to;
        Edge *nxt;
    } *first[MAXM], e[MAXM], *ptr = e;

    inline void insert(register int u, register int v) {
        *ptr = (Edge) {v, first[u]}; first[u] = ptr++;
    }

    void tarjan(register int o) {
        register int son; dfn[o] = low[o] = ++dfn_index; stack[++st] = o; on_stack[o] = 1;
        for (register Edge *i = first[o]; i; i = i -> nxt) {
            if (!dfn[son = i -> to]) {
                tarjan(son); cmin(low[o], low[son]);
            }
            else
                on_stack[son] && cmin(low[o], dfn[son]);
        }
        if (dfn[o] == low[o]) {
            ++scc_index;
            do {
                son = stack[st--];
                on_stack[son] = 0;
                scc[son] = scc_index;
            } while (o != son);
        }
    }
} g;

int main() {
    for (scanf("%d%d", &n, &m); m; --m) {
        int u, u_val, v, v_val;
        scanf("%d%d%d%d", &u, &u_val, &v, &v_val);
        g.insert(u + n * (1 - u_val), v + n * v_val);
        g.insert(v + n * (1 - v_val), u + n * u_val);
    }
    for (register int i = 0, i_lim = n << 1; i < i_lim; ++i)
        !g.dfn[i] && (g.tarjan(i), 1);
    for (register int i = 0; i < n; ++i)
        if (g.scc[i] == g.scc[i + n]) {
            puts("No");
            return 0;
        }
    puts("Yes");
    for (register int i = 0; i < n; ++i)
        printf("%d ", g.scc[i] >= g.scc[i + n]);
    return 0;
}
