#include <bits/stdc++.h>
#define MAXN 210
#define MAXD 1010
using namespace std;

int n, d;
long long p, mat[MAXN][MAXN], c[MAXD][MAXN];

long long exgcd(register long long a, register long long b, register long long &x, register long long &y) {
    if (!b) {
        x = 1; y = 0;
        return a;
    }
    register long long z = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return z;
}

long long query(register long long o) {
    long long x, y;
    exgcd(o, p, x, y);
    return (x % p + p) % p;
}

void orz_night() {
    for (register int i = 1; i <= n; ++i) {
        register int del;
        register long long tmp;
        for (del = i; del <= n; ++del)
            if (mat[del][i])
                break;
        for (register int j = 1, j_lim = n << 1; j <= j_lim; ++j)
            swap(mat[i][j], mat[del][j]);
        tmp = query(mat[i][i]);
        for (register int j = 1, j_lim = n << 1; j <= j_lim; ++j)
            mat[i][j] = mat[i][j] * tmp % p;
        for (register int j = 1; j <= n; ++j) {
            if (i == j)
                continue;
            register long long tmp_2 = mat[j][i] * query(mat[i][i]) % p;
            for (register int k = 1, k_lim = n << 1; k <= k_lim; ++k)
                mat[j][k] = (mat[j][k] - mat[i][k] * tmp_2 % p + p) % p;
        }
    }
}

int main() {
    scanf("%d%d%lld", &n, &d, &p);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= n; ++j)
            scanf("%lld", &mat[i][j]);
    for (register int i = 1; i <= d; ++i)
        for (register int j = 1; j <= n; ++j)
            scanf("%lld", &c[i][j]);
    for (register int i = 1; i <= n; ++i)
        mat[i][i + n] = 1;
    orz_night();
    for (register int i = 1; i <= d; ++i) {
        for (register int j = 1; j <= n; ++j) {
		    register long long ans = 0;
		    for (register int k = n + 1, k_lim = n << 1; k <= k_lim; ++k)
				ans = (ans + c[i][k - n] * mat[j][k] % p) % p;
			printf("%lld ", ans % p);
		}
		putchar('\n');
    }
    return 0;
}
