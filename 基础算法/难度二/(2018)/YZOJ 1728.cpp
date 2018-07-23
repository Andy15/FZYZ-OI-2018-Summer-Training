#include <bits/stdc++.h>
using namespace std;

#define BASE 10
#define L 20010
char s[10 * L];
struct BigInt {
    int num[L], len;

    BigInt (register int x = 0) { memset(num, 0, sizeof(num)); len = 1; num[0] = x; }

    bool substract(BigInt b, register int pos) {
        if (len < b.len - pos)
            return 0;
        if (len == b.len - pos)
            for (register int i = len - 1; i >= 0; --i) {
                if (num[i] < b.num[i + pos])
                    return 0;
                if (num[i] > b.num[i + pos])
                    break;
            }
        for (register int i = 0; i < len; ++i) {
            num[i] -= b.num[i + pos];
            (num[i] < 0) && (num[i] += BASE, --num[i + 1]);
        }
        while (!num[len - 1])
            --len;
        return 1;
    }

    BigInt operator / (BigInt b) {
        BigInt c;
        if (len < b.len)
            return c;
        register int k = len - b.len; c.len = k + 1;
        for (register int i = len - 1; i >= 0; --i)
            b.num[i] = i >= k ? b.num[i - k] : 0;
        b.len = len;
        for (register int i = 0; i <= k; ++i)
            while (this -> substract(b, i))
                ++c.num[k - i];
        for (register int i = 0; i < c.len; ++i) {
            c.num[i + 1] += c.num[i] / BASE; c.num[i] %= BASE;
        }
        while (!c.num[c.len - 1] && c.len > 0)
            --c.len;
        return c;
    }

    bool scan() {
        register int n = -1;
        register char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == EOF)
                return 0;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9') {
            s[++n] = ch - '0'; ch = getchar();
        }
        len = 0;
        for (register int i = n; i >= 0; --i)
            num[len++] += s[i];
        return 1;
    }

    void print() {
        for (register int i = len - 1; i >= 0; --i)
            printf("%d", num[i]);
    }
} m, n;

int main() {
    m.scan(); n.scan();
    (m / n).print();
    return 0;
}
