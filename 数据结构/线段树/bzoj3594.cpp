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

const int MaxN = 11000, MaxK = 510, MaxS = 5100;

int N, K, Ans;
int A[MaxN], MS;

int V[MaxK][MaxS + MaxK];

#define lowbit(x) (x & (-x))

int Query_Max(int x, int y)
{
	int Tmp = 0;
	for (RG int i = x; i; i -= lowbit(i))
		for (RG int j = y; j; j -= lowbit(j))
			cmax(Tmp, V[i][j]);
	return Tmp;
}

void Change(int x, int y, int v)
{
	for (RG int i = x; i <= K; i += lowbit(i))
		for (RG int j = y; j <= MS + K; j += lowbit(j))
			cmax(V[i][j], v);
}

int main()
{
	scan(N), scan(K);
	For (i, 1, N) scan(A[i]), cmax(MS, A[i]);
	K++;
	for(RG int i = 1; i <= N; i++)
		for (RG int j = K; j; j--)
		{
			int x = Query_Max(j, A[i] + j) + 1;
			cmax(Ans, x);
			Change(j, A[i] + j, x);
		}
	printf("%d\n", Ans);
	return 0;
}

/*
3 1
2 1 3
*/
