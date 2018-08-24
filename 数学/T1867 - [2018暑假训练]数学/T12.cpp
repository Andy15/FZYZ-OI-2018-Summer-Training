#include <bits/stdc++.h>
using namespace std;

namespace subtask1 {
    int T;
    long long a, p, x, y;

    long long exgcd(register long long a, register long long b, register long long &x, register long long &y) {
        if (!b) {
            x = 1; y = 0;
            return a;
        }
        register long long d = exgcd(b, a % b, x, y);
        register long long z = x; x = y; y = z - y * (a / b);
        return d;
    }

    void main() {
        for (scanf("%d", &T); T; --T, x = y = 0) {
            scanf("%lld%lld", &a, &p);
            exgcd(a, p, x, y);
            printf("%lld\n", (x % p + p) % p);
        }
    }
}

namespace subtask2 {
    #define LLONG_INF 0x3f3f3f3f3f3f3f3f

    int T;
    long long a, p, m, n = LLONG_INF;

    inline void cmin(register long long &a, register long long b) {
        (a > b) && (a = b);
    }

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

    void main() {
        for (scanf("%d", &T); T; --T, n = LLONG_INF) {
            scanf("%lld%lld", &a, &p); m = phi(p);
            for (register long long i = 1; i * i <= m; ++i)
                if (!(m % i)) {
                    xpow(a, i, p) == 1 && (cmin(n, i), 1);
                    xpow(a, m / i, p) == 1 && (cmin(n, m / i), 1);
                }
            printf("%lld\n", n);
        }
    }

    #undef LLONG_INF
}

namespace subtask3 {
    #define MAXN 10000010

    int T, n, m, p_cnt, p[MAXN], mu[MAXN], mu_pre[MAXN];
    long long ans;
    bool com[MAXN];

    inline int dmin(register int a, register int b) {
        return a < b ? a : b;
    }

    inline void xswap(register int &a, register int &b) {
        a ^= b ^= a ^= b;
    }

    void sieve() {
        mu[1] = com[1] = 1;
        for (register int i = 2; i <= 10000000; ++i) {
            !com[i] && (p[++p_cnt] = i, mu[i] = -1);
            for (register int j = 1; j <= p_cnt && i * p[j] <= 10000000; ++j) {
                com[i * p[j]] = 1;
                if (!(i % p[j])) {
                    mu[i * p[j]] = 0;
                    break;
                }
                mu[i * p[j]] = -mu[i];
            }
        }
        for (register int i = 1; i <= 10000000; ++i)
            mu_pre[i] = mu_pre[i - 1] + mu[i];
    }

    int query(register int a, register int b) {
        register int i = 1, j;
        register long long res = 0;
        while (i <= a) {
            j = dmin(a / (a / i), b / (b / i));
            res += ((long long) mu_pre[j] - mu_pre[i - 1]) * (a / i) * (b / i);
            i = j + 1;
        }
        return res;
    }

    void main() {
        for (scanf("%d", &T); T; --T, ans = 0) {
            scanf("%d%d", &n, &m); (n > m) && (xswap(n, m), 1); sieve();
            register int i = 1, j;
            while (i <= n) {
                j = dmin(n / (n / i), m / (m / i));
                register long long tmp = ((long long) i + j) * (j - i + 1) >> 1;
                ans += tmp * query(n / i, m / i);
                i = j + 1;
            }
            printf("%lld\n", ans);
        }
    }

    #undef MAXN
}

namespace subtask4 {
    int T, n;
    long long ans;

    inline int dmin(register int a, register int b) {
        return a < b ? a : b;
    }

    void main() {
        for (scanf("%d", &T); T; --T, ans = 0) {
            scanf("%d", &n);
            for (register int i = 1, j; i <= n; i = j + 1) {
                j = n / i ? dmin(n / (n / i), n) : n;
                ans += (n / i) * (j - i + 1);
            }
            printf("%lld\n", ans);
        }
    }
}

namespace subtask5 {
    void main() {

    }
}

int Q;

int main() {
	scanf("%d", &Q);
	switch (Q) {
		case 1 : case 2 :
			subtask1::main();
			break;

		case 3 : case 4 : case 5 : case 6 :
			subtask2::main();
			break;

		case 7 : case 8 : case 9 : case 10 :
			subtask3::main();
			break;

		case 11 : case 12 : case 13 : case 14 :
			subtask4::main();
			break;

		case 15 : case 16 : case 17 : case 18 : case 19 : case 20 :
			subtask5::main();
			break;
	}
	return 0;
}
