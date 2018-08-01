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
int A[MaxN], Heap[MaxN << 1];

int Tot;
void Push(int x) { Heap[++Tot] = x; push_heap(Heap + 1, Heap + Tot + 1); }
int Top() { return Heap[1]; }
void Pop() { pop_heap(Heap + 1, Heap + Tot + 1); Tot--; }

int main()
{
	scan(N);
	For (i, 1, N) scan(A[i]);
	For (i, 1, N) A[i] = A[i] + N - i;
	ll B = A[1], K = -1, X;
	Push(A[1]);
	For (i, 2, N)
	{
		while (Tot + K > 0) Pop();
		X = A[i];
		--K, B += X;
		Push(X); Push(X);
	}
	while (Tot + K > 0) Pop();
	sort(Heap + 1, Heap + Tot + 1);
	B += (ll) K * Heap[1];
	For (i, 2, Tot)
		B += (ll) (++ K) * (Heap[i] - Heap[i - 1]);
	printf("%lld\n", B);
	return 0;
}

