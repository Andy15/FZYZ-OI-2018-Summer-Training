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

struct Pair
{
	int fir, sec;
};
#define mkP(x, y) (Pair) {x, y}

unsigned int rand_cur, rand_x = 1401010315, rand_y = 1000000007;
unsigned int rand_int()
{
	return rand_cur = rand_cur * rand_x + rand_y;
}

int N, M;

int NodeCnt, rt, c[MaxT][2];
int v[MaxT], Sum[MaxT], Size[MaxT], Mx[MaxT], Lx[MaxT], Rx[MaxT]; 
bool RevTag[MaxT], SetTag[MaxT];

int q[MaxT], qtot;
int GetUse()
{
	if (qtot) return q[qtot--];
	else return ++NodeCnt;
}
void RecUse(int x) { q[++qtot] = x; }

void Pushup(int x)
{
	if (!x) return;
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
	if (!x) return;
	RevTag[x] ^= 1;
	swap(Lx[x], Rx[x]);
	swap(c[x][0], c[x][1]);
}

void Pushdown(int x)
{
	if (!x) return;
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


void Print(int x)
{
	if (!x) return;
	Pushdown(x);
	Print(c[x][0]);
	printf("%d ", v[x]);
	Print(c[x][1]);
}

void PrintA(int x)
{
//	printf("rt %d, ", rt);
	Print(x);
	puts("");
}

inline Pair Split(RG int x, RG int k)
{
	if (!x) return mkP(0, 0);
	Pushdown(x);
	if (Size[c[x][0]] >= k)
	{
		RG Pair tmp = Split(c[x][0], k);
		c[x][0] = tmp.sec;
		Pushup(x);
		return mkP(tmp.fir, x);
	}
	else
	{
		RG Pair tmp = Split(c[x][1], k - Size[c[x][0]] - 1);
		c[x][1] = tmp.fir;
		Pushup(x);
		return mkP(x, tmp.sec);
	}
}

inline int Merge(RG int x, RG int y)
{
	if (!x || !y) return x + y;
	if (rand_int() % (Size[x] + Size[y]) < Size[x])
	{
		Pushdown(x);
		c[x][1] = Merge(c[x][1], y);
		Pushup(x);
		return x;
	}
	else
	{
		Pushdown(y);
		c[y][0] = Merge(x, c[y][0]);
		Pushup(y);
		return y;
	}
}

int Build(int l, int r)
{
	if (l == r)
	{
		int c, x = GetUse(); scanf("%d", &c);
		v[x] = Sum[x] = Mx[x] = c; Size[x] = 1;
		if (v[x] >= 0) Lx[x] = Rx[x] = c;
		else Lx[x] = Rx[x] = 0;
		return x;
	}
	int Mid = (l + r) >> 1;
	int ls = Build(l, Mid), rs = Build(Mid + 1, r);
	int x = Merge(ls, rs);
	Pushup(x);
	return x;
}

void Insert(int pos, int tot)
{
	Pair p = Split(rt, pos);
	rt = Merge(Merge(p.fir, Build(1, tot)), p.sec);
}

void Rec(int x)
{
	if (!x) return;
	Rec(c[x][0]); Rec(c[x][1]);
	RecUse(x);
	c[x][0] = c[x][1] = 0;
	RevTag[x] = SetTag[x] = 0;
}

void Delete(int pos, int tot)
{
	RG Pair p1 = Split(rt, pos - 1), p2 = Split(p1.sec, tot);
	Rec(p2.fir);
	rt = Merge(p1.fir, p2.sec);
}

void Reverse(int pos, int tot)
{
	RG Pair p1 = Split(rt, pos - 1), p2 = Split(p1.sec, tot);
	UseRev(p2.fir);
	rt = Merge(Merge(p1.fir, p2.fir), p2.sec);
}

void Get_Sum(int pos, int tot)
{
	RG Pair p1 = Split(rt, pos - 1), p2 = Split(p1.sec, tot);
	printf("%d\n", Sum[p2.fir]);
	rt = Merge(Merge(p1.fir, p2.fir), p2.sec);
}

void Make_Same(int pos, int tot, int c)
{
	RG Pair p1 = Split(rt, pos - 1), p2 = Split(p1.sec, tot);
	UseSet(p2.fir, c);
	rt = Merge(Merge(p1.fir, p2.fir), p2.sec);
}

int main()
{
	scanf("%d %d", &N, &M);
	Mx[0] = -inf;
	rt = Build(1, N);
//	PrintA(rt);
	For (i, 1, M)
	{
//		cerr << "case " << i << endl;
		char ch[10]; scanf("%s", ch);
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
//		PrintA(rt);
	}
	return 0;
}

