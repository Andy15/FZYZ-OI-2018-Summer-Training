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

const int MaxN = 110000, Inf = 1000000000;

int S = 1, T, A[MaxN];
int N, M;
int c[MaxN], l[MaxN], r[MaxN];

#define pa pair<int, int>
#define mkp(x, y) make_pair(x, y)
priority_queue< pa, vector<pa> , greater<pa> > q;

int main()
{
	scan(T), scan(M);
	For (i, 1, T) scan(A[i]);
	while (A[T] <= 0) T--;
	while (A[S] <= 0) S++;
	for (; S <= T; S++)
		if (!((A[S] > 0) ^ (A[S - 1] > 0)))
			c[N] += A[S];
		else c[++N] = A[S];
	int Ans = 0;
	For (i, 1, N)
		if (c[i] > 0) Ans += c[i], M--;
		else c[i] = -c[i];
	if (M >= 0) { printf("%d\n", Ans); return 0; }
	
	For (i, 1, N)
		l[i] = i - 1, r[i] = i + 1, q.push(pa(c[i], i));
	l[1] = r[N] = 0;
	For (i, 1, N) q.push(mkp(c[i], i));
	For (i, 1, -M)
	{
		while (q.top().first != c[q.top().second]) q.pop();
		int pos = q.top().second, L = l[pos], R = r[pos];
		Ans -= c[pos]; q.pop();
		l[r[pos] = r[R]] = pos; r[l[pos] = l[L]] = pos;
		c[pos] = L && R ? dmin(Inf, c[L] + c[R] - c[pos]) : Inf;
		c[L] = c[R] = Inf;
		q.push(mkp(c[pos], pos));
	}
	printf("%d\n", Ans);
	return 0;
}
