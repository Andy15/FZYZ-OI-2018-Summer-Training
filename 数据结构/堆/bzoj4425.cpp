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

const int MaxN = 310000;

int N, M, Ans;

struct stuff { int l, r; } s[MaxN];
IL bool cmp(stuff a, stuff b) { return a.l < b.l; }
struct process
{
	int x;
	IL bool operator<(const process &a) const { return x > a.x; }
};

priority_queue<process> heap;

int main()
{
	scan(N), scan(M);
	For (i, 1, N) scan(s[i].l), scan(s[i].r), s[i].r += s[i].l;
	sort(s + 1, s + N + 1, cmp);
	heap.push((process){s[1].r + M});
	For (i, 2, N)
	{
		while (!heap.empty() && heap.top().x < s[i].l) heap.pop();
		int t = heap.top().x;
		if (t - M <= s[i].l && s[i].l <= t) Ans++, heap.pop();
		heap.push((process){s[i].r + M});
	}
	printf("%d\n", Ans);
	return 0;
}
