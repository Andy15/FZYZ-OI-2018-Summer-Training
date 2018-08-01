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

const int MaxN = 1000010, Inf = 1e9, Mod = 1e9 + 7;

int N;
int c[MaxN], d[MaxN], g[MaxN];

struct Node
{
	int x, y;
	Node(int _x = 0, int _y = 0) { x = _x, y = _y; }
	IL  Node operator + (const Node &b)
	{
		if (x != b.x) return x > b.x ? Node(x, y) : b;
		return Node(x, (y + b.y) % Mod);
	}
	IL Node operator + (int tx)
	{
		return Node(x + tx, y);
	}
	IL void operator += (const Node &b) { *this = *this + b; } 
}	F[MaxN];

#define L (o << 1)
#define R (L | 1)

struct Seg
{
	int pos, val;
	Node f, flag;
}	T[(MaxN << 1) + (int)1e5];

int ql, qr, qx;

IL void Build1(int o, int l, int r)
{
	if (l == r)
	{
		T[o].pos = l;
		T[o].val = d[l];
		return;
	}
	int Mid = (l + r) >> 1;
	Build1(L, l, Mid), Build1(R, Mid + 1, r);
	T[o].pos = c[T[L].pos] > c[T[R].pos] ? T[L].pos : T[R].pos;
	T[o].val = dmin(T[L].val, T[R].val);
}

IL void Build2(int o, int l, int r)
{
	T[o].flag = (Node){-1000000, 0};
	if (l == r)
	{
		T[o].val = d[l];
		T[o].f = F[l];
		return;
	}
	int Mid = (l + r) >> 1;
	Build2(L, l, Mid), Build2(R, Mid + 1, r);
	T[o].f = T[L].f + T[R].f;
	T[o].val = dmin(T[L].val, T[R].val);
}

IL void Modify_Add(int o, int l, int r, const Node& delta)
{
	if (ql <= l && r <= qr)
	{
		T[o].flag += delta;
		return;
	}
	int Mid = (l + r) >> 1;
	if (ql <= Mid) Modify_Add(L, l, Mid, delta);
	if (Mid < qr)  Modify_Add(R, Mid + 1, r, delta);
}

IL void Modify_cov(int o, int l, int r, const Node& delta)
{
	if (l == r)
	{
		T[o].f = delta;
		return;
	}
	int Mid = (l + r) >> 1;
	if (qx <= Mid) Modify_cov(L, l, Mid, delta);
	else Modify_cov(R, Mid + 1, r, delta);
	T[o].f = T[L].f + T[R].f;
}

IL Node Ask(int x)
{
	int o = 1, l = 0, r = N, Mid = (l + r) >> 1;
	Node t = Node(-1000000, 0);
	while (l != r)
	{
		t += T[o].flag;
		Mid = (l + r) >> 1;
		if (x <= Mid) o = L, r = Mid;
		else o = R, l = Mid + 1;
	}
	t += T[o].flag;
	return t;
}

IL int Query_c(int o, int l, int r)
{
	if (ql <= l && r <= qr) return T[o].pos;
	int Mid = (l + r) >> 1, Tmp1 = -1000000, Tmp2 = -1000000;
	if (ql <= Mid) Tmp1 = Query_c(L, l, Mid);
	if (Mid < qr)  Tmp2 = Query_c(R, Mid + 1, r);
	if (Tmp1 == -1000000 || Tmp2 == -1000000) return Tmp1 == -1000000 ? Tmp2 : Tmp1;
	return c[Tmp1] > c[Tmp2] ? Tmp1 : Tmp2;
}

IL int Query_d(int o, int l, int r)
{
	if (ql <= l && r <= qr) return T[o].val;
	int Mid = (l + r) >> 1, Tmp = 1000000;
	if (ql <= Mid) cmin(Tmp, Query_d(L, l, Mid));
	if (Mid < qr)  cmin(Tmp, Query_d(R, Mid + 1, r));
	return Tmp;
}

IL Node Query_f(int o, int l, int r)
{
	if (ql > qr) return Node(-1000000, 0);
	if (ql <= l && r <= qr) return T[o].f;
	int Mid = (l + r) >> 1;
	if (!(ql <= Mid)) return Query_f(R, Mid + 1, r);
	else if (!(Mid < qr))  return Query_f(L, l, Mid);
	else return Query_f(L, l, Mid) + Query_f(R, Mid + 1, r);
}

IL void Update(int l, int Mid, int r)
{
	int i = dmax(c[Mid] + l, Mid);
	if (i > r || g[i] >= Mid) return;
	int newl = dmax(l, g[i]), newr = i - c[Mid];
	ql = newl, qr = newr; Node Tmp = Query_f(1, 0, N) + 1;
	for (; i <= Mid - 1 + c[Mid] && i <= r; i++)
	{
		if (g[i] > newl)
		{
			if (g[i] >= Mid) return;
			newl = g[i];
			ql = newl, qr = newr, Tmp = Query_f(1, 0, N) + 1;
		}
		F[i] += Tmp; newr ++;
		if (newr >= newl) Tmp += F[newr] + 1;
	}
	while (i <= r)
	{
		if (g[i] > newl)
		{
			if (g[i] >= Mid) return;
			newl = g[i];
		}
		ql = newl, qr = Mid - 1, Tmp = Query_f(1, 0, N) + 1;
		ql = newl + 1, qr = N; int t = Query_d(1, 0, N);
		if (t > r) { ql = i, qr = r, Modify_Add(1, 0, N, Tmp); return; }
		ql = i, qr = t - 1, Modify_Add(1, 0, N, Tmp); i = t;
	}
}

IL void Solve(RG int l, RG int r)
{
	if (l == r)
	{
		if (l) qx = l, Modify_cov(1, 0, N, F[l] = F[l] + Ask(l));
		return;
	}
	ql = l + 1, qr = r;
	int Mid = Query_c(1, 0, N);
	Solve(l, Mid - 1); Update(l, Mid, r); Solve(Mid, r);
}

int main()
{
	scan(N);
	For (i, 1, N) scan(c[i]), scan(d[i]);
	Build1(1, 0, N);
	For (i, 0, N) d[i] = N + 1, F[i] = Node(-1000000, 0);
	F[0] = Node(0, 1);
	int j = 0;
	For (i, 0, N)
	{
		while (1)
		{
			ql = j + 1, qr = i;
			if (!(j < i && i - j > Query_d(1, 0, N))) break;
			j++;
		}
		g[i] = j;
		if (d[g[i]] > N) d[g[i]] = i;
	}
//	For (i, 0, N) printf("%d ", g[i]); puts("");
	Build2(1, 0, N);
	Solve(0, N);
//	for (int i = 0; i <= N; i++) printf("%d %d\n", F[i].x, F[i].y);
	if (F[N].x > 0) printf("%d %d\n", F[N].x, F[N].y);
	else puts("NIE");
	return 0;
}

/*
9
1 4
2 5
3 4
1 5
1 1
2 5
3 5
1 3
1 1
*/
