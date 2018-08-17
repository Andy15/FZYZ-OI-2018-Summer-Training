#include <bits/stdc++.h>
#define MAXN 110

namespace MirAc1e {
    #define BUF_SIZ 20
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << BUF_SIZ, stdin), S == T) ? 0 : *S++)
    //#define cmax(a, b) ((a) < (b) && ((a) = (b)))
    //#define dmax(a, b) ((a) > (b) ? (a) : (b))
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
    	register char ch, f; // Signed
    	while (ch = getc(), (ch < '0' || ch > '9') && ch != '-'); // Signed
        //register char ch; // Unsigned
    	//while (ch = getc(), ch < '0' || ch > '9'); // Unsigned
        //o = ch - '0'; // Unsigned
    	ch == '-' ? o = f = 0 : (o = ch - '0', f = 1); // Signed
    	while (ch = getc(), ch >= '0' && ch <= '9') o = o * 10 + ch - '0';
    	!f && (o = -o); // Signed
    }

    // Call 'fwrite(U, 1, O - U, stdout);' at the end of main().
    template<typename P>
    void print(register P o) {
        // Commit when 'o != 0' always holds.
        if (!o) {
           *O++ = '0';
           return;
        }
        //(o < 0) && (o = -o, *O++ = '-'); // Signed
        register int T = 0;
        for ( ; o; o /= 10)
            K[++T] = o % 10;
        for ( ; T; *O++ = '0' + K[T--]);
    }
}

using namespace std;
using namespace MirAc1e;

int m, n, ans;

struct Graph {
    int partner[MAXN];
    bool vis[MAXN], flag[MAXN];

    struct Edge {
        int to;
        Edge *nxt;
    } *first[MAXN], e[MAXN * MAXN], *ptr = e;

    inline void insert(register int &u, register int &v) {
        *ptr = (Edge) {v, first[u]}; first[u] = ptr++;
    }

    bool hungary(register int o) {
        register int son;
        for (register Edge *i = first[o]; i; i = i -> nxt) {
            if (vis[son = i -> to])
                continue;
            vis[son] = 1;
            if (!partner[son] || hungary(partner[son])) {
                partner[partner[o] = son] = o;
                return 1;
            }
        }
        return 0;
    }
} g;

int main() {
    scan(m); scan(n);
    while (1) {
        int i, j; scan(i); scan(j);
        if (!~i && !~j)
            break;
        g.insert(i, j);
    }
    for (register int i = 1; i <= m; ++i) {
        memset(g.vis, 0, sizeof(g.vis));
        g.hungary(i) && (++ans, g.flag[i] = 1);
    }
	if (!ans) {
		puts("No Solution!");
		return 0;
	}
    print(ans); *O++ = '\n';
    for (register int i = 1; i <= m; ++i)
        g.flag[i] && (print(i), *O++ = ' ', print(g.partner[i]), *O++ = '\n');
    fwrite(U, 1, O - U, stdout);
    return 0;
}
