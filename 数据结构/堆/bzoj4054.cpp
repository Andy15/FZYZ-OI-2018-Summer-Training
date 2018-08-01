#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define For(i, f, t) for (int i = f; i <= t; i++)

void scan(int &aa)
{
	char ch; bool bb;
	while (ch = getchar(), (ch < '0' || ch > '9') && ch != '-');
	ch == '-' ? (bb = 1, aa = 0) : (bb = 0, aa = ch - '0');
	while (ch = getchar(), ch >= '0' && ch <= '9') aa = aa * 10 + ch - '0';
	bb ? aa = -aa : 0;
}

const int MaxN = 200010;
const ll inf = 1e18;

int n, v[MaxN];

int nodeCnt, c[MaxN][2], h[MaxN];
ll x[MaxN], y[MaxN];

int newnode(ll _x, ll _y)
{
	int o = ++nodeCnt;
	c[o][0] = c[o][1] = h[o] = 0;
	x[o] = _x, y[o]= _y;
	return o;
}

int merge(int a, int b)
{
	if (!a || !b) return a ^ b;
	if (x[a] > x[b]) swap(a, b);
	c[a][1] = merge(c[a][1], b);
	if (h[c[a][0]] < h[c[a][1]]) swap(c[a][0], c[a][1]);
	h[a] = h[c[a][1]] + 1;
	return a;
}

int node[MaxN], Ecnt;
struct Edges { int t, next; } e[MaxN << 1];
void Add(int u, int v)
{
	e[++Ecnt] = (Edges) {v, node[u]}, node[u] = Ecnt;
	e[++Ecnt] = (Edges) {u, node[v]}, node[v] = Ecnt;
}

int root[MaxN], End;

void Dfs(int now, int fa)
{
	root[now] = 0;
	if (now == End)
	{
		root[now] = newnode(0, inf);
		if (v[now] < 0) x[root[now]] = -v[now];
		return;
	}
	for (int i = node[now]; i; i = e[i].next)
	{
		int t = e[i].t; if (t == fa) continue;
		Dfs(t, now);
		root[now] = merge(root[now], root[t]);
	}
	if (v[now] < 0)
	{
		int tmp = newnode(-v[now], 0);
		while (root[now] && (x[tmp] > x[root[now]] || x[tmp] >= y[tmp]))
		{
			if (y[tmp] >= x[root[now]])
			{
				y[tmp] = y[tmp] - x[root[now]] + y[root[now]];
			}
			else
			{
				x[tmp] = x[tmp] + x[root[now]] - y[tmp]; 
				y[tmp] = y[root[now]];
			}
			root[now] = merge(c[root[now]][0], c[root[now]][1]);
		}
		if (x[tmp] < y[tmp]) root[now] = merge(root[now], tmp);
	}
	else
	{
		ll sum = v[now];
		while (root[now] && x[root[now]] <= sum)
		{
			sum = sum - x[root[now]] + y[root[now]];
			root[now] = merge(c[root[now]][0], c[root[now]][1]);
		}
		root[now] = merge(root[now], newnode(0, sum));
	}
}

void Solve()
{
	scan(n); scan(End);
	Ecnt = 0; For (i, 1, n) node[i] = 0;
	nodeCnt = 0;
	For (i, 1, n) scan(v[i]);
	For (i, 2, n) { int u, v; scan(u), scan(v); Add(u, v); }
	Dfs(1, 0);
	if (y[root[1]] > inf / 2) puts("escaped");
	else puts("trapped");
}

int main()
{
	int T; scanf("%d", &T);
	For (t, 1, T) Solve();
	return 0;
}

