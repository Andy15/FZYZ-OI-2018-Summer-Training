#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
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
#define For(i, f, t) for (RG int i = f; i <= t; ++i)

const int MaxN = 100010;

int N;
struct Q
{
	int x, v, id;
}	q[MaxN << 1], Ans[MaxN << 1], Final[MaxN << 2];
int tot, Anstot, Finaltot;
bool cmp(RG Q q1, RG Q q2) { return q1.x < q2.x; }

#define pbds_queue __gnu_pbds::priority_queue<int>
pbds_queue pq;
pbds_queue::point_iterator Iter[MaxN];

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
	RG int cnt = 0;
	For (i, 1, tot)
	{
		RG int t = i;
		while (q[t].x == q[i].x && t <= tot)
		{
			if (q[t].v > 0) Iter[q[t].id] = pq.push(q[t].v), cnt++;
			else pq.erase(Iter[q[t].id]), cnt--;
			t ++;
		}
		RG int newv = cnt == 0 ? 0 : pq.top();
		if (newv != Ans[Anstot].v) Ans[++Anstot] = (Q) {q[i].x, newv};
		i = t - 1;
	}
	printf("%d\n", Anstot << 1);
	For (i, 1, Anstot)
	{
		printf("%d %d\n", Ans[i].x, Ans[i - 1].v);
		printf("%d %d\n", Ans[i].x, Ans[i].v);
	}
	return 0;
}
