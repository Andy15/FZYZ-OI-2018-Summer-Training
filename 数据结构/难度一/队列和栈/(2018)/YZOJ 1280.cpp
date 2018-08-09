#include <bits/stdc++.h>
#define MAXN 100010
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

int n, a, sta[MAXN], top, ans;

int main() {
	r(&n);
	for (int x; n; --n) {
		r(&x);
		while (top && sta[top] > x)
			--top;
		sta[top] != x && ++ans;
		sta[++top] = x;
	}
	w(ans);
	return 0;
}
