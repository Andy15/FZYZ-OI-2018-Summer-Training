// 修改自提交记录：240018
// 原记录作者：MirAc1e (UID: 1942)
#include <bits/stdc++.h>
#define MAXN 100010
using namespace std;

int n;
char cmd;
string s;
map<string, bool> vis;

int main() {
    for (scanf("%d", &n); n; --n) {
        scanf("%s", &cmd); cin >> s;
        cmd == 'I' ? vis[s] = 1 : puts(vis[s] ? "YES" : "NO");
    }
    return 0;
}
