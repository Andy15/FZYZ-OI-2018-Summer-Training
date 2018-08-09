#include <bits/stdc++.h>
using namespace std;

int n, m, x, y;
char s[10];

struct Union_Set {
    map<int, int> fa;
    map<int, char> p;

    int find(int o) {
        register int tmp;
        return (fa[o] == o) ? (o) : (tmp = find(fa[o]), p[o] ^= p[fa[o]], fa[o] = tmp);
    }

    inline void join(int a, register int b) {
        fa[a] = b; p[a] = query();
    }

    inline int query() {
        return p[x] ^ p[y] ^ (*s == 'o');
    }
} orz_yrt;

int main() {
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= m; ++i) {
        scanf("%d%d%s", &x, &y, s); --x;
        (!orz_yrt.fa[x]) && (orz_yrt.fa[x] = x); (!orz_yrt.fa[y]) && (orz_yrt.fa[y] = y);
        register int a = orz_yrt.find(x), b = orz_yrt.find(y);
        if (a == b) {
            if (orz_yrt.query()) {
                printf("%d\n", i - 1);
                return 0;
            }
        }
        else
            orz_yrt.join(a, b);
    }
    printf("%d\n", m);
    return 0;
}
