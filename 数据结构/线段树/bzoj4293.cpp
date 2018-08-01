#include <bits/stdc++.h>
using namespace std;

template<class T> void scan(T &aa)
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

const int MaxN = 510000;

int N, M;
ll day, lim, lastd;
int A[MaxN];
ll Ans;

#define L (o << 1)
#define R (L | 1)

struct Node
{
	int l, r;
	ll s, sum, vl, vr;
	bool a; ll b, c;
}	t[MaxN << 2];

IL void Build(int o, int l, int r)
{
	t[o].l = l, t[o].r = r;
	if (l == r)
	{
		t[o].s = A[l];
		return;
	}
	int Mid = (l + r) >> 1;
	Build(L, l, Mid), Build(R, Mid + 1, r);
	t[o].s = t[L].s + t[R].s;
}

IL void Add(int o, bool a, ll b, ll c)
{
	t[o].vl = t[o].vl * a + b + c * A[t[o].l];
	t[o].vr = t[o].vr * a + b + c * A[t[o].r];
	t[o].sum = t[o].sum * a + b * (t[o].r - t[o].l + 1) + c * t[o].s;
	t[o].a &= a;
	t[o].b = t[o].b * a + b;
	t[o].c = t[o].c * a + c;
}

IL void Pushdown(int o)
{
	Add(L, t[o].a, t[o].b, t[o].c);
	Add(R, t[o].a, t[o].b, t[o].c);
	t[o].a = 1, t[o].b = 0, t[o].c = 0;
}

IL void Find(int o)
{
	if (t[o].vr <= lim) return;
	if (t[o].vl > lim)
	{
		Ans += t[o].sum - (t[o].r - t[o].l + 1) * lim;
		Add(o, 0, lim, 0);
		return;
	}
	Pushdown(o);
	Find(L); Find(R);
	t[o].vl = t[L].vl; t[o].vr = t[R].vr;
	t[o].sum = t[L].sum + t[R].sum;
}

int main()
{
	scan(N), scan(M);
	For (i, 1, N) scan(A[i]);
	sort(A + 1, A + N + 1);
	Build(1, 1, N);
	For (i, 1, M)
	{
		scan(day), scan(lim);
		Add(1, 1, 0, day - lastd);
		Ans = 0;
		Find(1);
		lastd = day;
		printf("%lld\n", Ans);
	}
	return 0;
}

/*
4 4
1 2 4 3
1 1
2 2
3 0
4 4
*/
