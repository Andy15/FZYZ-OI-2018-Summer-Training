#include <bits/stdc++.h>
#define MAXN 1010
#define MAXM 1000010
#define add(u, v) (nxt[++cnt] = first[u], first[u] = cnt, to[cnt] = v)
using namespace std;

char B[1 << 15], *S = B, *T = B;
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
template<typename P>
inline void r(register P *o) {
	register char ch, f;
	while (ch = getc(), (ch < '0' || ch > '9') && ch != '-');
	ch == '-' ? *o = f = 0 : (*o = ch - '0', f = 1);
	while (ch = getc(), ch >= '0' && ch <= '9' ) *o = *o * 10 + ch - '0';
	!f && (*o = -*o);
}
template<typename P>
inline void w(register P o) {
    o < 0 && (putchar('-'), o = -o);
    o > 9 && (w(o / 10), 0);
    putchar(o % 10 + '0');
}

int n, k, d, tmp, ans, ansa[MAXM], ansb[MAXM];
int cnt, first[MAXN], nxt[MAXM], to[MAXM];
bool vis[MAXN], viss[MAXN], flag[MAXN];
queue<int> que; // STL大法好！！！！！
bitset<MAXN> lck[MAXN], temp; // STL大法好！！！！！

void bfs() {
	memset(vis, 0, sizeof(vis));
	for (register int i = k + 1; i <= n; ++i)
		(!flag[i]) && (que.push(i), vis[i] = 1);
	while (!que.empty()) {
		register int id = que.front(); que.pop();
		for (register int i = first[id]; i; i = nxt[i])
			(!vis[to[i]] && !flag[to[i]]) && (que.push(to[i]), vis[to[i]] = 1);
	}
}

int main() {
	r(&n); r(&k);
	for (register int i = 1; i <= k; ++i) {
		r(&d);
		for (register int j = 1; j <= d; ++j) {
			r(&tmp); add(tmp, i);
		}
	}
	bfs();
	for (register int i = 1; i <= n; ++i)
		!vis[i] && ++ans;
	w(ans); putchar('\n');
	for (register int i = 1; i <= n; ++i)
		!vis[i] && (w(i), putchar('\n'));
	memcpy(viss, vis, sizeof(vis));
	for (register int i = 1; i <= n; ++i) {
		flag[i] = 1;
		bfs();
		for (register int j = 1; j <= n; ++j)
			(vis[j] != viss[j]) && (lck[j][i] = 1);
		flag[i] = 0;
	}
	ans = 0;
	for (register int i = 1; i <= n; ++i)
		for (register int j = i + 1; j <= n; ++j) {
			temp = lck[i] & lck[j];
			(temp.count()) && (++ans, ansa[ans] = i, ansb[ans] = j);
		}
	w(ans); putchar('\n');
	if (ans > 10000)
		return 0;
	for (register int i = 1; i <= ans; ++i) {
		w(ansa[i]); putchar(' '); w(ansb[i]); putchar('\n');
	}
	return 0;
}
