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

const int MaxN = 110000;

int N;
struct Q
{
	int x, v, id;
}	q[MaxN << 1], Ans[MaxN << 1], Final[MaxN << 2];
int tot, Anstot, Finaltot;

bool cmp(Q q1, Q q2)
{
	return q1.x < q2.x;
}

multiset<int> s;
multiset<int>::iterator Iter[MaxN];

int main()
{
	scan(N);
	For (i, 1, N)
	{
		int H, L, R; scan(H), scan(L), scan(R);
		q[++tot] = (Q) {L, H, i};
		q[++tot] = (Q) {R, -H, i};
	}
	sort(q + 1, q + tot + 1, cmp);
	For (i, 1, tot)
	{
		int x = q[i].x, v = q[i].v;
		int t = i;
		while (q[t].x == q[i].x && t <= tot)
		{
			if (q[t].v > 0) Iter[q[t].id] = s.insert(q[t].v);
			else s.erase(Iter[q[t].id]);
			t ++;
		}
		
		int newv = s.empty() ? 0 : *--s.end();
		if (newv != Ans[Anstot].v) Ans[++Anstot] = (Q) {q[i].x, newv};
		i = t - 1;
	}
	int now = 0;
	printf("%d\n", Anstot << 1);
	For (i, 1, Anstot)
	{
		printf("%d %d\n", Ans[i].x, now);
		printf("%d %d\n", Ans[i].x, Ans[i].v);
		now = Ans[i].v;
	}
	return 0;
}
