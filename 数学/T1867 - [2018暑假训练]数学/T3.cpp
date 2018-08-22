#include <bits/stdc++.h>

namespace MirAc1e {
    #define BUF_SIZ 25
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << BUF_SIZ, stdin), S == T) ? 0 : *S++)
    #define cmax(a, b) ((a) < (b) && ((a) = (b)))
    #define dmax(a, b) ((a) > (b) ? (a) : (b))
    #define cmin(a, b) ((a) > (b) && ((a) = (b)))
    #define dmin(a, b) ((a) < (b) ? (a) : (b))
    #define xabs(o) ((o) < 0 ? -(o) : (o))
    #define xswap(a, b) ((a) ^= (b) ^= (a) ^= (b))
    #define INF 0x3f3f3f3f
    #define EPS 1e-6

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

long long n, m;

struct Matrix {
    long long a[2][2];

    Matrix() {
        memset(a, 0, sizeof(a));
    }

    Matrix operator * (register const Matrix &ano) const {
        static Matrix t; t = Matrix();
		for (register int i = 0; i <= 1; ++i)
			for (register int k = 0; k <= 1; ++k)
				if (a[i][k]) {
                    register const long long *ptr = ano.a[k], tmp = a[i][k];
					for (register int j = 0; j <= 1; ++j)
						ano.a[k][j] && (t.a[i][j] = (t.a[i][j] + tmp * ptr[j]) % m);
				}
		return t;
	}

	Matrix operator ^ (register const long long &k) const {
		static Matrix base, ret; base = Matrix(); ret = Matrix(); base = *this;
		static long long x; x = k;
		for (register int i = 0; i <= 1; ++i)
            ret.a[i][i] = 1;
		while (x) {
			x & 1 && (ret = ret * base, 1);
			x >>= 1;
			base = base * base;
		}
		return ret;
	}
} origin, probkiller;

int main() {
    scan(probkiller.a[0][0]); scan(probkiller.a[0][1]); probkiller.a[1][0] = 1;
    scan(origin.a[1][0]); scan(origin.a[0][0]);
    scan(n); scan(m);
    print(((probkiller ^ (n - 2)) * origin).a[0][0]);
    fwrite(U, 1, O - U, stdout);
    return 0;
}
