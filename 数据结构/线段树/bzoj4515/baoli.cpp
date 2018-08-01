#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define RG register
#define ll long long
#define IL inline
#define For(i, f, t) for (RG int i = f; i <= t; i++)

template<class T> void cmax(T &a, T b) { a < b ? a = b : 0; }
template<class T> void cmin(T &a, T b) { a > b ? a = b : 0; }
template<class T> T dmax(T a, T b) { return a > b ? a : b; }
template<class T> T dmin(T a, T b) { return a < b ? a : b; }

const int MaxN = 100010;
const ll inf = 123456789123456789ll;

int N, M;

int Node[MaxN], Ecnt;
struct Edges { int t, next, c; } e[MaxN << 1];
void Add()
{
	int u, v, c; scanf("%d %d %d", &u, &v, &c);
	e[++Ecnt] = (Edges) {v, Node[u], c}, Node[u] = Ecnt;
	e[++Ecnt] = (Edges) {u, Node[v], c}, Node[v] = Ecnt;
}

int Fa[MaxN], Size[MaxN], Dep[MaxN], HSon[MaxN], Top[MaxN];
int Dfn[MaxN], Last[MaxN], DfnCnt; ll Dis[MaxN], To[MaxN];

void Dfs1(int x)
{
	Size[x] = 1;
	Dep[x] = Dep[Fa[x]] + 1;
	for (int i = Node[x]; i; i = e[i].next)
	{
		int t = e[i].t; if (t == Fa[x]) continue;
		Fa[t] = x; Dis[t] = Dis[x] + e[i].c; Dfs1(t);
		Size[x] += Size[t]; if (Size[t] > Size[HSon[x]]) HSon[x] = t;
	}
}

void Dfs2(int x)
{
	Dfn[x] = ++DfnCnt;
	if (HSon[Fa[x]] == x) Top[x] = Top[Fa[x]];
	else Top[x] = x;
	if (HSon[x]) Dfs2(HSon[x]);
	for (int i = Node[x]; i; i = e[i].next)
	{
		int t = e[i].t; if (t == Fa[x] || t == HSon[x]) continue;
		Dfs2(t);
	}
}

int GetLca(int u, int v)
{
	while (Top[u] != Top[v]) Dep[Top[u]] > Dep[Top[v]] ? u = Fa[Top[u]] : v = Fa[Top[v]];
	return Dep[u] < Dep[v] ? u : v;
}

struct node
{
	node *ls, *rs;
	ll k, b, v;
}	mem[MaxN * 4], *tot = mem, *rt[MaxN];

ll qk, qb; int ql, qr;

IL void usetag(node *o, int l, int r)
{
	o->k = qk, o->b = qb;
	o->v = dmin(qk * To[l] + qb, qk * To[r] + qb);
}

void addtag(node *&o, int l, int r)
{
	if (!o)
	{
		o = tot++;
		o->ls = o->rs = 0;
		o->k = 0, o->b = o->v = inf;
	}
	bool v1 = o->k * To[l] + o->b < qk * To[l] + qb;
	bool v2 = o->k * To[r] + o->b < qk * To[r] + qb;
	if (v1 && v2) return;
	if (!v1 && !v2) { usetag(o, l, r); return; }
	int mid = (l + r) >> 1;
	bool v3 = o->k * To[mid] + o->b < qk * To[mid] + qb;
	if (v3)
	{
		if (!v1) addtag(o->ls, l, mid);
		else addtag(o->rs, mid + 1, r);
	}
	else
	{
		if (!v1) usetag(o->ls, l, mid), addtag(o->rs, mid + 1, r);
		else usetag(o->rs, mid + 1, r), addtag(o->ls, l, mid);
	}
	cmin(o->v, dmin(o->ls ? o->ls->v : inf, o->rs ? o->rs->v : inf));
}

void change1(node *&o, int l, int r)
{
	if (!o)
	{
		o = tot++;
		o->ls = o->rs = 0;
		o->k = 0, o->b = o->v = inf;
	}
	if (ql <= l && r <= qr) addtag(o, l, r);
	else
	{
		int mid = (l + r) >> 1;
		if (ql <= mid) change1(o->ls, l, mid);
		if (mid <  qr) change1(o->rs, mid + 1, r);
	}
	o->v = dmin(o->ls ? o->ls->v : inf, o->rs ? o->rs->v : inf);
}

ll query1(node *o, int l, int r)
{
	if (!o) return inf;
	if (ql <= l && r <= qr) return o->v;
	ll tmp = dmin(qk * To[dmax(l, ql)] + qb, qk * To[dmin(r, qr)] + qb);
	int mid = (l + r) >> 1;
	if (ql <= mid) cmin(tmp, query1(o->ls, l, mid));
	if (mid <  qr) cmin(tmp, query1(o->rs, mid + 1, r));
	return tmp;
}

ll Ans[MaxN];

void change2(int x, int f, ll beg, ll a)
{
	while (x != f)
	{
		cmin(Ans[x], beg);
		beg -= (Dis[x] - Dis[Fa[x]]) * a;
		x = Fa[x];
	}
	cmin(Ans[x], beg);
}

ll query2(int x, int f)
{
	ll ans = inf;
	while (x != f)
	{
		cmin(ans, Ans[x]);
		x = Fa[x];
	}
	cmin(ans, Ans[x]);
	return ans;
}

int main()
{
	scanf("%d %d", &N, &M);
	For (i, 2, N) Add();
	Dfs1(1); Dfs2(1);
	For (i, 1, N) Ans[i] = inf;
	For (i, 1, N) cmax(Last[Top[i]], Dfn[i]), To[i] = Dis[i] - Dis[Top[i]];
	For (i, 1, M)
	{
		int opt; scanf("%d", &opt);
		if (opt == 1)
		{
			int S, T, A, B; scanf("%d %d %d %d", &S, &T, &A, &B);
			int Lca = GetLca(S, T);
			change2(S, Lca, B, -A);
			change2(T, Lca, B + (Dis[S] + Dis[T] - 2 * Dis[Lca]) * A, A);
		}
		if (opt == 2)
		{
			int S, T; scanf("%d %d", &S, &T);
			int Lca = GetLca(S, T);
			printf("%lld\n", dmin(query2(S, Lca), query2(T, Lca)));
		}
	}
	return 0;
}

/*
3 5
1 2 10
2 3 20
2 1 3
1 2 3 5 6
2 2 3
1 2 3 -5 -6
2 2 3
*/
