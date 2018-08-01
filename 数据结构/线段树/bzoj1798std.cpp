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

int N, M, P;
int A[100010];

int main()
{
	scan(N); scan(P);
	For (i, 1, N) scan(A[i]);
	scan(M);
	For (m, 1, M)
	{
		int opt, l, r, v; scan(opt); scan(l); scan(r);
		if (opt == 1)
		{
			scan(v); v %= P;
			For (i, l, r) A[i] = ((ll) A[i] * v) % P;
		}
		if (opt == 2)
		{
			scan(v); v %= P;
			For (i, l, r) A[i] = ((ll) A[i] + v) % P;
		}
		if (opt == 3)
		{
			int Sum = 0;
			For (i, l, r) Sum = (Sum + A[i]) % P;
			printf("%d\n", Sum);
		}
	}
	return 0;
}
