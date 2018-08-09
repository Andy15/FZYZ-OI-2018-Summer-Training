#include <bits/stdc++.h>
#define MAXN 300010
#define Mul(p, x) (V[p] *= x, MUL[p] *= x, ADD[p] *= x)
#define Add(p, x) (V[p] += x, ADD[p] += x)
#define swap(a, b) (a ^= b ^= a ^= b)
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

int f[MAXN], c[MAXN], dep[MAXN], n, m, fdep[MAXN], ch[MAXN][2], root[MAXN], ans1[MAXN], ans2[MAXN];
long long h[MAXN], mul[MAXN], add[MAXN], s[MAXN], V[MAXN], MUL[MAXN], ADD[MAXN];

inline void push_down(register int x) {
	register int lson = ch[x][0], rson = ch[x][1];
	MUL[x] != 1 && (lson && Mul(lson, MUL[x]), rson && Mul(rson, MUL[x]), MUL[x] = 1);
	ADD[x] && (lson && Add(lson, ADD[x]), rson && Add(rson, ADD[x]), ADD[x] = 0);
}

int Merge(register int a, register int b) {
	if (!a || !b)
		return a + b;
	V[a] > V[b] && swap(a, b);
	push_down(a);
	ch[a][1] = Merge(ch[a][1], b);
	fdep[ch[a][0]] < fdep[ch[a][1]] && swap(ch[a][0], ch[a][1]);
	fdep[a] = fdep[ch[a][1]] + 1;
	return a;
}

int main() {
	r(&n); r(&m);
	for (register int i = 1; i <= n; ++i)
		r(&h[i]);
	for (register int i = 2; i <= n; ++i) {
		int a; long long v;
		r(&f[i]); r(&a); r(&v);
		a ? (mul[i] = v, add[i] = 0) : (mul[i] = 1, add[i] = v);
	}
	// 我们可以把在同一个点的所有玩家存在一个堆里，按战斗力从小到大排序，
	for (register int i = 1; i <= m; ++i) {
		r(&s[i]); r(&c[i]);
		MUL[i] = 1; V[i] = s[i];
		root[c[i]] = Merge(root[c[i]], i);
	}
	for (register int i = 1; i <= n; ++i)
		dep[i] = dep[f[i]] + 1;
	for (register int i = n; i; --i) {
		// 若目前最小值小于该点守卫的战斗力，则POP。
		while (root[i] && V[root[i]] < h[i]) {
			ans2[root[i]] = dep[c[root[i]]] - dep[i];
			++ans1[i];
			push_down(root[i]);
			root[i] = Merge(ch[root[i]][0], ch[root[i]][1]);
		}
		// 剩下的玩家打上标记后，合并到父亲节点的堆上。
		root[i] && (Mul(root[i], mul[i]), Add(root[i], add[i]), root[f[i]] = Merge(root[f[i]], root[i]));
	}
	while (root[0]) {
		ans2[root[0]] = dep[c[root[0]]];
		push_down(root[0]);
		root[0] = Merge(ch[root[0]][0], ch[root[0]][1]);
	}
	for (register int i = 1; i <= n; ++i) {
		w(ans1[i]);
		putchar('\n');
	}
	for (register int i = 1; i <= m; ++i) {
		w(ans2[i]);
		putchar('\n');
	}
	return 0;
}

/*
5 5
50 20 10 10 30
1 1 2
2 0 5
2 0 -10
1 0 10
20 2
10 3
40 4
20 4
35 5

2
2
0
0
0
1
1
3
1
1
*/
