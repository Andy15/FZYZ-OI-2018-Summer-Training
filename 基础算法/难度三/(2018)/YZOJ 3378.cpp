#include <bits/stdc++.h>
#define MAXN 110
using namespace std;

int n, a[MAXN], cnt;
bool vis[MAXN], outed;
char ans[MAXN];

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

void dfs(register int now) {
	if (outed || cnt < 0)
		return;
	if (now > n) {
		if (cnt)
			return;
		for (register int i = 1; i <= n; ++i)
			putchar(ans[i]);
		outed = 1;
	}
	if (vis[now]) {
		ans[now] == '(' ? ++cnt : --cnt;
		dfs(now + 1);
		ans[now] == '(' ? --cnt : ++cnt;
		return;
	}
	register int k = 1;
	for (register int i = now; !vis[i]; i = a[i]) {
		vis[i] = 1;
		k = !k;
		k ? ans[i] = '(' : ans[i] = ')';
	}
	--cnt; dfs(now + 1);
	if (outed)
		return;
	cnt += 2;
	ans[now] = '(';
	for (register int i = a[now]; i != now; i = a[i]) {
		k = !k;
		k ? ans[i] = '(' : ans[i] = ')';
	}
	dfs(now + 1);
	if (outed)
		return;
	--cnt;
	for (register int i = now; vis[i]; i = a[i])
		vis[i] = 0;
}

int main() {
	r(&n);
	for (register int i = 1; i <= n; ++i)
		r(&a[i]);
	for (register int i = 1; i <= n; ++i)
		((!vis[i]) && i == a[a[i]]) && (vis[i] = vis[a[i]] = 1, ans[i] = '(', ans[a[i]] = ')');
	dfs(1);
	return 0;
}
