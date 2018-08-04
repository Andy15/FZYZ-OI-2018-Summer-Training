#include <bits/stdc++.h>
#define MAXN 111111
#define MAXP 33333
#define lowbit(o) (o & -o)
using namespace std;

int n, x[MAXN], y[MAXN], id[MAXN], a[MAXP], ans[MAXN];

inline bool cmp(register int a, register int b) {
    return x[a] == x[b] ? y[a] == y[b] ? a < b : y[a] < y[b] : x[a] < x[b];
}

void modify(register int pos, register int delta) {
    for (register int i = pos; i <= 32768; i += lowbit(i))
        a[i] += delta;
}

int query(register int pos) {
    register int ans = 0;
    for (register int i = pos; i > 0; i -= lowbit(i))
        ans += a[i];
    return ans;
}

int main() {
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i) {
        scanf("%d%d", &x[i], &y[i]); id[i] = i;
    }
    sort(id + 1, id + 1 + n, cmp);
    for (register int i = 1, cnt = 1; i <= n; ++i) {
        if (x[id[i]] == x[id[i + 1]] && y[id[i]] == y[id[i + 1]]) {
            ++cnt;
            continue;
        }
        ans[query(y[id[i]]) + cnt - 1] += cnt; modify(y[id[i]], cnt); cnt = 1;
    }
    for (register int i = 0; i < n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
