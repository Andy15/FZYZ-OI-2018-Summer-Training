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

const int MaxN = 1100000, Inf = 1000000000;

int N, M, c[MaxN], l[MaxN], r[MaxN];

#define pa pair<int, int>
#define mkp(x, y) make_pair(x, y)
priority_queue< pa > q;

int main()
{
	scan(N), scan(M);
	if (M > N / 2) { puts("Error!"); return 0; }
	For (i, 1, N) scan(c[i]), l[i] = i - 1, r[i] = i + 1;
	l[1] = N, r[N] = 1;
	int Ans = 0;
	For (i, 1, N) q.push(mkp(c[i], i));
	For (i, 1, M)
	{
		while (q.top().first != c[q.top().second]) q.pop();
		int pos = q.top().second, L = l[pos], R = r[pos];
		Ans += c[pos]; q.pop();
		l[r[pos] = r[R]] = pos; r[l[pos] = l[L]] = pos;
		c[pos] = c[L] + c[R] - c[pos];
		c[L] = c[R] = -Inf;
		q.push(mkp(c[pos], pos));
	}
	printf("%d\n", Ans);
	return 0;
}
