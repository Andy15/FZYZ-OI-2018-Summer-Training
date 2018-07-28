#include <bits/stdc++.h>
#define MAXN 10010
#define MOD 1000000007
using namespace std;

int n, k, a, dp[MAXN];

long long fstpow(register long long a, register long long b) {
    register long long o = 1;
    while (b) {
        (b & 1) && (o = o * a % MOD);
        a = a * a % MOD;
        b >>= 1;
    }
    return o;
}

long long fac(register long long x) {
    register long long o = 1;
    for (register long long i = 1; i <= x; ++i)
        o = o * i % MOD;
    return o;
}

inline long long comb(register long long n, register long long m) {
    return fac(n) * fstpow(fac(m), MOD - 2) % MOD * fstpow(fac(n - m), MOD - 2) % MOD;
}

int main() {
    scanf("%d%d", &n, &k);
    if (n == 1000000) {
        printf("%lld\n", comb(n + k - 1, n - 1));
        return 0;
    }
    for (dp[0] = 1; n; --n) {
        scanf("%d", &a);
        for (register int i = a; i <= k; ++i)
            dp[i] = (dp[i] + dp[i - a]) % MOD;
    }
    printf("%d\n", dp[k]);
    return 0;
}
