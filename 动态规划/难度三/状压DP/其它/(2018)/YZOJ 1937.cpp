#include <bits/stdc++.h>
#define MAXN 30
using namespace std;

int n, m, item[MAXN], bag[MAXN], itemtot, l, mid, r, ans = -1;

inline bool dfs(register int x) {
    if (x == n + 1)
        return 1;
    register bool suc;
    for (register int i = mid; i; --i) {
        if (bag[i] >= item[x]) {
            bag[i] -= item[x];
            suc = dfs(x + 1);
            bag[i] += item[x];
            if (suc)
                return 1;
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &n, &m); r = m;
    for (register int i = 1; i <= n; ++i)
        scanf("%d", &item[i]), itemtot += item[i];
    for (register int i = 1; i <= m; ++i)
        scanf("%d", &bag[i]);
    sort(bag + 1, bag + m + 1, greater<int>());
	sort(item + 1, item + n + 1, greater<int>());
    for (register int i = 1, temp = 0; i <= m; ++i) {
        temp += bag[i];
        if (temp >= itemtot) {
            l = i;
            break;
        }
    }
    while (l <= r)
        mid = (l + r) >> 1, (dfs(1)) ? (ans = mid, r = mid - 1) : l = mid + 1;
    printf("%d", ans);
    return 0;
}
