#include <bits/stdc++.h>

using namespace std;

#define RG register
#define For(i, f, t) for (RG int i = f; i <= t; i++)

void scan(int &aa)
{
	char ch; bool bb;
	while (ch = getchar(), (ch < '0' || ch > '9') && ch != '-');
	ch == '-' ? (bb = 1, aa = 0) : (bb = 0, aa = ch - '0');
	while (ch = getchar(), ch >= '0' && ch <= '9') aa = aa * 10 + ch - '0';
	bb ? aa = -aa : 0;
}

const int MaxT = 1000010, inf = 1e9;

int N, M, rt, Cnt;
int a[MaxT], id[MaxT], fa[MaxT], c[MaxT][2];
int v[MaxT], Sum[MaxT], Size[MaxT], Mx[MaxT], Lx[MaxT], Rx[MaxT];
bool RevTag[MaxT], SetTag[MaxT];

int q[MaxT], qtot;

void Pushup(int x)
{
	int l = c[x][0], r = c[x][1];
	Sum[x] = Sum[l] + Sum[r] + v[x];
	Size[x] = Size[l] + Size[r] + 1;
	Mx[x] = max(Mx[l], Mx[r]);
	Mx[x] = max(Mx[x], Rx[l] + v[x] + Lx[r]);
	Lx[x] = max(Lx[l], Sum[l] + v[x] + Lx[r]);
	Rx[x] = max(Rx[r], Sum[r] + v[x] + Rx[l]); 
}

void UseSet(int x, int c)
{
	if (!x) return;
	SetTag[x] = 1;
	v[x] = c;
	Sum[x] = Size[x] * c;
	if (v[x] >= 0) Lx[x] = Rx[x] = Mx[x] = Sum[x];
	else Lx[x] = Rx[x] = 0, Mx[x] = Sum[x];
}

void UseRev(int x)
{
	RevTag[x] ^= 1;
	swap(Lx[x], Rx[x]);
	swap(c[x][0], c[x][1]);
}

void Pushdown(int x)
{
//	printf("%d %d\n", x, RevTag[x]);
	int l = c[x][0], r = c[x][1];
	if (SetTag[x])
	{
		UseSet(l, v[x]);
		UseSet(r, v[x]);
		SetTag[x] = 0;
	}
	if (RevTag[x])
	{
		UseRev(l);
		UseRev(r);
		RevTag[x] ^= 1;
	}
}

void Rotate(int x, int &k)
{
	int y = fa[x], z = fa[y];
	bool l = (c[y][1] == x), r = l ^ 1;
	if (y == k) k = x;
	else c[z][c[z][1] == y] = x;
	fa[y] = x; fa[x] = z; fa[c[x][r]] = y;
	c[y][l] = c[x][r]; c[x][r] = y;
	Pushup(y);
}

void Splay(int x, int &k)
{
	while (x != k)
	{
		int y = fa[x], z = fa[y];
		if (y != k)
		{
			if ((c[y][0] == x) ^ (c[z][0] == y)) Rotate(x, k);
			else Rotate(y, k);
		}
		Rotate(x, k);
	}
	Pushup(x);
}

int Find(int x, int rk)
{
	Pushdown(x);
	if (Size[c[x][0]] + 1 == rk) return x;
	if (Size[c[x][0]] >= rk) return Find(c[x][0], rk);
	return Find(c[x][1], rk - Size[c[x][0]] - 1);
}

void print(int x)
{
	if (!x) return;
	Pushdown(x);
//	printf("L1 x = %d v = %d ls = %d rs = %d fa = %d\n", x, v[x], c[x][0], c[x][1], fa[x]);
	print(c[x][0]);
	printf("%d ", v[x]);
//	printf("L2 x = %d v = %d ls = %d rs = %d fa = %d\n", x, v[x], c[x][0], c[x][1], fa[x]);
	print(c[x][1]);
//	printf("L3 x = %d v = %d ls = %d rs = %d fa = %d\n", x, v[x], c[x][0], c[x][1], fa[x]);
}

