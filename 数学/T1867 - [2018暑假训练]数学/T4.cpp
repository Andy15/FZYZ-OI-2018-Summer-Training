#include <bits/stdc++.h>
#define MAXN 10000007

namespace MirAc1e {
    #define BUF_SIZ 25
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << BUF_SIZ, stdin), S == T) ? 0 : *S++)

    char B[1 << BUF_SIZ], *S = B, *T = B;
    char U[1 << BUF_SIZ], *O = U, K[BUF_SIZ];

    template<typename P>
    void scan(register P &o) {
        register char ch; // Unsigned
    	while (ch = getc(), ch < '0' || ch > '9'); // Unsigned
        o = ch - '0'; // Unsigned
    	while (ch = getc(), ch >= '0' && ch <= '9') o = o * 10 + ch - '0';
    }

    template<typename P>
    void print(register P o) {
        register int T = 0;
        for ( ; o; o /= 10)
            K[++T] = o % 10;
        for ( ; T; *O++ = '0' + K[T--]);
    }
}

using namespace std;
using namespace MirAc1e;

int p_cnt, p[MAXN];
bool com[MAXN];

int xpow(register int x, register int y) {
    register int res = 1;
    while (y) {
        y & 1 && (res = res * x);
        x = x * x;
        y >>= 1;
    }
    return res;
}

int main() {
    com[1] = 1;
    for (register int i = 2; i <= 10000000; ++i) {
        !com[i] && (p[++p_cnt] = i);
        for (register int j = 1; j <= p_cnt && i * p[j] <= 10000000; ++j) {
            com[i * p[j]] = 1;
            if (!(i % p[j]))
                break;
        }
    }
    int T, n;
    for (scan(T); T; --T) {
        scan(n);
        if (!(n & 1)) {
            *O++ = '0'; *O++ = '\n';
            continue;
        }
        register int ans = 1;
        for (register int pos = 1, *prime = p + 1, cnt = 0; n != 1; ++pos, ++prime, cnt = 0) {
            while (!(n % *prime)) {
                ++cnt;
                n /= *prime;
            }
            if (!cnt)
                continue;
            ans *= xpow(*prime, cnt - 1) * (*prime - 2);
            if (!com[n]) {
                ans *= n - 2;
                break;
            }
        }
        print(ans); *O++ = '\n';
    }
    fwrite(U, 1, O - U, stdout);
    return 0;
}
