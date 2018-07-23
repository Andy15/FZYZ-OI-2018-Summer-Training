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
