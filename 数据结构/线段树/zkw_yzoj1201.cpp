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
#define For(i, f, t) for (RG int i = f; i <= t; ++i)
IL int dmax(int x, int y) { return x > y ? x : y; }
IL void cmax(int &x, int y) { x < y ? x = y : 0; }

const int MaxN = 210000;

int N, M, Q;
int Mx[MaxN << 2];

int main()
{
	scan(N);
	for (M = 1; M < N; M <<= 1);
	For (i, M + 1, M + N) scan(Mx[i]);
	for (RG int i = M; i; i--) Mx[i] = dmax(Mx[i << 1], Mx[i << 1 | 1]);
	scan(Q);
	For (i, 1, Q)
	{
		RG int l, r; scan(l), scan(r);
		RG int Ans = -1000000000;
		for (l = l + M - 1, r = r + M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
		{
			if (~l & 1) cmax(Ans, Mx[l ^ 1]);
			if ( r & 1) cmax(Ans, Mx[r ^ 1]);
		}
		printf("%d\n", Ans);
	}
	return 0;
}
