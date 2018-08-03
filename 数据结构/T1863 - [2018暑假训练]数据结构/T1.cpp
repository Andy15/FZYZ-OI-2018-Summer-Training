#include <bits/stdc++.h>
#define MAXP 1010
using namespace std;

int a, b, n, arr[MAXP][MAXP], head, tail, que[MAXP], res[4][MAXP][MAXP], ans = 0x3f3f3f3f;

inline void cmin(register int &a, register int b) {
    (a > b) && (a = b);
}

int main() {
    scanf("%d%d%d", &a, &b, &n);
    for (register int i = 1; i <= a; ++i)
        for (register int j = 1; j <= b; ++j)
            scanf("%d", &arr[i][j]);
    for (register int i = 1; i <= a; ++i) {
        head = tail = 0;
        for (register int j = 1; j <= b; ++j) {
            (head != tail && j - que[head + 1] == n) && (++head);
            while (head != tail && arr[i][j] <= arr[i][que[tail]])
                --tail;
            que[++tail] = j;
            res[0][i][j] = arr[i][que[head + 1]];
        }
        head = tail = 0;
        for (register int j = 1; j <= b; ++j) {
            (head != tail && j - que[head + 1] == n) && (++head);
            while (head != tail && arr[i][j] >= arr[i][que[tail]])
                --tail;
            que[++tail] = j;
            res[1][i][j] = arr[i][que[head + 1]];
        }
    }
    for (register int j = 1; j <= b; ++j) {
        head = tail = 0;
        for (register int i = 1; i <= a; ++i) {
            (head != tail && i - que[head + 1] == n) && (++head);
            while (head != tail && res[0][i][j] <= res[0][que[tail]][j])
                --tail;
            que[++tail] = i;
            res[2][i][j] = res[0][que[head + 1]][j];
        }
        head = tail = 0;
        for (register int i = 1; i <= a; ++i) {
            (head != tail && i - que[head + 1] == n) && (++head);
            while (head != tail && res[1][i][j] >= res[1][que[tail]][j])
                --tail;
            que[++tail] = i;
            res[3][i][j] = res[1][que[head + 1]][j];
        }
    }
    for (register int i = n; i <= a; ++i)
        for (register int j = n; j <= b; ++j)
            cmin(ans, res[3][i][j] - res[2][i][j]);
    printf("%d\n", ans);
    return 0;
}
