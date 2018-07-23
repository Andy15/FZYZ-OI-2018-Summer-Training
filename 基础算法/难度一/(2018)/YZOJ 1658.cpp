#include <bits/stdc++.h>
#define MAXS 256
using namespace std;

char s[MAXS], ans;
int n, x, c, sign = 1, tmp;
bool side = 1;

int main() {
    scanf("%s", s); n = strlen(s);
    for (register int i = 0; i < n; ++i)
        switch (s[i]) {
            case '=' : { side = 0; continue; }
            case '-' : { sign = -1; continue; }
            case '+' : { sign = 1; continue; }
            default : {
                tmp = 0;
                while (s[i] >= '0' && s[i] <= '9')
                    tmp = tmp * 10 + s[i++] - '0';
                (!tmp) && (tmp = 1);
                (s[i] >= 'a' && s[i] <= 'z') ? (side ? x += sign * tmp : x -= sign * tmp, ans = s[i]) : (side ? c -= sign * tmp : c += sign * tmp, --i);
                sign = 1;
            }
        }
    printf("%c=%.3lf", ans, (double) c / x);
    return 0;
}
