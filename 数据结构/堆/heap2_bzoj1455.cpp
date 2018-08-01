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

const int MaxN = 1100000;

int N, M;
int A[MaxN];
bool Die[MaxN];

struct UFS
{
	int Fa[MaxN];
	void pre() { For (i, 1, N) Fa[i] = i; }
	int find(int x) { return Fa[x] == x ? x : Fa[x] = find(Fa[x]); }
}	ufs;

struct Heap
{
	int c[MaxN][2], d[MaxN];
	void pre()
	{
		d[0] = -1;
	}
	int merge(int x, int y)
	{
		if (!x) return y;
		if (!y) return x;
		if (A[x] > A[y]) mswap(x, y);
		c[x][1] = merge(c[x][1], y);
		if (d[c[x][0]] > d[c[x][1]]) swap(c[x][0], c[x][1]);
		d[x] = d[c[x][1]] + 1;
		return x;
	}
}	heap;

int main()
{
	scan(N);
	For (i, 1, N) scan(A[i]);
	ufs.pre();

	heap.pre();
	scan(M);
	For (m, 1, M)
	{
		RG char ch[10]; RG int x, y;
		scanf("%s", ch);
		if (ch[0] == 'M')
		{
			scan(x), scan(y);
			if (Die[x] || Die[y]) continue;
			int x2 = ufs.find(x), y2 = ufs.find(y);
			if (x2 != y2)
			{
				int t = heap.merge(x2, y2);
				ufs.Fa[x2] = ufs.Fa[y2] = t;
			}
		}
		if (ch[0] == 'K')
		{
			scan(x);
			if (Die[x]) puts("0");
			else
			{
				int x2 = ufs.find(x);
				Die[x2] = 1;
				printf("%d\n", A[x2]);
				int now = heap.merge(heap.c[x2][0], heap.c[x2][1]);
				ufs.Fa[x2] = ufs.Fa[now] = now;
			}
		}
	}
	return 0;
}
