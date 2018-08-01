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

const int MaxN = 510000, MaxT = 1100000;

#define L (o << 1)
#define R (L | 1)

int Sum[MaxT];

void Update(int o)
{
	Sum[o] = Sum[L] + Sum[R];
}

void Change_Add(int o, int l, int r, int x, int ql, int qr)
{
	if (ql <= l && r <= qr) { Sum[o] += x; return; }
	int Mid = (l + r) >> 1;
	if (ql <= Mid) Change_Add(L, l, Mid, x, ql, qr);
	if (Mid < qr)  Change_Add(R, Mid + 1, r, x, ql, qr);
	Update(o);
}

int Query_Sum(int o, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) { return Sum[o]; }
	int Mid = (l + r) >> 1, Tmp = 0;
	if (ql <= Mid) Tmp += Query_Sum(L, l, Mid, ql, qr);
	if (Mid < qr)  Tmp += Query_Sum(R, Mid + 1, r, ql, qr);
	return Tmp;
}

int main()
{
	
	return 0;
}
