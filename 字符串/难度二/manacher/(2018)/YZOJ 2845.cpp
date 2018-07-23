#include <bits/stdc++.h>
#define MAXN 300010
#define MAXS 30
#define sigma 26
#define idx(o) (o - 'a')
using namespace std;

struct PalindromicAutoMata {
    int nxt[MAXN][MAXS], f[MAXN], cnt[MAXN], num[MAXN], len[MAXN], s[MAXN], lst, n, p;

    int add(register int o) {
        for (register int i = 0; i < sigma; ++i)
            nxt[p][i] = 0;
        cnt[p] = num[p] = 0; len[p] = o;
        return p++;
    }

    int getFail(register int o) {
        while (s[n - len[o] - 1] != s[n])
            o = f[o];
        return o;
    }

    void insert(register int o) {
        o = idx(o); s[++n] = o;
        register int cur = getFail(lst);
        if (!nxt[cur][o]) {
            register int now = add(len[cur] + 2);
            f[now] = nxt[getFail(f[cur])][o]; nxt[cur][o] = now; num[now] = num[f[now]] + 1;
        }
        lst = nxt[cur][o]; ++cnt[lst];
    }

    void count() {
        for (register int i = p - 1; i >= 0; --i)
            cnt[f[i]] += cnt[i];
    }

    PalindromicAutoMata() {
        p = 0; add(0); add(-1); lst = n = 0; s[n] = -1; f[0] = 1;
    }
} probkiller_night;

int n;
long long ans;
char s[MAXN];

inline void cmax(register long long &a, register long long b) {
    (a < b) && (a = b);
}

int main() {
    scanf("%s", s + 1); n = strlen(s + 1);
    for (register int i = 1; i <= n; ++i)
        probkiller_night.insert(s[i]);
    probkiller_night.count();
    for (register int i = probkiller_night.p - 1; i >= 0; --i)
        cmax(ans, (long long) probkiller_night.cnt[i] * probkiller_night.len[i]);
    printf("%lld\n", ans);
    return 0;
}
