#include <bits/stdc++.h>
#define MAXN 555555
using namespace std;

int n, m, val, ans;
char cmd;
priority_queue<int, vector<int>, greater<int> > heap;

int main() {
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= n; ++i) {
        scanf("%s%d", &cmd, &val);
        switch (cmd) {
            case 'd' :
                heap.push(val);
                break;
            case 'p' :
                while ((int) heap.size() >= val)
                    heap.pop();
                break;
        }
    }
    if ((int) heap.size() < m) {
        puts("Rabbit can not beat bear.");
        return 0;
    }
    while (!heap.empty()) {
        ans += heap.top(); heap.pop();
    }
    printf("%d\n", ans);
    return 0;
}
