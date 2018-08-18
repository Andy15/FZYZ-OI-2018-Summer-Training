#include <bits/stdc++.h>
#define MAXN 210
#define MAXM 10010
using namespace std;

struct Edge {
    int a, b, c, t, w;

    inline bool operator < (const Edge &ano) const {
        return w < ano.w;
    }
} e[MAXM];

struct Point {
    int x = 0, y = 0;

    inline Point operator - (const Point &ano) const {
        return (Point) {x - ano.x, y - ano.y};
    }

    inline int operator ^ (const Point &ano) const {
        return x * ano.y - y * ano.x;
    }
} c_min, t_min, ans;

struct Union_Find_Set {
    int fa[MAXN];

    int find(register int &x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    inline void join(register int &a, register int &b) {
        fa[a] = b;
    }

    inline void init(register int &siz) {
        for (register int i = 1; i <= siz; ++i)
            fa[i] = i;
    }
} ufs;

int n, m;

Point kruskal() {
    static Point cur; ufs.init(n); sort(e + 1, e + 1 + m);
    for (register int i = 1; i <= m; ++i) {
        int fa_a = ufs.find(e[i].a), fa_b = ufs.find(e[i].b);
        if (fa_a == fa_b)
            continue;
        ufs.join(fa_b, fa_a);
        cur.x += e[i].c; cur.y += e[i].t;
    }
    (!ans.x || ans.x * ans.y > cur.x * cur.y) && (ans = cur, 1);
    return cur;
}

void divide_and_conquer(const Point &a, const Point &b) {
    for (register int i = 1; i <= m; ++i)
        e[i].w = e[i].t * (b.x - a.x) - e[i].c * (b.y - a.y);
    static Point c = kruskal();
    if (((c - a) ^ (b - a)) <= 0)
        return;
    divide_and_conquer(a, c); divide_and_conquer(c, b);
}

int main() {
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= m; ++i) {
        scanf("%d%d%d%d", &e[i].a, &e[i].b, &e[i].c, &e[i].t); ++e[i].a; ++e[i].b;
    }
    for (register int i = 1; i <= m; ++i)
        e[i].w = e[i].c;
    c_min = kruskal();
    for (register int i = 1; i <= m; ++i)
        e[i].w = e[i].t;
    t_min = kruskal();
    divide_and_conquer(c_min, t_min);
    printf("%d %d\n", ans.x, ans.y);
    return 0;
}
