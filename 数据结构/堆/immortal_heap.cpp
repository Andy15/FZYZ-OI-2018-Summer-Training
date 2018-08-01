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
#define ll long long
#define pause() getchar()
#define For(i, f, t) for (RG int i = f; i <= t; ++i)

const int MaxN = 51000, MaxH = 15000000;

int N, M;
int Node[MaxN], Ecnt;
struct Edges
{
	int t, next, c;
}	e[MaxN << 1];
void Addedge()
{
	int u, v, c; scan(u), scan(v), scan(c);
	e[++Ecnt] = (Edges) {v, Node[u], c}, Node[u] = Ecnt;
	e[++Ecnt] = (Edges) {u, Node[v], c}, Node[v] = Ecnt;
}


struct node *tot, *last;
struct node
{
	int v, d;
	node *l, *r;
	IL int val() const { return v + d; }
	IL node *force_copy() const { return new (++tot)node(*this); }
	IL node *force_do_add(RG int _d) const { RG node *o = force_copy(); o->d += _d; return o; }
	IL node *copy() { return this > last ? this : new (++tot)node(*this); }
	IL node *do_add(RG int _d) { if (!this || !_d) return this; RG node *o = copy(); o->d += _d; return o; }
}	mem[MaxH], *T[MaxN], *U[MaxN], *V[MaxN];

node *T_merge(RG node *x, RG node *y)
{
	if (!x || !y) return x ? x : y;
	RG node *Tmp;
	if (x->val() < y->val()) Tmp = x, x = y, y = Tmp;
	x = x->copy();
	Tmp = x->l, x->l = x->r, x->r = T_merge(Tmp, y->do_add(-x->d));
	return x;
}

bool type = 1;
void next_step() { type = 0, last = tot; }
node *merge(RG node *x, RG node *y)
{
	if (!x && !y) return 0;
	if (type) last = tot;
	return T_merge(x, y)->force_copy();
}

node *pop(RG node* o)
{
	return merge(o->l->do_add(o->d), o->r->do_add(o->d));
}

bool cmp(RG int a, RG int b) { return T[a]->val() < T[b]->val(); }
int heap[MaxN];

int main()
{
	tot = mem;
	
	scan(N), scan(M); M <<= 1;
	For (i, 2, N) Addedge();
	
	static bool Vis[MaxN];
	static int q[MaxN], Head, Tail;
	q[Head = Tail = 1] = 1; Vis[1] = 1;
	while (Head <= Tail)
	{
		int x = q[Head ++];
		for (RG int j = Node[x]; j; j = e[j].next)
			if (!Vis[e[j].t]) Vis[e[j].t] = 1, q[++ Tail] = e[j].t;
	}
	
	RG int i;
	for (RG int _i = N; _i; _i--)
	{
		Vis[i = q[_i]] = 0;
		T[i] = ++tot;
		for (RG int j = Node[i]; j; j = e[j].next)
			if (!Vis[e[j].t])
			{
				V[e[j].t] = T[e[j].t]->force_do_add(e[j].c);
				T[i] = merge(T[i], V[e[j].t]);
			}
	}
	RG int Top = 0, nSon;
	For (_i, 1, N)
	{
		Vis[i = q[_i]] = 1;
		T[i] = merge(T[i], U[i]);
		heap[Top++] = i, push_heap(heap, heap + Top, cmp);
		
		static Edges son[MaxN];
		static node *l[MaxN], *r[MaxN];
		nSon = 0;
		for (RG int j = Node[i]; j; j = e[j].next)
			if (!Vis[e[j].t]) son[++nSon] = e[j];
		
		if (!nSon) continue;
		
		l[0] = U[i];
		r[nSon + 1] = ++tot;
		
		for (RG int j = 1; j <= nSon - 1; j++) l[j] = merge(l[j - 1], V[son[j].t]);
		for (RG int j = nSon; j >= 1 + 1; j--) r[j] = merge(r[j + 1], V[son[j].t]);	
		
		For (j, 1, nSon)
			U[son[j].t] = merge(l[j - 1], r[j + 1])->force_do_add(son[j].c);
	}
	next_step();
	while (--M)
	{
		pop_heap(heap, heap + Top, cmp); Top--;
		i = heap[Top];
		if (M & 1) printf("%d\n", T[i]->val());
		T[i] = pop(T[i]);
		Top++; push_heap(heap, heap + Top, cmp);
	}
	return 0;
}
