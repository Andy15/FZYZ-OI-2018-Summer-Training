#include <bits/stdc++.h>
#define MAXN 5010
using namespace std;

int n, a[MAXN], top[MAXN], s;

int main() {
    scanf("%d", &n);
    for (register int i = n + 1, i_lim = n << 1; i <= i_lim; ++i) {
        scanf("%d", &a[i]); a[n * 2 + 1 - i] = a[i];
    }
    for (register int i = 1, i_lim = n << 1; i <= i_lim; ++i) {
        register int l = 1, r = s + 1, mid;
		while (l < r)
			(top[mid = (l + r) >> 1] < a[i]) ? (l = mid + 1) : (r = mid);
		top[l] = a[i]; (s < l) && (s = l);
    }
    printf("%d", s);
    return 0;
}
