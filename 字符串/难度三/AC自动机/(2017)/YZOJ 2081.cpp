#warning orz_night
#include <bits/stdc++.h>
#define MAXL 20
#define MAXM 200010
#define MOD 100000
using namespace std;

int n, m, ans;
char s[MAXL];

#define MAXNODE 110
#define SIGMA_SIZE 10
#define idx(o) (o - 'A')
struct AhoCorasickAutomata {
    int ch[MAXNODE][SIGMA_SIZE], f[MAXNODE], val[MAXNODE], sz;

    void insert() {
        register int u = 0, n = strlen(s);
        for (register int i = 0; i < n; ++i) {
            register int c = idx(s[i]);
            (!ch[u][c]) && (ch[u][c] = ++sz);
            u = ch[u][c];
        }
        val[u] = 1;
    }

    void getFail() {
        queue<int> q; f[0] = -1; q.push(0);
        while (!q.empty()) {
            register int r = q.front(); q.pop();
            for (register int c = 0; c < SIGMA_SIZE; ++c) {
                int u = ch[r][c];
                u ? (q.push(u), f[u] = r ? ch[f[r]][c] : 0) : (ch[r][c] = r ? ch[f[r]][c] : 0);
            }
            val[r] |= val[f[r]];
        }
    }
} orz_night;

struct Matrix {
    long long a[MAXNODE][MAXNODE];

    Matrix() {
        memset(a, 0, sizeof(a));
    }

    Matrix operator * (register const Matrix &ano) const {
		static Matrix t; t = Matrix();
		for (register int i = 0; i <= orz_night.sz; ++i)
			for (register int k = 0; k <= orz_night.sz; ++k)
				if (a[i][k]) {
                    register const long long *x = ano.a[k];
					for (register int j = 0, tmp = a[i][k]; j <= orz_night.sz; ++j, ++x)
						ano.a[k][j] && (t.a[i][j] = (t.a[i][j] + (long long) tmp * *x) % MOD);
				}
		return t;
	}

	Matrix operator ^ (register const int &k) const {
		static Matrix base, ret; base = Matrix(); ret = Matrix(); base = *this;
		static int x; x = k;
		for (register int i = 0; i <= orz_night.sz; ++i)
            ret.a[i][i] = 1;
		while (x) {
			x & 1 && (ret = ret * base, 1);
			x >>= 1;
			base = base * base;
		}
		return ret;
	}
} probkiller, res;

int main() {
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= n; ++i) {
        scanf("%s", s); orz_night.insert();
    }
    orz_night.getFail();
    for (register int i = 0; i <= orz_night.sz; ++i) {
        if (orz_night.val[i])
            continue;
        for (register int j = 0; j < 4; ++j)
            (!orz_night.val[orz_night.ch[i][j]]) && (++probkiller.a[orz_night.ch[i][j]][i]);
    }
    /*
    for (register int i = 0; i <= orz_night.sz; ++i) {
		for (register int j = 0; j <= orz_night.sz; ++j)
			printf("%lld ", probkiller.a[i][j]);
		putchar('\n');
	}
    */
	res.a[0][0] = 1; res = (probkiller ^ m) * res;
	for (register int i = 0; i <= orz_night.sz; ++i)
		ans = (ans + res.a[i][0]) % MOD;
    /*
    for (register int i = 0; i <= orz_night.sz; ++i) {
        for (register int j = 0; j <= orz_night.sz; ++j)
            printf("%lld ", res.a[i][j]);
        putchar('\n');
    }
    */
	printf("%d", ans);
    return 0;
}
