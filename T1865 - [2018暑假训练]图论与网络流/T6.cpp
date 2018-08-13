#include <bits/stdc++.h>
#define MAXN 100010
using namespace std;

namespace MirAc1e {
    #define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? 0 : *S++)
    //#define cmax(a, b) ((a) > (b) && ((a) = (b)))
    //#define dmax(a, b) ((a) > (b) ? (a) : (b))
    //#define cmin(a, b) ((a) < (b) && ((a) = (b)))
    //#define dmin(a, b) ((a) > (b) ? (a) : (b))
    //#define xabs(o) ((o) < 0 ? -(o) : (o))
    #define xswap(a, b) ((a) ^= (b) ^= (a) ^= (b))
    //#define INF 0x3f3f3f3f
    //#define EPS 1e-6

    char B[1 << 15], *S = B, *T = B;

    template<typename P>
    void scan(register P *o) {
    	//register char ch, f; // Signed
    	//while (ch = getc(), (ch < '0' || ch > '9') && ch != '-'); // Signed
        register char ch; // Signed
    	while (ch = getc(), ch < '0' || ch > '9'); // Unsigned
        *o = ch - '0'; // Unsigned
    	//ch == '-' ? *o = f = 0 : (*o = ch - '0', f = 1); // Signed
    	while (ch = getc(), ch >= '0' && ch <= '9' ) *o = *o * 10 + ch - '0';
    	//!f && (*o = -*o); // Signed
    }

    /*
    template<typename P>
    void print(register P o) {
        //o < 0 && (putchar('-'), o = -o); // Signed
        o > 9 && (print(o / 10), 0);
        putchar(o % 10 + '0');
    }
    */
}

struct Edge {
    int to;
    Edge *nxt;
};

struct Graph {
    int graph, val[MAXN], fa[MAXN], dep[MAXN];
    Edge *first[MAXN], e[MAXN], *ptr = e;

    inline void insert(register int &u, register int &v) {
	    *ptr = (Edge) {v, first[u]}; first[u] = ptr++; fa[v] = u;
    }

    void dfs(register int o) {
        for (register Edge *i = first[o]; i; i = i -> nxt) {
            register int son = i -> to;
            dep[son] = dep[o] + 1;
            dfs(son);
        }
    }

	/*
	inline void clr() {
		graph = 0; ptr = e;
		memset(first, 0, sizeof(first)); memset(e, 0, sizeof(0));
	}
	*/
} orz_night;

int n, q, a, b, t, top, sta[MAXN];
bool flag;

int main() {
    MirAc1e::scan(&n); MirAc1e::scan(&q);
    for (register int i = 1; i <= n; ++i)
        MirAc1e::scan(&orz_night.val[i]);
    for (register int i = 1; i < n; ++i) {
        MirAc1e::scan(&a); MirAc1e::scan(&b); orz_night.insert(a, b);
    }
    orz_night.dfs(1);
    //printf("Query counts: %d\n", q);
    while (q--) {
        MirAc1e::scan(&t); MirAc1e::scan(&a); MirAc1e::scan(&b);
        //printf("Query #%d: %d %d %d ", q, t, a, b);
        switch (t) {
            case 0 :
                //printf("Query ");
                top = 0;
                /*
                orz_night.dep[a] < orz_night.dep[b] && xswap(a, b);
                while (orz_night.dep[a] != orz_night.dep[b] && t < 50) {
                    sta[++top] = orz_night.val[a]; a = orz_night.fa[a];
                }
                */
                while (a != b && top < 50) {
                    /*
                    sta[++top] = orz_night.val[a]; a = orz_night.fa[a];
                    sta[++top] = orz_night.val[b]; a = orz_night.fa[b];
                    */
                    if (orz_night.dep[a] < orz_night.dep[b]) {
                        sta[++top] = orz_night.val[b];
                        b = orz_night.fa[b];
                    }
                    else {
                    sta[++top] = orz_night.val[a];
                    a = orz_night.fa[a];
                    }
                }
                (top < 50) && (sta[++top] = orz_night.val[a]);
                if (top >= 50) {
                    puts("Y");
                    break;
                }
                sort(sta + 1, sta + 1 + top);
                flag = 1;
                for (register int i = 1, i_lim = top - 2; i <= i_lim; ++i)
                    if (sta[i] > sta[i + 2] - sta[i + 1]) {
                        puts("Y");
                        flag = 0;
                        break;
                    }
                flag && puts("N");
                break;
            case 1 :
                //printf("Modify\n");
                orz_night.val[a] = b;
                break;
        }
    }
    return 0;
}
