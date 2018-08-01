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

const int MaxN = 510000;

int N, M, S;
int a, b, c, d;

int Node[MaxN << 2], Ecnt;
struct Edges
{
	int l, r, next;
}	e[MaxN << 4];

int Pos[MaxN];
int q[MaxN << 2], Head, Tail;

set <int> T;
set <int>::iterator y, Tmp[MaxN];

int F[MaxN];

#define L (o << 1)
#define R (L | 1)

void Build(int o, int l, int r)
{
	if (l == r)
	{
		Pos[l] = o;
		return;
	}
	int Mid = (l + r) >> 1;
	Build(L, l, Mid), Build(R, Mid + 1, r);
}

void Insert(int o, int l, int r)
{
	if (c <= l && r <= d)
	{
		e[++Ecnt] = (Edges) {a, b, Node[o]}, Node[o] = Ecnt; 
		return;
	}
	int Mid = (l + r) >> 1;
	if (c <= Mid) Insert(L, l, Mid);
	if (Mid < d)  Insert(R, Mid + 1, r);
}

int main()
{
	scan(N), scan(M), scan(S);
	while (M--)
	{
		scan(a), scan(b), scan(c), scan(d);
		Insert(1, 1, N);
		swap(a, c); swap(b, d);
		Insert(1, 1, N);
	}
	Build(1, 1, N);
	q[Head = Tail = 1] = S;
	For (i, 1, N + 1) if (i != S) T.insert(i);
	while (Head <= Tail)
	{
		int x = q[Head ++], v = F[x] + 1;
		for (x = Pos[x]; x; Node[x] = 0, x >>= 1)
			for (int i = Node[x]; i; i = e[i].next)
			{
				int Cnt = 0;
				for (y = T.lower_bound(e[i].l); *y <= e[i].r; y++)
					q[++Tail] = *y, F[*y] = v, Tmp[++Cnt] = y;
				while (Cnt) T.erase(Tmp[Cnt--]);
			}
	}
	For (i, 1, N) printf("%d\n", F[i]);
	return 0;
}

/*
5 3 4
1 2 4 5
5 5 4 4
1 1 3 3
*/
