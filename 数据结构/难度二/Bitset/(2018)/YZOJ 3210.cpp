#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#define getchar() getchar_unlocked()
#endif // ONLINE_JUDGE
using namespace std;

int nxt;

int read() {
	register int n = 0, F = 1;
	char ch;
	while ( (ch = getchar()) != '-' && (ch < '0' || ch > '9'));
	ch == '-' ? F = 0 : n = ch - '0';
	while ( (ch = getchar()) >= '0' && ch <= '9') n = (n << 1) + (n << 3) + ch - '0';
	nxt = ch == '\n';
	return F ? n : -n;
}

int a[1000010], c[1000010];
unsigned b[40010], r[40][40010];

void sett(register int v) {
	b[v >> 5] |= 1 << (v & 31);
	v = 500000 - v;
	for (register int i = 0; i < 32; ++i)
		v - i >= 0 && (r[i][(v - i) >> 5] |= 1 << ((v - i) & 31));
}

void resett(register int v) {
	b[v >> 5] -= (1u << (v & 31));
	v = 500000 - v;
	for (register int i = 0; i < 32; ++i)
		v - i >= 0 && (r[i][(v - i) >> 5] -= (1u << ((v - i) & 31)));
}

int main() {
	register int n = read(), m = read(), tp = read();
	if (tp) {
		for (register int i = 1; i <= n; ++i)
			++c[a[i] = read()];
		register int la = 0, fl = 0;
		for (register int i = 1; i <= m; ++i) {
			register int op = read(), u = read();
			if (nxt) {
				if (fl) {
					if ((la ^ op) == 2)
						puts("no");
					else {
						puts("yes"); ++la;
					}
				}
				fl = 1;
			}
			else {
				register int v = read();
				if (fl) {
					if ((la ^ op) == 1)
						puts("no");
					else {
						puts("yes"); ++la;
					}
				}
				u ^= la; v ^= la;
				--c[a[u]]; ++c[a[u] = v];
				fl = 0;
			}
			if (i == m && (op ^ la) == 2) {
				u ^= la;
				for (register int j = 0; j <= u; ++j)
					if (c[j] && c[u - j]) {
						puts ("yes");
						return 0;
					}
				puts("no");
			}
		}
	}
	else {
		for (register int i = 1; i <= n; ++i)
			c[a[i] = read()]++ == 0 && (sett(a[i]), 0);
		for (register int i = 1; i <= m; ++i) {
			register int op = read();
			if (op == 1) {
				register int u = read(), v = read();
				--c[a[u]] == 0 && (resett(a[u]), 0);
				c[a[u] = v]++ == 0 && (sett(v), 0);
			}
			else {
				register int u = read(), v = 500000 - u, pl = v & 31, cnt = (u + 544) >> 9;
				register unsigned *R = r[pl];
				register bool suc = 0;
				for (register int p = 0, q = (v - pl) >> 5; cnt--; p += 8, q += 8)
					if ((b[p] & R[q]) |
					    (b[p + 1] & R[q + 1]) |
						(b[p + 2] & R[q + 2]) |
						(b[p + 3] & R[q + 3]) |
						(b[p + 4] & R[q + 4]) |
						(b[p + 5] & R[q + 5]) |
						(b[p + 6] & R[q + 6]) |
						(b[p + 7] & R[q + 7])) {
						puts("yes");
						suc = 1;
						break;
					}
				!suc && puts("no");
			}
		}
	}
	return 0;
}