void PrintA()
{
//	printf("rt %d\n", rt);
//	puts("Case");
//	print(rt);
//	puts("");
}

void Build(int l, int r, int f)
{
	if (l > r) return;
	int Mid = (l + r) >> 1, x = id[Mid], last = id[f];
	if (l == r)
	{
		Sum[x] = a[l]; Size[x] = 1;
		RevTag[x] = SetTag[x] = 0;
		if (a[l] >= 0) Lx[x] = Rx[x] = Mx[x] = Sum[x];
		else Lx[x] = Rx[x] = 0, Mx[x] = Sum[x];
	}
	else Build(l, Mid - 1, Mid), Build(Mid + 1, r, Mid);
	v[x] = a[Mid];
	fa[x] = last;
	Pushup(x);
	c[last][Mid > f] = x;
//	printf("x = %d fa = %d ls = %d rs = %d size = %d sum = %d\n", x, fa[x], c[x][0], c[x][1], Size[x], Sum[x]);
}

int Split(int pos, int tot)
{
//	printf("Split %d %d\n", pos, tot);
	int x = Find(rt, pos), y = Find(rt, pos + tot + 1);
	Splay(x, rt); Splay(y, c[x][1]);
	return c[y][0];
}

void Insert(int pos, int tot)
{
	For (i, 1, tot) scan(a[i]);
	For (i, 1, tot)
	{
		if (qtot) id[i] = q[qtot--];
		else id[i] = ++Cnt;
	}
	Build(1, tot, 0);
	int z = id[(tot + 1) >> 1];
	int x = Find(rt, pos + 1), y = Find(rt, pos + 2);
	Splay(x, rt); Splay(y, c[x][1]);
	fa[z] = y; c[y][0] = z;
	Pushup(y); Pushup(x);
}

void Rec(int x)
{
	if (!x) return;
	Rec(c[x][0]); Rec(c[x][1]);
	q[++qtot] = x;
	fa[x] = c[x][0] = c[x][1] = 0;
	RevTag[x] = SetTag[x] = 0;
}

void Delete(int pos, int tot)
{
	int x = Split(pos, tot), y = fa[x];
	Rec(x); c[y][0] = 0;
	Pushup(y); Pushup(fa[y]);
}

void Reverse(int pos, int tot)
{
	int x = Split(pos, tot), y = fa[x];
	UseRev(x);
	Pushup(y); Pushup(fa[y]);
}

void Make_Same(int pos, int tot, int c)
{
	int x = Split(pos, tot), y = fa[x];
	UseSet(x, c);
	Pushup(y); Pushup(fa[y]);
}

void Get_Sum(int pos, int tot)
{
	int x = Split(pos, tot);
	printf("%d\n", Sum[x]);
}

int main()
{
	scan(N), scan(M);
	char ch[10];
	Mx[0] = a[1] = a[N + 2] = -inf; 
	For (i, 1, N) scan(a[i + 1]);
	For (i, 1, N + 2) id[i] = i;
	Build(1, N + 2, 0);
	rt = (N + 3) >> 1; Cnt = N + 2;
	PrintA();
	For (i, 1, M)
	{
//		printf("case %d\n", i);
		scanf("%s", ch);
		int pos, tot, c;
		if (!(ch[0] == 'M' && ch[2] == 'X')) scan(pos), scan(tot);
		if (ch[0] == 'I') Insert(pos, tot);
		if (ch[0] == 'D') Delete(pos, tot);
		if (ch[0] == 'R') Reverse(pos, tot);
		if (ch[0] == 'G') Get_Sum(pos, tot);
		if (ch[0] == 'M')
		{
			if(ch[2] == 'X') printf("%d\n", Mx[rt]);
			else { scan(c); Make_Same(pos, tot, c);}
		}
		PrintA();
	}
	return 0;
}
