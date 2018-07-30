#include <bits/stdc++.h>
#define MAXN 1010
#define MAXK 240010
#define add(a, b) (nxt[++cnt] = first[a], first[a] = cnt, to[cnt] = b)
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

int n, m, k, a, b, partner[MAXN], cnt, first[MAXN], to[MAXK], nxt[MAXK], ans;
bool vis[MAXN];

bool hungary(register int o) {
	for (register int i = first[o]; i; i = nxt[i]) {
		if (vis[to[i]])
			continue;
		vis[to[i]] = 1;
		if (!partner[to[i]] || hungary(partner[to[i]])) {
			partner[to[i]] = o;
			return 1;
		}
	}
	return 0;
}

int main() {
	r(&n); r(&m); r(&k);
	while (k--) {
		r(&a); r(&b); add(a, b);
	}
	for (register int i = 1; i <= n; ++i) {
		memset(vis, 0, sizeof(vis));
		hungary(i) && ++ans;
	}
	w(ans);
	return 0;
}
