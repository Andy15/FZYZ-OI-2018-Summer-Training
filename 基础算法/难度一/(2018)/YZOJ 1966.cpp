#include <bits/stdc++.h>
#define MAXN 30
using namespace std;

int n, a, b;

struct P {
    int l = -1, r = -1;
} o[MAXN << 1];

void pop(register int h) {
    register int cur = o[h].r, nxt;
    while (cur != -1) {
        nxt = o[cur].r;
        o[cur].l = cur + n; o[cur].r = -1; o[cur + n].r = cur;
        cur = nxt;
    }
    o[h].r = -1;
}

void push(register int x, register int y) {
    register int cur = y;
    while (o[cur].r != -1)
        cur = o[cur].r;
    o[o[x].l].r = -1; o[x].l = cur; o[cur].r = x;
}

bool check(register int x, register int y) {
    register int cur_a = x, cur_b = y;
    while (cur_a != -1) {
        if (cur_a == y)
            return 1;
        cur_a = o[cur_a].r;
    }
    while (cur_b != -1) {
        if (cur_b == x)
            return 1;
        cur_b = o[cur_b].r;
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (register int i = 0; i < n; ++i) {
        o[i].l = i + n; o[i + n].r = i;
    }
    string tmp1, tmp2;
    while (1) {
        cin >> tmp1 >> a >> tmp2 >> b;
        if (tmp1 == "move") {
            if (check(a, b))
                continue;
            if (tmp2 == "onto") {
                pop(a); pop(b); push(a, b);
            }
            else {
                pop(a); push(a, b);
            }
        }
        else if (tmp1 == "pile") {
            if (check(a, b))
                continue;
            if (tmp2 == "onto") {
                pop(b); push(a, b);
            }
            else
                push(a, b);
        }
        else {
            for (register int i = n, i_lim = (n << 1) - 1, cur = o[n].r; i <= i_lim; ++i, cur = o[i].r) {
                printf("%d:", i - n);
                while (cur != -1) {
                    printf(" %d", cur);
                    cur = o[cur].r;
                }
                putchar('\n');
            }
            break;
        }
    }
    return 0;
}
