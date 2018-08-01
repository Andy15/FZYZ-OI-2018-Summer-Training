#include <bits/stdc++.h>
using namespace std;

void scan(int &aa)
{
	char ch; bool bb;
	while (ch = getchar(), (ch < '0' || ch > '9') && ch != '-');
	ch == '-' ? (bb = 1, aa = 0): (bb = 0, aa = ch - '0');
	while (ch = getchar(), ch >= '0' && ch <= '9') aa = aa * 10 + ch - '0';
	bb? aa = -aa: 0;
}

#define RG register
#define IL inline
#define db double
#define ll long long
#define For(i, f, t) for (RG int i = f; i <= t; ++i)
IL int dmin(int x, int y) { return x < y ? x : y; }
IL int dmax(int x, int y) { return x > y ? x : y; }
IL void cmin(int &x, int y) { x > y ? x = y : 0; }
IL void cmax(int &x, int y) { x < y ? x = y : 0; }
IL void mswap(int &x, int &y) { int o = x; x = y; y = o; }
IL int mabs(int x) { return x < 0 ? -x : x; }

const int MaxN = 110000, MaxT = 1010000;

#define L (o << 1)
#define R (L | 1)

int N, M, P;
int A[MaxN];
int Size[MaxT];
ll Sum[MaxT], Ml[MaxT], Ad[MaxT], v[MaxT];

void Update(int o, int x)
{
	int a = Ml[x] * Ml[o] % P;
	int b = (Ad[x] * Ml[o] % P + Ad[o]) % P;
	Ml[x] = a, Ad[x] = b;
}
void Pushup(int o)
{
	Sum[o] = ((v[o] + Sum[L] + Sum[R]) % P * Ml[o] % P + Ad[o] * Size[o] % P) % P;
}
void Pushdown(int o)
{
	Update(o, L); Update(o, R);
	Ml[o] = 1, Ad[o] = 0;
}

void Build(int o, int l, int r)
{
	Size[o] = r - l + 1;
	Ml[o] = 1;
	if (l == r) { v[o] = A[l]; Pushup(o); return; }
	int Mid = (l + r) >> 1;
	Build(L, l, Mid), Build(R, Mid + 1, r);
	Pushup(o);
}

void Change_Mul(int o, int l, int r, int x, int ql, int qr)
{
	if (ql <= l && r <= qr)
	{
		Ml[o] = Ml[o] * x % P;
		Ad[o] = Ad[o] * x % P;
		Pushup(o);
		return;
	}
	int Mid = (l + r) >> 1;
	Pushdown(o); Pushup(L); Pushup(R);
	if (ql <= Mid) Change_Mul(L, l, Mid, x, ql, qr);
	if (Mid < qr)  Change_Mul(R, Mid + 1, r, x, ql, qr);
	Pushup(o);
}

void Change_Add(int o, int l, int r, int x, int ql, int qr)
{
	if (ql <= l && r <= qr)
	{
		Ad[o] = (Ad[o] + x) % P;
		Pushup(o);
		return;
	}
	int Mid = (l + r) >> 1;
	Pushdown(o); Pushup(L); Pushup(R);
	if (ql <= Mid) Change_Add(L, l, Mid, x, ql, qr);
	if (Mid < qr)  Change_Add(R, Mid + 1, r, x, ql, qr);
	Pushup(o);
}

int Query_Sum(int o, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) { return Sum[o]; }
	int Mid = (l + r) >> 1, Tmp = 0;
	Pushdown(o); Pushup(L); Pushup(R);
	if (ql <= Mid) Tmp = (Tmp + Query_Sum(L, l, Mid, ql, qr)) % P;
	if (Mid < qr)  Tmp = (Tmp + Query_Sum(R, Mid + 1, r, ql, qr)) % P;
	return Tmp;
}

int main()
{
	scan(N), scan(P);
	For (i, 1, N) scan(A[i]);
	Build(1, 1, N);
	scan(M);
	For (m, 1, M)
	{
		int opt, l, r, v; scan(opt); scan(l); scan(r);
		if (opt == 1) scan(v), Change_Mul(1, 1, N, v, l, r);
		if (opt == 2) scan(v), Change_Add(1, 1, N, v, l, r);
		if (opt == 3) printf("%d\n", Query_Sum(1, 1, N, l, r));
	}
	return 0;
}

/*
7 43
1 2 3 4 5 6 7
5
1 2 5 5
3 2 4
2 3 7 9
3 1 3
3 4 7
*/
