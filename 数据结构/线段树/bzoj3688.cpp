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

const int MaxN = 110000, MaxM = 12, Mod = 100007, MaxH = 110000;

int N, M;
struct P {int x, y;} p[MaxN];
bool cmp(P p1, P p2) { return p1.x < p2.x; }
int MH;
int F[MaxN][MaxM][2];
int V[MaxM][2][MaxH];

void dmod(int &x) { x = (x % Mod + Mod) % Mod; }

#define lowbit(x) ((x) & (-x))

void Add(int h, int j, int k, int v)
{
	for (int i = h; i <= MaxH; i += lowbit(i))
		dmod(V[j][k][i] += v);
}

int Query(int h, int j, int k)
{
	int Sum = 0;
	for (int i = h; i; i -= lowbit(i))
		dmod(Sum += V[j][k][i]);
	return Sum;
}

int main()
{
	scan(N), scan(M);
	For (i, 1, N) scan(p[i].x), scan(p[i].y), cmax(MH, p[i].y);
	sort(p + 1, p + N + 1, cmp);
	For (i, 1, N)
	{
		F[i][0][0] = F[i][0][1] = 1;
		Add(p[i].y, 0, 0, 1); Add(p[i].y, 0, 1, 1);
		For (j, 1, M)
		{
			dmod(F[i][j][0] += Query(p[i].y - 1, j, 0) + Query(p[i].y - 1, j - 1, 1));
			dmod(F[i][j][1] += Query(MH, j, 1) - Query(p[i].y, j, 1) + Query(MH, j - 1, 0) - Query(p[i].y, j - 1, 0));
			Add(p[i].y, j, 0, F[i][j][0]); Add(p[i].y, j, 1, F[i][j][1]);
		}
	}
	int Ans = 0;
	For (i, 1, N) dmod(Ans += F[i][M][0] + F[i][M][1]);
	printf("%d\n", Ans);
	return 0;
}

/*
5 1
5 5
3 2
4 4
2 3
1 1
*/
