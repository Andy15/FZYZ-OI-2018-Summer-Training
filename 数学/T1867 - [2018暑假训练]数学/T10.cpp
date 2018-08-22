#include <bits/stdc++.h>
#define MAXN 100010
using namespace std;

int n, cnt, m;
double a, b, r, x, y, theta, res;

struct Point {
    double x, y;

    Point operator - (const Point &ano) const {
        return (Point) {x - ano.x, y - ano.y};
    }

    double operator * (const Point &ano) const {
        return x * ano.y - y * ano.x;
    }

    bool operator < (const Point &ano) const {
        return x == ano.x ? y < ano.y : x < ano.x;
    }
} pt[MAXN << 2], ans[MAXN << 2];

int main() {
    scanf("%d%lf%lf%lf", &n, &a, &b, &r); a /= 2; b /= 2; a -= r; b -= r;
    for (register int i = 0; i < n; ++i) {
        scanf("%lf%lf%lf", &x, &y, &theta);
        register double x1, x2, y1, y2, sint = sin(theta), cost = cos(theta);
        x1 = b * cost, x2 = a * sint, y1 = b * sint, y2 = a * cost;
        pt[cnt++] = (Point) {x + x1 - x2, y + y1 + y2};
        pt[cnt++] = (Point) {x + x1 + x2, y + y1 - y2};
        pt[cnt++] = (Point) {x - x1 - x2, y - y1 + y2};
        pt[cnt++] = (Point) {x - x1 + x2, y - y1 - y2};
    }
    sort(pt, pt + cnt);
    for (register int i = 0; i < cnt; ++i) {
        while (m > 1 && (ans[m - 1] - ans[m - 2]) * (pt[i] - ans[m - 2]) <= 0) --m;
        ans[m++] = pt[i];
    }
    register int k = m;
    for (register int i = cnt - 2; i >= 0; --i) {
        while (m > k && (ans[m - 1] - ans[m - 2]) * (pt[i] - ans[m - 2]) <= 0) --m;
        ans[m++] = pt[i];
    }
    cnt > 1 && --m;
    for (register int i = 0; i < m; ++i)
        res += sqrt((ans[i].x - ans[i + 1].x) * (ans[i].x - ans[i + 1].x) + (ans[i].y - ans[i + 1].y) * (ans[i].y - ans[i + 1].y));
    res += acos(-1) * r * 2;
    printf("%.2f", res);
    return 0;
}
