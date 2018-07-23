#include <bits/stdc++.h>
#define MAXS 110
using namespace std;

int n;
char s[MAXS];

#define MAXNODE 1000010
#define SIGMA_SIZE 10
#define idx(o) (o - '0')
struct Trie {
    int ch[MAXNODE][SIGMA_SIZE], val[MAXNODE], sz;

    int check() {
        register int u = 0, n = strlen(s);
        for (register int i = 0; i < n; ++i) {
            register int c = idx(s[i]);
            if (!ch[u][c])
                return -1;
            u = ch[u][c];
        }
        return val[u] ? val[u] : 0;
    }

    void insert(register int v) {
        register int u = 0, n = strlen(s);
        for (register int i = 0; i < n; ++i) {
            register int c = idx(s[i]);
            (!ch[u][c]) && (ch[u][c] = ++sz);
            u = ch[u][c];
        }
        val[u] = v;
    }
} orz_night;

int main() {
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i) {
        scanf("%s", s);
        printf("%d\n", orz_night.check());
        orz_night.insert(i);
    }
    return 0;
}
