#include <bits/stdc++.h>
#define MAXS 100010
#define MAXN 100010
using namespace std;

#define MAXNODE 100010
#define SIGMA_SIZE 26
#define idx(o) (o - 'a')
struct AhoCorasickAutomata {
    int ch[MAXNODE][SIGMA_SIZE], f[MAXNODE], val[MAXNODE], sz;

    void insert(register char *s) {
        register int u = 0, n = strlen(s);
        for (register int i = 0; i < n; ++i) {
            register int c = idx(s[i]);
            (!ch[u][c]) && (ch[u][c] = ++sz);
            u = ch[u][c];
        }
        val[u] = n;
    }

    void getFail() {
        queue<int> q;
        for (register int c = 0, u; c < SIGMA_SIZE; ++c)
            (u = ch[0][c]) && (q.push(u), 1);
        while (!q.empty()) {
            register int r = q.front(); q.pop();
            for (register int c = 0, u; c < SIGMA_SIZE; ++c)
                (u = ch[r][c]) ? (q.push(u), f[u] = ch[f[r]][c]) : (ch[r][c] = ch[f[r]][c]);
        }
    }
} orz_night;

char s[MAXS], t[MAXS];
int n, top, sta[MAXN], lst[MAXN];

int main() {
    scanf("%s%d", s, &n);
    for (register int i = 1; i <= n; ++i) {
        scanf("%s", t); orz_night.insert(t);
    }
    orz_night.getFail();
    for (register int i = 0, cur = 0, m = strlen(s); i < m; ++i) {
        sta[++top] = i; cur = orz_night.ch[cur][idx(s[i])];
        lst[top] = cur; top -= orz_night.val[cur]; cur = lst[top];
    }
    for (register int i = 1; i <= top; ++i)
        putchar(s[sta[i]]);
    putchar('\n');
    return 0;
}
