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

const int MaxN = 210000, MaxT = 810000;

#define L (o << 1)
#define R (L | 1)

int N, M, D;
int lastans;
int Mx[MaxT];

void Update(int o)
{
	Mx[o] = dmax(Mx[L], Mx[R]);
}

void Change_Add(int o, int l, int r, int x, int qx)
{
	if (l == r) { Mx[o] = x; return; }
	int Mid = (l + r) >> 1;
	if (qx <= Mid) Change_Add(L, l, Mid, x, qx);
	if (Mid < qx)  Change_Add(R, Mid + 1, r, x, qx);
	Update(o);
}

int Query_Max(int o, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) return Mx[o];
	int Mid = (l + r) >> 1, Tmp = 0;
	if (ql <= Mid) cmax(Tmp, Query_Max(L, l, Mid, ql, qr));
	if (Mid < qr)  cmax(Tmp, Query_Max(R, Mid + 1, r, ql, qr));
	return Tmp;
}

int main()
{
	scan(M); scan(D);
	For (m, 1, M)
	{
		char ch; while (ch = getchar(), ch != 'Q' && ch != 'A');
		int x, Num; scan(x);
		if (ch == 'Q') printf("%d\n", lastans = Query_Max(1, 1, M, N - x + 1, N));
		if (ch == 'A') Num = ((ll)x + lastans) % D, ++N, Change_Add(1, 1, M, Num, N);
	}
	return 0;
}
/*
5 100
A 96
Q 1
A 97
Q 1
Q 2
*/
