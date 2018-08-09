#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) (x & -x)

long long n, m, a, o[1000010], d1[1000010], d2[1000010], req, reqa, reqb, reqv;

inline void modify(register long long *array, register long long pos, register long long delta) {
    for (register long long i = pos; i <= n; i += lowbit(i)) array[i] += delta;
}

inline long long query(register long long *array, register long long pos) {
    register long long sum = 0;
    for (register long long i = pos; i > 0; i -= lowbit(i)) sum += array[i];
    return sum;
}

int main() {
    scanf("%lld %lld", &n, &m);
    for (register long long i = 1; i <= n; ++i) {
        scanf("%lld", &a);
        o[i] = o[i - 1] + a;
    }
    for ( ; m; --m) {
        scanf("%lld %lld %lld", &req, &reqa, &reqb);
        if (!req) {
            register long long suma = o[reqa - 1] + reqa * query(d1, reqa - 1) - query(d2, reqa - 1);
            register long long sumb = o[reqb] + (reqb + 1) * query(d1, reqb) - query(d2, reqb);
            printf("%lld\n", sumb - suma);
        }
        if (req) {
            scanf("%lld", &reqv);
            modify(d1, reqa, reqv);
            modify(d1, reqb + 1, -reqv);
            modify(d2, reqa, reqv * reqa);
            modify(d2, reqb + 1, -reqv * (reqb + 1));
        }
    }
    return 0;
}
