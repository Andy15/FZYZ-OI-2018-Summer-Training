#include <bits/stdc++.h>
#define MAXI 10000010

namespace MirAc1e {
    #define BUF_SIZ 25 // 20 is NOT enough for this problem.
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << BUF_SIZ, stdin), S == T) ? 0 : *S++)
    //#define cmax(a, b) ((a) < (b) && ((a) = (b)))
    #define dmax(a, b) ((a) > (b) ? (a) : (b))
    //#define cmin(a, b) ((a) > (b) && ((a) = (b)))
    //#define dmin(a, b) ((a) < (b) ? (a) : (b))
    //#define xabs(o) ((o) < 0 ? -(o) : (o))
    //#define xswap(a, b) ((a) ^= (b) ^= (a) ^= (b))
    //#define INF 0x3f3f3f3f
    //#define EPS 1e-6

    char B[1 << BUF_SIZ], *S = B, *T = B;
    char U[1 << BUF_SIZ], *O = U, K[BUF_SIZ];

    template<typename P>
    void scan(register P &o) {
    	//register char ch, f; // Signed
    	//while (ch = getc(), (ch < '0' || ch > '9') && ch != '-'); // Signed
        //ch == '-' ? o = f = 0 : (o = ch - '0', f = 1); // Signed
        register char ch; // Unsigned
    	while (ch = getc(), ch < '0' || ch > '9'); // Unsigned
        o = ch - '0'; // Unsigned
    	while (ch = getc(), ch >= '0' && ch <= '9') o = o * 10 + ch - '0';
    	//!f && (o = -o); // Signed
    }

    // Call 'fwrite(U, 1, O - U, stdout);' at the end of main().
    template<typename P>
    void print(register P o) {
        // Commit when 'o != 0' always holds.
        //if (!o) {
        //   *O++ = '0';
        //   return;
        //}
        //(o < 0) && (o = -o, *O++ = '-'); // Signed
        register int T = 0;
        for ( ; o; o /= 10)
            K[++T] = o % 10;
        for ( ; T; *O++ = '0' + K[T--]);
    }
}

using namespace std;
using namespace MirAc1e;

bool a[MAXI], b[MAXI];

void interval_sieve(register int left, register int right) {
    register int interval_length = right - left;
    for (register int i = 0; i * i < right; ++i)
        a[i] = 1;
    for (register int i = 0; i < interval_length; ++i)
        b[i] = 1;
    for (register int i = 2, prime_max = (left + i - 1) / i; i * i < right; ++i, prime_max = (left + i - 1) / i) {
        if (!a[i])
            continue;
        for (register int j = i << 1; j * j < right; j += i)
            a[j] = 0;
        for (register int j = dmax(2, prime_max) * i; j < right; j += i)
            b[j - left] = 0;
    }
    for (register int i = 0; i < interval_length; ++i)
        b[i] && (print(left + i), *O++ = '\n');
    *O++ = '\n';
}

int main() {
    int T;
    for (scan(T); T; --T) {
        memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));
        int m, n; scan(m); scan(n); interval_sieve(dmax(m, 2), n + 1);
    }
    fwrite(U, 1, O - U, stdout);
    return 0;
}
