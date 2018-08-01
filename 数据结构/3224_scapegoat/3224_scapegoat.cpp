#include <bits/stdc++.h>

using namespace std;

#define RG register
#define db double
#define For(i, f, t) for (RG int i = f; i <= t; i++)

void scan(int &aa)
{
	char ch; bool bb;
	while (ch = getchar(), (ch < '0' || ch > '9') && ch != '-');
	ch == '-' ? (bb = 1, aa = 0) : (bb = 0, aa = ch - '0');
	while (ch = getchar(), ch >= '0' && ch <= '9') aa = aa * 10 + ch - '0';
	bb ? aa = -aa : 0;
}

const int MaxT = 100010, inf = 1e9;
const db alpha = 0.75;

int N;

int rt, NodeCnt, fa[MaxT], c[MaxT][2];
int v[MaxT], Size1[MaxT], Size2[MaxT];
bool UnDel[MaxT];

void Pushup(int x)
{
	Size1[x] = Size1[c[x][0]] + Size1[c[x][1]] + UnDel[x];
	Size2[x] = Size2[c[x][0]] + Size2[c[x][1]] + 1;
}

int NewNode(int C)
{
	int x = ++NodeCnt;
	Size1[x] = Size2[x] = UnDel[x] = 1;
	v[x] = C;
	return x; 
}

int a[MaxT], atot;
void RecDfs(int o)
{
	if (!o) return;
	RecDfs(c[o][0]);
	if (UnDel[o]) a[++atot] = o;
	RecDfs(c[o][1]);
}

int Build(int l, int r)
{
	if (l > r) return 0;
	int mid = (l + r) >> 1;
	int o = a[mid];
	int ls = Build(l, mid - 1), rs = Build(mid + 1, r);
	c[o][0] = ls; c[o][1] = rs;
	if (ls) fa[ls] = o;
	if (rs) fa[rs] = o;
	Pushup(o);
	return o;
}

void printson(int o)
{
	if (!o) return;
	printson(c[o][0]);
	printf("%d ", v[o]);
	printson(c[o][1]);
}

void Rebuild(int o)
{
	atot = 0;
	int tmpfa = fa[o];
	RecDfs(o);
	int x = Build(1, atot);
	if (o == rt) rt = x, fa[x] = 0;
	else fa[x] = tmpfa, c[tmpfa][c[tmpfa][1] == o] = x;
	while (fa[x]) Pushup(fa[x]), x = fa[x];
}

bool isbad(int o)
{
	return Size2[c[o][0]] > Size2[o] * alpha + 5 || Size2[c[o][1]] > Size2[o] * alpha + 5;
}

int Ins(int &o, int C)
{
	if (!o) { o = NewNode(C); return 0; }
	int x = Ins(c[o][C >= v[o]], C); fa[c[o][C >= v[o]]] = o;
	if (isbad(o)) x = o;
	Pushup(o);
	return x;
}

void Insert(int c)
{
	int x = Ins(rt, c);
	if (x) Rebuild(x);
}

int Rank(int C) // 小于C的数的个数+1
{
	int o = rt;
	int ans = 1;
	while (o)
	{
		if (v[o] >= C) o = c[o][0];
		else
		{
			ans += Size1[c[o][0]] + UnDel[o]; 
			o = c[o][1];
		}
	}
	return ans;
}

int Kth(int k) // 第k大的数
{
	int o = rt;
	while (o)
	{
		if (Size1[c[o][0]] + 1 == k && UnDel[o]) return v[o];
		if (Size1[c[o][0]] >= k) o = c[o][0];
		else k = k - Size1[c[o][0]] - UnDel[o], o = c[o][1];
	}
}

void Erase(int o, int k)
{
	int num = Size1[c[o][0]] + UnDel[o];
	if (UnDel[o] && num == k) UnDel[o] = 0;
	else if (k <= num) Erase(c[o][0], k);
	else Erase(c[o][1], k - num);
	Pushup(o);
}

void Erase(int k)
{
	Erase(rt, Rank(k));
	if (Size1[rt] < alpha * Size2[rt]) Rebuild(rt);
}

int main()
{
	scan(N);
	For (i, 1, N)
	{
		int opt, x; scan(opt); scan(x);
//		printf("case %d\n", i);
		if (opt == 1) Insert(x);
		if (opt == 2) Erase(x);
		if (opt == 3) printf("%d\n", Rank(x));
		if (opt == 4) printf("%d\n", Kth(x));
		if (opt == 5) printf("%d\n", Kth(Rank(x) - 1));
		if (opt == 6) printf("%d\n", Kth(Rank(x + 1))); 
//		printson(rt); puts("");
	}
	return 0;
}

