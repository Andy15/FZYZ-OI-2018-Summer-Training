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

const int MaxN = 2100, MaxT = 4100, Inf = 1000000000;

int N, M;
int A[MaxN];
int F[MaxN][MaxN];

#define L (o << 1)
#define R (L | 1)

struct Segment_Tree
{
	int V[MaxT];
	
	void build()
	{
		For (i, 1, N + M) V[i] = Inf;
	}
	
	void insert(int x, int y)
	{
		for (x += M; x; x >>= 1) cmin(V[x], y);
	}
	
	void ask(int x, int y, int &v)
	{
		if (x > y) return;
		for (x += M - 1, y += M + 1; x ^ y ^ 1; x >>= 1, y >>= 1)
		{
			if (~x & 1) cmin(v, V[x ^ 1]);
			if ( y & 1) cmin(v, V[y ^ 1]);
		}
	}
	
}	T1[MaxN], T2[MaxN];

void Add(int x, int y)
{
	if (x > 1) T1[y].insert(x - 1, F[x][y] + A[x - 1]);
	if (y < N) T2[x].insert(y + 1, F[x][y] + A[y + 1]);
}

int main()
{
	scan(N);
	for (M = 1; M < N + 2; M <<= 1);
	For (i, 1, N) scan(A[i]), T1[i].build(), T2[i].build();
	For (i, 1, N) Add(i, i - 1);
	For (i, 1, N) F[i][i] = A[i], Add(i, i);
	for (RG int i = N; i; i --)
		for (RG int j = i + 1, g = i; j <= N; j++)
		{
			while (g <= j && F[i][g - 1] < F[g + 1][j]) g++;
			F[i][j] = Inf;
			T1[j].ask(i, g - 1, F[i][j]);
			T2[i].ask(g, j, F[i][j]);
			Add(i, j);
		}
	printf("%d\n", F[1][N]);
	return 0;
}

/*
4
8 24 12 6
*/
