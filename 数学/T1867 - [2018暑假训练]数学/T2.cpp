#include <bits/stdc++.h>

namespace MirAc1e {
    #define BUF_SIZ 25
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << BUF_SIZ, stdin), S == T) ? 0 : *S++)

    char B[1 << BUF_SIZ], *S = B, *T = B;
    char U[1 << BUF_SIZ], *O = U, K[BUF_SIZ];

    template<typename P>
    void scan(register P &o) {
        register char ch;
    	while (ch = getc(), ch < '0' || ch > '9');
        o = ch - '0';
    	while (ch = getc(), ch >= '0' && ch <= '9') o = o * 10 + ch - '0';
    }

    template<typename P>
    void print(register P o) {
        if (!o) {
           *O++ = '0';
           return;
        }
        register int T = 0;
        for ( ; o; o /= 10)
            K[++T] = o % 10;
        for ( ; T; *O++ = '0' + K[T--]);
        *O++ = '\n';
    }
}

using namespace std;
using namespace MirAc1e;

long long eular(register long long o) {
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

long long xpow(register long long a, register long long b, register long long modulo) {
    register long long res = 1;
    while (b) {
        b & 1 && (res = res * a % modulo);
        a = a * a % modulo;
        b >>= 1;
    }
    return res;
}

long long gcd(register long long a, register long long b) {
    return b ? gcd(b, a % b) : a;
}

long long x, n, m, p, e, a, b;

int main() {
    scan(x); scan(n); scan(m); scan(p);
    e = eular(p); a = xpow(n, m, e); b = xpow(n, m, e + 1);
    if (gcd(x, p) == 1)
        print(xpow(x, xpow(n, m, e), p));
    else
        if (a == b)
            print(xpow(x, b, p));
        else
            print(xpow(x, e, p) * xpow(x, xpow(n, m, e), p) % p);
    fwrite(U, 1, O - U, stdout);
    return 0;
}
