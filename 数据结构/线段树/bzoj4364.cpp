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

const int MaxN = 2100000, MaxT = 10100000, MaxH = 100000;

#define L (o << 1)
#define R (L | 1)

int Mx[MaxT], Mn[MaxT], V[MaxT];

void Update_Max(int o, int qv)
{
	cmax(Mx[o], qv);
	cmax(Mn[o], qv);
}

void Update_Min(int o, int qv)
{
	cmin(Mx[o], qv);
	cmin(Mn[o], qv);
}

void Pushdown(int o)
{
	Update_Max(L, Mx[o]);
	Update_Max(R, Mx[o]);
	Update_Min(L, Mn[o]);
	Update_Min(R, Mn[o]);
	Mx[o] = 0, Mn[o] = MaxH;
}

void Change(int o, int l, int r, int ql, int qr, int qv, int opt)
{
	if (ql <= l && r <= qr)
	{
		if (opt == 1) Update_Max(o, qv);
		if (opt == 2) Update_Min(o, qv);
		return;
	}
	Pushdown(o);
	int Mid = (l + r) >> 1;
	if (ql <= Mid) Change(L, l, Mid, ql, qr, qv, opt);
	if (Mid < qr)  Change(R, Mid + 1, r, ql, qr, qv, opt);
}

void Query(int o, int l, int r, int *&out)
{
	if (l == r)
	{
		*out++ = Mx[o];
		return;
	}
	Pushdown(o);
	int Mid = (l + r) >> 1;
	Query(L, l, Mid, out), Query(R, Mid + 1, r, out);
}

void buildWall(int N, int K, int op[], int left[], int right[], int height[], int finalHeight[])
{
	For (i, 1, 5 * N) Mn[i] = MaxH;
	For (i, 0, K - 1) Change(1, 1, N, left[i] + 1, right[i] + 1, height[i], op[i]);
	Query(1, 1, N, finalHeight);
}

int main()
{
  int n;
  int k;

  int i, j;  
  int status = 0;

  status = scanf("%d%d", &n, &k);
  assert(status == 2);

  int* op = (int*)calloc(sizeof(int), k);
  int* left = (int*)calloc(sizeof(int), k);
  int* right = (int*)calloc(sizeof(int), k);
  int* height = (int*)calloc(sizeof(int), k);
  int* finalHeight = (int*)calloc(sizeof(int), n);

  for (i = 0; i < k; i++){
    status = scanf("%d%d%d%d", &op[i], &left[i], &right[i], &height[i]);
    assert(status == 4);
  }

  buildWall(n, k, op, left, right, height, finalHeight);

  for (j = 0; j < n; j++)
    printf("%d\n", finalHeight[j]);
  
  return 0;
}

