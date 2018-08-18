#include <bits/stdc++.h>
#define MAXN 310
using namespace std;

int n, m, ans, blk_cnt, blk_siz[MAXN], blk_mem[MAXN], ans_blk, ans_siz, ans_cnt, ans_lst[MAXN];
bool res[MAXN], block[MAXN];

struct Graph {
    int partner_left[MAXN], partner_right[MAXN];
    bool g[MAXN][MAXN], vis[MAXN], left[MAXN], right[MAXN], select[MAXN];

    struct Edge {
        int to;
        Edge *nxt;
    } *first[MAXN * MAXN << 1], e[MAXN * MAXN << 1], *ptr = e;

    inline void insert(register int &u, register int &v) {
        g[u][v] = 1; *ptr = (Edge) {v, first[u]}; first[u] = ptr++;
    }

    void floyd(register int &n) {
        for (register int k = 1; k <= n; ++k)
            for (register int i = 1; i <= n; ++i)
                for (register int j = 1; j <= n; ++j)
                    g[i][j] |= g[i][k] & g[i][j];
    }

    bool hungary(register int o) {
        register int son;
        for (register Edge *i = first[o]; i; i = i -> nxt) {
            if (vis[son = i -> to])
                continue;
            vis[son] = 1;
            if (!partner_right[son] || hungary(partner_right[son])) {
                partner_right[son] = o;
                return 1;
            }
        }
        return 0;
    }

    void dfs(register int o) {
        register int son;
        for (register Edge *i = first[o]; i; i = i -> nxt) {
            if (right[son = i -> to])
                continue;
            right[son] = 1; left[partner_right[son]] = 0; dfs(partner_right[son]);
        }
    }

    void floodfill(register int o) {
        if (select[o])
            return;
        select[o] = 1;
        for (register Edge *i = first[o]; i; i = i -> nxt)
            floodfill(i -> to);
    }
} g;

int main() {
    for (scanf("%d%d", &n, &m); m; --m) {
        int u, v; scanf("%d%d", &u, &v); g.insert(u, v);
    }
    g.floyd(n);
    for (register int i = 1; i <= n; ++i) {
        memset(g.vis, 0, sizeof(g.vis));
        g.hungary(i) && ++ans;
    }
    for (register int i = 1; i <= n; ++i)
        g.partner_right[i] && (g.partner_left[g.partner_right[i]] = i);
    for (register int i = 1; i <= n; ++i)
        g.partner_left[i] && (g.left[i] = 1);
    for (register int i = 1; i <= n; ++i)
        !g.left[i] && (g.dfs(i), 1);
    for (register int i = 1; i <= n; ++i)
        (!g.left[i] && !g.right[i]) && (res[i] = 1);
    for (register int i = 1; i <= n; ++i) {
        if (!res[i] || block[i])
            continue;
        memset(g.select, 0, sizeof(g.select));
        block[i] = (blk_siz[blk_mem[i] = ++blk_cnt] = 1); g.floodfill(i);
        for (register int j = 1; j <= n; ++j)
            (res[j] && !g.select[j] && !block[j]) && (block[j] = 1, ++blk_siz[blk_mem[j] = blk_cnt], g.floodfill(j), 1);
        ans_siz < blk_siz[blk_cnt] && (ans_siz = blk_siz[blk_cnt], ans_blk = blk_cnt);
    }
    for (register int i = 1; i <= n; ++i)
        blk_mem[i] == ans_blk && (ans_lst[++ans_cnt] = i);
    printf("%d\n", ans_cnt);
    for (register int i = 1; i <= ans_cnt; ++i)
        printf("%d%c", ans_lst[i], " \n"[i == ans_cnt]);
    return 0;
}
