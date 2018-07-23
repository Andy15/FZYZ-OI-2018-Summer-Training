#include <bits/stdc++.h>
#define MAXS 110
#define MAXA 30010
using namespace std;

int p1, p2, p3, top, i, t1, t3;
char s[MAXS], ans[MAXA];

int main() {
    scanf("%d%d%d%s", &p1, &p2, &p3, s);
    while (s[i]) {
        t1 = s[i]; t3 = s[i + 2];
        if (s[i + 1] == '-') {
            ans[top++] = s[i];
            if (t1 >= t3) { ans[top++] = '-'; i += 2; continue; }
            else if (t1 + 1 == t3) { i += 2; continue; }
            if ((t1 >= 'a' && t1 <= 'z') && (t3 >= 'a' && t3 <= 'z')) {
                for (register int j = p3 == 1 ? t1 + 1 : t3 - 1; p3 == 1 ? j < t3 : j > t1; p3 == 1 ? ++j : --j)
                    for (register int k = 1; k <= p2; ++k)
                        ans[top++] = (p1 == 1) ? (j) : ((p1 == 2) ? (j - 'a' + 'A') : ('*'));
                i += 2; continue;
            }
            else if ((t1 >= '0' && t1 <= '9') && (t3 >= '0' && t3 <= '9')) {
                for (register int j = p3 == 1 ? t1 + 1 : t3 - 1; p3 == 1 ? j < t3 : j > t1; p3 == 1 ? ++j : --j)
                    for (register int k = 1; k <= p2; ++k)
                        ans[top++] = p1 == 3 ? '*' : j;
                i += 2; continue;
            }
            else { ans[top++] = '-'; i += 2; continue; }
        }
        else { ans[top++] = s[i]; ++i; continue; }
    }
    printf("%s", ans);
    return 0;
}
