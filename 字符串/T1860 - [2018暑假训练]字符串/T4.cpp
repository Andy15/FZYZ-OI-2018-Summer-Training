#include <bits/stdc++.h>
#define MAXN 300010
#define SIGMA 30
#define idx(o) (o - 'a')
using namespace std;

int n, len[MAXN], ch[MAXN][SIGMA], siz = 1, deg[SIGMA], que[MAXN], head, tail, cnt;
bool val[MAXN], g[SIGMA][SIGMA], ans[MAXN];
string s[MAXN];

bool chk() {
    head = 1; tail = 0; memset(deg, 0, sizeof(deg));
    for (register int i = 0; i <= 25; ++i)
        for (register int j = 0; j <= 25; ++j)
            g[i][j] && ++deg[j];
    for (register int i = 0; i <= 25; ++i)
        !deg[i] && (que[++tail] = i);
    register int cur;
    while (head <= tail) {
		cur = que[head++];
        for (register int i = 0; i <= 25; ++i)
            (g[cur][i] && !(--deg[i])) && (que[++tail] = i);
	}
	return tail == 26;
}

int main() {
    scanf("%d", &n);
    for (register int i = 0, ori, tot; i < n; ++i) {
        cin >> s[i]; ori = 1; tot = len[i] = s[i].size();
        for (register int j = 0, cur; j < tot; ++j) {
            cur = idx(s[i][j]);
            !ch[ori][cur] && (ch[ori][cur] = ++siz);
            ori = ch[ori][cur];
        }
        val[ori] = 1;
    }
    for (register int i = 0; i < n; ++i) {
        for (register int a = 0; a <= 25; ++a)
            for (register int b = 0; b <= 25; ++b)
                g[a][b] = 0;
        register bool flag = 1;
        for (register int j = 0, j_lim = len[i], pos = 1, cur; j < j_lim; ++j) {
            if (val[pos]) {
                flag = 0;
                break;
            }
            cur = idx(s[i][j]);
            for (register int k = 0; k <= 25; ++k)
                (k != cur && ch[pos][k]) && (g[cur][k] = 1);
            pos = ch[pos][cur];
        }
        (flag && chk()) && (ans[i] = 1, ++cnt);
    }
    printf("%d\n", cnt);
    for (register int i = 0; i < n; ++i)
        ans[i] && (cout << s[i] << '\n');
    return 0;
}
