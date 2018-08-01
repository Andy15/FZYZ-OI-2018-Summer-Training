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
IL void cmax(db &x, db y) { x < y ? x = y : 0; }
IL void mswap(int &x, int &y) { int o = x; x = y; y = o; }
IL int mabs(int x) { return x < 0 ? -x : x; }

const int MaxN = 51000;

int N = 50000, T, x;
db B[MaxN << 2], K[MaxN << 2], Ans;
bool flag[MaxN << 2];

#define L (o << 1)
#define R (L | 1)

db InterSection(db k1, db b1, db k2, db b2)
{
	return (b2 - b1) / (k1 - k2);
}

void Add(int o, int l, int r, db b, db k)
{
	if (!flag[o]) K[o] = k, B[o] = b, flag[o] = 1;
	else
	{
		int Mid = (l + r) >> 1;
		db f1 = k * l + b, f2 = K[o] * l + B[o], f3 = k * r + b, f4 = K[o] * r + B[o];
		if (f1 <= f2 && f3 <= f4) return;
		if (f1 >= f2 && f3 >= f4) K[o] = k, B[o] = b;
		else
		{
			db xx = InterSection(k, b, K[o], B[o]);
			if (f1 >= f2)
			{
				if (xx <= Mid) Add(L, l, Mid, b, k);
				else Add(R, Mid + 1, r, B[o], K[o]), K[o] = k, B[o] = b;
			}
			else
			{
				if (xx > Mid) Add(R, Mid + 1, r, b, k);
				else Add(L, l, Mid, B[o], K[o]), K[o] = k, B[o] = b;
			}
		}
	}
}

void Query(int o, int l, int r)
{
	if (flag[o]) cmax(Ans, K[o] * x + B[o]);
	if (l == r) return;
	int Mid = (l + r) >> 1;
	if (x <= Mid) Query(L, l, Mid);
	else Query(R, Mid + 1, r);
}

int main()
{
	scan(T);
	while (T--)
	{
		char ch[10];
		scanf("%s", ch);
		if (ch[0] == 'P')
		{
			db b, k;
			scanf("%lf %lf", &b, &k);
			Add(1, 1, N, b - k, k);
		}
		if (ch[0] == 'Q')
		{
			scanf("%d", &x);
			Ans = 0;
			Query(1, 1, N);
			printf("%lld\n", (ll)floor(Ans / 100.0));
		}
	}
	return 0;
}

/*
10
Project 5.10200 0.65000
Project 2.76200 1.43000
Query 4
Query 2
Project 3.80200 1.17000
Query 2
Query 3
Query 1
Project 4.58200 0.91000
Project 5.36200 0.39000
*/
