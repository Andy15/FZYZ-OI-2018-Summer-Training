#include <bits/stdc++.h>
using namespace std;

long long phi(register long long o) {
    register long long res = o;
    for (register long long i = 2; i * i <= o; ++i) {
        if (o % i)
            continue;
        res = res - res / i;
        while (!(o % i))
            o /= i;
    }
    o > 1 && (res = res - res / o);
    return res;
}

long long xmul(register long long a, register long long b, register long long modulo) {
    register long long res = 0;
    for (register int i = 62; ~i; --i) {
        res = (res << 1) % modulo;
        b & (1LL << i) && (res = (res + a) % modulo);
    }
    return res;
}

long long xpow(register long long a, register long long b, register long long modulo) {
    register long long res = 1;
    while (b) {
        b & 1 && (res = xmul(res, a, modulo));
        a = xmul(a, a, modulo);
        b >>= 1;
    }
    return res;
}

long long x, n, m, p, e, q;

int main() {
    scanf("%lld%lld%lld%lld", &x, &n, &m, &p);
    e = phi(p); q = xpow(n, m, e);
    printf("%lld\n", xpow(x, q + (q == pow(n, m) ? 0 : e), p));
    return 0;
}
