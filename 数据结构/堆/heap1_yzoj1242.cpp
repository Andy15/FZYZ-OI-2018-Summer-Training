#include <bits/stdc++.h>
using namespace std;

char b[1 << 8], *s = b, *t = b;
#define getc() (s == t && (t = (s = b) + fread(b, 1, 1 << 8, stdin), s == t) ? 0 : *s ++)

void scan(int &aa)
{
	char ch; bool bb;
	while (ch = getc(), (ch < '0' || ch > '9') && ch != '-');
	ch == '-' ? (bb = 1, aa = 0): (bb = 0, aa = ch - '0');
	while (ch = getc(), ch >= '0' && ch <= '9') aa = aa * 10 + ch - '0';
	bb? aa = -aa: 0;
}

#define RG register
#define For(i, f, t) for (RG int i = f; i <= t; ++i)


const int MaxN = 11000;
int N;

struct Heap
{
	int V[MaxN], NodeCnt;
	
	void push(int x)
	{
		RG int i;
		for (i = ++NodeCnt; V[i / 2] > x; i >>= 1)
			V[i] = V[i >> 1];
		V[i] = x;
	}
	
	int top() { return V[1]; }
	
	void pop()
	{
		RG int i, child, end = V[NodeCnt--];
		for (i = 1; i * 2 <= NodeCnt; i = child)
		{
			child = i << 1;
			if (child < NodeCnt && V[child + 1] < V[child]) child++;
			if (end > V[child]) V[i] = V[child]; else break;
		}
		V[i] = end;
	}
	
}	heap;

int main()
{
	RG int x, Ans = 0, Sum;
	scan(N);
	For (i, 1, N) scan(x), heap.push(x);
	For (i, 2, N)
	{
		Sum = 0;
		Sum += heap.top(); heap.pop();
		Sum += heap.top(); heap.pop();
		heap.push(Sum);
		Ans += Sum;
	}
	printf("%d\n", Ans);
	return 0;
}
