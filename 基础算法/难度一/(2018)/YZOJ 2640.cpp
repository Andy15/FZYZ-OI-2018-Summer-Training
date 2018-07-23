#include <bits/stdc++.h>
#define MAXN 10010
#define MAXL 110
using namespace std;

int n, len = 1, tmp;
char s[MAXN][MAXL], ans[MAXL];
string num[MAXN];

int main() {
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i)
        scanf("%s", s[i] + 1);
    while (s[1][len] >= 'a' && s[1][len] <= 'z')
        ++len;
    --len;
    for (register int i = 1; i <= len; ++i)
        ans[i] = s[1][i];
    ans[len + 1] = '\0';
    for (register int i = 1; i <= n; ++i) {
        register int num_len = strlen(s[i] + 1) - len - 3;
        for (register int j = 1, j_lim = 100 - num_len; j <= j_lim; ++j)
            num[i] += '0';
        for (register int j = len + 1, j_lim = strlen(s[i] + 1) - 3; j <= j_lim; ++j)
            num[i] += s[i][j];
    }
    sort(num + 1, num + 1 + n);
    for (register int i = 1; i <= n; ++i) {
        printf("%s", ans + 1);
        register int j = 0;
        for ( ; j < 100; ++j)
            if (num[i][j] != '0')
                break;
        j == 100 && putchar('0');
        for ( ; j < 100; ++j)
            putchar(num[i][j]);
        puts(".in");
    }
    return 0;
}
