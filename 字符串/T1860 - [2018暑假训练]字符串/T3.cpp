#include <bits/stdc++.h>
#define MAXS 400010
using namespace std;

char s[MAXS];
int n, f[MAXS], ans_cnt, ans[MAXS];

int main() {
    while (scanf("%s", s) != EOF) {
        n = strlen(s);
        register int i = 0, j = f[0] = -1;
        while (i < n)
            (s[i] == s[j] || j == -1) ? (f[++i] = ++j) : (j = f[j]);
        register int tmp = ans[0] = n;
        while (f[tmp]) {
    		ans[++ans_cnt] = f[tmp];
    		tmp = f[tmp];
    	}
        if (!ans_cnt) {
            printf("%d\n", n);
            continue;
        }
        printf("%d", ans[ans_cnt]);
    	while (--ans_cnt)
    		printf(" %d", ans[ans_cnt]);
    	printf(" %d\n", ans[0]);
    }
    return 0;
}
