#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;

template<class T> void scan(T &aa)
{
	char ch;
	while (ch = getchar(), ch < '0' || ch > '9'); aa = ch - '0';
	while (ch = getchar(), ch >= '0' && ch <= '9') aa = aa * 10 + ch - '0';
}

#define RG register
#define IL inline
#define For(i, f, t) for (RG int i = f; i <= t; ++i)
IL int dmin(int x, int y) { return x < y ? x : y; }
IL int dmax(int x, int y) { return x > y ? x : y; }
IL void cmin(int &x, int y) { x > y ? x = y : 0; }
IL void cmax(int &x, int y) { x < y ? x = y : 0; }
IL void mswap(int &x, int &y) { int o = x; x = y; y = o; }

const int MaxN = 105;

int N, M;
short A[MaxN][MaxN];
bool Vis1[MaxN][MaxN], Vis2[MaxN][MaxN];
int Ans = 0;

struct Node
{
	short x, y, h;
	bool operator< (const Node &a) const
	{
		return h > a.h;
	}
};
__gnu_pbds::priority_queue<Node> pq;

int addx[4] = {0, 0, 1, -1}, addy[4] = {1, -1, 0, 0};

void Dfs(short x, short y, short h)
{
//	printf("%d %d %d\n", x, y, h);
//	getchar();
	For (i, 0, 3)
	{
		int nx = x + addx[i], ny = y + addy[i];
		if (!(1 <= nx && nx <= N && 1 <= ny && ny <= M)) continue;
		if (Vis1[nx][ny]) continue;
		if (A[nx][ny] <= h) Ans += h - A[nx][ny], Vis1[nx][ny] = 1, Dfs(nx, ny, h);
		else if (!Vis2[nx][ny]) Vis2[nx][ny] = 1, pq.push((Node) {nx, ny, A[nx][ny]});
	}
}

int main()
{
	scan(N), scan(M);
	For (i, 1, N)
		For (j, 1, M)
		{
			scan(A[i][j]);
			Vis1[i][j] = Vis2[i][j] = 0;
			if (i == 1 || i == N || j == 1 || j == M) Vis2[i][j] = 1, pq.push((Node) {i, j, A[i][j]});
		}
	while (!pq.empty())
	{
		Node now = pq.top(); pq.pop();
		if (!Vis1[now.x][now.y]) Vis1[now.x][now.y] = 1, Dfs(now.x, now.y, now.h);
	}
	printf("%d\n", Ans);
	return 0;
}
