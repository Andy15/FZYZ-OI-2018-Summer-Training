#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define RG register
#define ll long long
#define IL inline
#define For(i, f, t) for (RG int i = f; i <= t; i++)

template<class T> IL void cmax(T &a, T b) { a < b ? a = b : 0; }
template<class T> IL void cmin(T &a, T b) { a > b ? a = b : 0; }
template<class T> IL T dmax(T a, T b) { return a > b ? a : b; }
template<class T> IL T dmin(T a, T b) { return a < b ? a : b; }

const int MaxN = 100010;
const ll inf = 123456789123456789ll;

int N, M;

void scan(int &aa)
{
	char ch; bool bb;
	while (ch = getchar(), (ch < '0' || ch > '9') && ch != '-');
	ch == '-' ? (bb = 1, aa = 0) : (bb = 0, aa = ch - '0');
	while (ch = getchar(), ch >= '0' && ch <= '9') aa = aa * 10 + ch - '0';
	bb ? aa = -aa : 0;
}

int Node[MaxN], Ecnt;
struct Edges { int t, next, c; } e[MaxN << 1];
void Add()
{
	int u, v, c; scan(u), scan(v), scan(c);
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

ll qk, qb, nqk, nqb; int ql, qr;

IL void usetag(node *o, int l, int r)
{
	o->k = nqk, o->b = nqb;
	o->v = dmin(nqk * To[l] + nqb, nqk * To[r] + nqb);
}

void addtag(node *&o, int l, int r)
{
	if (!o)
	{
		o = tot++;
		o->ls = o->rs = 0;
		o->k = 0, o->b = o->v = inf;
	}
	bool v1 = o->k * To[l] + o->b < nqk * To[l] + nqb;
	bool v2 = o->k * To[r] + o->b < nqk * To[r] + nqb;
	if (v1 && v2) return;
	if (!v1 && !v2)
	{
		usetag(o, l, r);
		cmin(o->v, dmin(o->ls ? o->ls->v : inf, o->rs ? o->rs->v : inf));
		return;
	}
	int mid = (l + r) >> 1;
	bool v3 = o->k * To[mid] + o->b < nqk * To[mid] + nqb;
	if (v3)
	{
		if (!v1) addtag(o->ls, l, mid);
		else addtag(o->rs, mid + 1, r);
	}
	else
	{
		ll t_qk = o->k, t_qb = o->b;
		usetag(o, l, r);
		nqk = t_qk, nqb = t_qb;
		if (v1) addtag(o->ls, l, mid);
		else addtag(o->rs, mid + 1, r);
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
	if (ql <= l && r <= qr) { nqk = qk, nqb = qb; addtag(o, l, r); }
	else
	{
		int mid = (l + r) >> 1;
		if (ql <= mid) change1(o->ls, l, mid);
		if (mid <  qr) change1(o->rs, mid + 1, r);
	}
	cmin(o->v, dmin(o->ls ? o->ls->v : inf, o->rs ? o->rs->v : inf));
}

ll query1(node *o, int l, int r)
{
	if (!o) return inf;
	if (ql <= l && r <= qr) { return o->v; }
	ll tmp = dmin(o->k * To[dmax(l, ql)] + o->b, o->k * To[dmin(r, qr)] + o->b);
	int mid = (l + r) >> 1;
	if (ql <= mid) cmin(tmp, query1(o->ls, l, mid));
	if (mid <  qr) cmin(tmp, query1(o->rs, mid + 1, r));
	return tmp;
}

void change2(int x, int f, ll beg, ll a)
{
	while (Top[x] != Top[f])
	{
		ql = Dfn[Top[x]], qr = Dfn[x];
		qk = a, qb = beg - (Dis[x] - Dis[Top[x]]) * a;
		change1(rt[Top[x]], Dfn[Top[x]], Last[Top[x]]);
		beg -= (Dis[x] - Dis[Fa[Top[x]]]) * a;
		x = Fa[Top[x]];
	}
	ql = Dfn[f], qr = Dfn[x];
	qk = a, qb = beg - (Dis[x] - Dis[Top[x]]) * a;
//	printf("x %d fa %d qk %lld qb %lld\n", x, f, qk, qb);
	change1(rt[Top[x]], Dfn[Top[x]], Last[Top[x]]);
}

ll query2(int x, int f)
{
	ll ans = inf;
	while (Top[x] != Top[f])
	{
		ql = Dfn[Top[x]], qr = Dfn[x];
		cmin(ans, query1(rt[Top[x]], Dfn[Top[x]], Last[Top[x]]));
		x = Fa[Top[x]];
	}
	ql = Dfn[f], qr = Dfn[x];
	cmin(ans, query1(rt[Top[x]], Dfn[Top[x]], Last[Top[x]]));
	return ans;
}

int main()
{
	scan(N), scan(M);
	For (i, 2, N) Add();
	Dfs1(1); Dfs2(1);
	For (i, 1, N) cmax(Last[Top[i]], Dfn[i]), To[Dfn[i]] = Dis[i] - Dis[Top[i]];
	For (i, 1, M)
	{
		int opt; scanf("%d", &opt);
		if (opt == 1)
		{
			int S, T, A, B; scan(S), scan(T), scan(A), scan(B);
			int Lca = GetLca(S, T);
			change2(S, Lca, B, -A);
			change2(T, Lca, B + (Dis[S] + Dis[T] - 2 * Dis[Lca]) * A, A);
		}
		if (opt == 2)
		{
			int S, T; scan(S), scan(T);
			int Lca = GetLca(S, T);
			printf("%lld\n", dmin(query2(S, Lca), query2(T, Lca)));
		}
	}
	return 0;
}

