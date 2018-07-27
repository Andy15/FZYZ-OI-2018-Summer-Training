#include <bits/stdc++.h>
#define MAXN 200010
using namespace std;

int n, a[MAXN], top[MAXN], tail;

int Binary_Search(register int x) {
	register int l = 1, r = tail, mid;
	while (l <= r)
		(top[mid = (l + r) >> 1] < x) ? (l = mid + 1) : (r = mid - 1);
	return l;
}

int main() {
	scanf("%d", &n);
	for (register int i = 1, pos; i <= n; ++i) {
		scanf("%d", &a[i]);
		(a[i] > top[tail]) ? (top[++tail] = a[i]) : (pos = Binary_Search(a[i]), top[pos] = a[i]);
	}
	printf("%d", tail);
	return 0;
}
