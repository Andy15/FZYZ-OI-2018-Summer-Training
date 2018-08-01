#include <bits/stdc++.h>
using namespace std;

#define RG register
#define ll long long
#define For(i, f, t) for (RG int i = f; i <= t; ++i)
#define par(x, a) For (i, 1, x) printf("%d ", a[i]); puts("");

const int MaxN = 1000010;

void scan(int &aa)
{
	char ch;
	while (ch = getchar(), ch < '0' || ch > '9'); aa = ch - '0';
	while (ch = getchar(), ch >= '0' && ch <= '9') aa = aa * 10 + ch - '0';
}

int N;
int Heap[MaxN << 1];

int Tot;
void Push(int x) { Heap[++Tot] = x; push_heap(Heap + 1, Heap + Tot + 1); }
int Top() { return Heap[1]; }
void Pop() { pop_heap(Heap + 1, Heap + Tot + 1); Tot--; }

int main()
{
	scan(N);
	ll Ans = 0;
	For (i, 1, N)
	{
		int Now; scan(Now); Now -= i;
		Push(Now);
		if (Top() > Now)
		{
			Ans += Top() - Now;
			Pop(); Push(Now);
		}
	}
	printf("%lld\n", Ans);
	return 0;
}

