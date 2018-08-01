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

const int MaxN = 510000, MaxT = 1100000, Inf = 1e9;

#define L (o << 1)
#define R (L | 1)

int N, K; ll Ans;
int i, j, A[MaxN], B[MaxN];
int aa[MaxT], ab[MaxT], ba[MaxT], bb[MaxT], vm[MaxT], tag[MaxT];

struct P
{
	int x, y;
	P(int _x = 0, int _y = 0) { x = _x, y = _y; }
	IL friend P operator + (P p1, P p2)
	{
		if (A[p1.x] + B[p1.y] < A[p2.x] + B[p2.y]) return p1; return p2;
	}
}	va[MaxT], vb[MaxT], vc[MaxT], t;

void Add1(int o, int add)
{
	vm[o] += add;
	tag[o] += add;
}

void Pushdown(int o)
{
	if (tag[o])
	{
		Add1(L, tag[o]);
		Add1(R, tag[o]);
		tag[o] = 0;
	}
}

void Pushup(int o)
{
	int l = L, r = R;
	va[o] = va[l] + va[r] + P(aa[l], ab[r]);
	vc[o] = vc[l] + vc[r] + P(aa[r], ab[l]);
	vb[o] = vb[l] + vb[r];
	aa[o] = A[aa[l]] < A[aa[r]] ? aa[l] : aa[r];
	ab[o] = B[ab[l]] < B[ab[r]] ? ab[l] : ab[r];
	if (vm[l] < vm[r])
	{
		vb[o] = vb[o] + vc[r] + P(aa[r], bb[l]);
		ba[o] = ba[l];
		bb[o] = B[ab[r]] < B[bb[l]] ? ab[r] : bb[l];
		vm[o] = vm[l];
	}
	if (vm[l] > vm[r])
	{
		vb[o] = vb[o] + vc[l] + P(ba[r], ab[l]);
		ba[o] = A[aa[l]] < A[ba[r]] ? aa[l] : ba[r];
		bb[o] = bb[r];
		vm[o] = vm[r];
	}
	if (vm[l] == vm[r])
	{
		vb[o] = vb[o] + P(ba[r], bb[l]);
		ba[o] = ba[l];
		bb[o] = bb[r];
		vm[o] = vm[l];
	}
}

void Build(int o, int l, int r)
{
	if (l == r)
	{
		va[o] = vc[o] = P(l, l), vb[o] = P(0, 0);
		aa[o] = ab[o] = ba[o] = l;
		return;
	}
	int Mid = (l + r) >> 1;
	Build(L, l, Mid), Build(R, Mid + 1, r);
	Pushup(o);
}

void Add(int o, int l, int r, int ql, int qr, int add)
{
	if (ql <= l && r <= qr) { Add1(o, add); return; }
	Pushdown(o);
	int Mid = (l + r) >> 1;
	if (ql <= Mid) Add(L, l, Mid, ql, qr, add);
	if (Mid < qr)  Add(R, Mid + 1, r, ql, qr, add);
	Pushup(o);
}

void Change(int o, int l, int r, int v)
{
	if (l == r) return;
	Pushdown(o);
	int Mid = (l + r) >> 1;
	if (v <= Mid) Change(L, l, Mid, v);
	else Change(R, Mid + 1, r, v);
	Pushup(o);
}

int main()
{
	scan(N); scan(K);
	For (pos, 1, N) scan(A[pos]);
	For (pos, 1, N) scan(B[pos]);
	A[0] = B[0] = Inf;
	Build(1, 0, N);
	while (K--)
	{
		t = va[1] + vb[1];
		i = t.x, j = t.y;
		Ans += A[i] + B[j];
		if (i < j) Add(1, 0, N, i, j - 1, 1);
		if (i > j) Add(1, 0, N, j, i - 1, -1);
		A[i] = Inf, Change(1, 0, N, i);
		B[j] = Inf, Change(1, 0, N, j);
	}
	printf("%lld\n", Ans);
	return 0;
}

/*
8 4
3 8 7 9 9 4 6 8
2 5 9 4 3 8 9 1
*/
