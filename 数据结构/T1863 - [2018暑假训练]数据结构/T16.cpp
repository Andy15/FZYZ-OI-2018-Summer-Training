#include <bits/stdc++.h>
#define MAXN 400010
#define MAXS 4000010
#define min(a, b) (a < b ? a : b)
using namespace std;

int n, siz = 1, y;
int x[MAXN], lson[MAXN], rson[MAXN];
long long ans, lans, rans;

struct Segment_Tree {
    int siz, root[MAXN], lson[MAXS], rson[MAXS], a[MAXS];

    void build(register int &o, register int l, register int r) {
        (!o) && (o = ++siz);
        if (l == r) {
            a[o] = 1;
            return;
        }
        register int mid = (l + r) >> 1;
        (y <= mid) ? (build(lson[o], l, mid), 1) : (build(rson[o], mid + 1, r), 1);
        a[o] = a[lson[o]] + a[rson[o]];
    }

    int merge(register int l, register int r) {
        if (!l)
            return r;
        if (!r)
            return l;
        lans += (long long) a[rson[l]] * a[lson[r]];
        rans += (long long) a[lson[l]] * a[rson[r]];
        lson[l] = merge(lson[l], lson[r]);
        rson[l] = merge(rson[l], rson[r]);
        a[l] = a[lson[l]] + a[rson[l]];
        return l;
    }
} orz_night;

void make(register int id) {
    scanf("%d", &x[id]);
    if (x[id])
        return;
    make(lson[id] = ++siz);
    make(rson[id] = ++siz);
}

void solve(register int id) {
    if (!id)
        return;
    solve(lson[id]);
    solve(rson[id]);
    if (x[id])
        return;
    lans = rans = 0;
    orz_night.root[id] = orz_night.merge(orz_night.root[lson[id]], orz_night.root[rson[id]]);
    ans += min(lans, rans);
}

int main() {
    scanf("%d", &n); make(1);
    for (register int i = 1; i <= siz; ++i)
        (y = x[i]) && (orz_night.build(orz_night.root[i], 1, n), 1);
    solve(1);
    printf("%lld\n", ans);
    return 0;
}
