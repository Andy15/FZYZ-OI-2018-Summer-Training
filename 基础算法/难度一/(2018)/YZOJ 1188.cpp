#include <bits/stdc++.h>
#define MAXN 1010
using namespace std;

char oper;
int n, b;

#define BASE 10000
int p;
char s[10 * MAXN];
struct BigInt {
    int num[MAXN], len;

    BigInt(register int x = 0) {
        memset(num, 0, sizeof(num));
        len = 1;
        num[0] = x;
    }

    BigInt operator * (register int b) {
        BigInt c;
        for (register int i = 0; i < len; ++i)
            c.num[i] = num[i] * b;
        for (register int i = 0; i < len; ++i) {
            c.num[i + 1] += c.num[i] / BASE;
            c.num[i] %= BASE;
        }
        c.len = len;
        while (c.num[c.len])
            ++c.len;
        return c;
    }

    BigInt operator / (register int b) {
        BigInt c;
        register int tmp = 0;
        for (register int i = len - 1; i >= 0; --i) {
            tmp = tmp * BASE + num[i];
            c.num[i] = tmp / b;
            tmp %= b;
        }
        for (c.len = len; !c.num[c.len-1] && c.len > 1; --c.len);
        return c;
    }

    bool scan() {
        register int n = -1;
        register char ch = getchar();
        while (ch < '0' || ch > '9')
            if (ch == EOF)
                return 0;
            else
                ch = getchar();
        while (ch >= '0' && ch <= '9') {
            s[++n] = ch - '0';
            ch = getchar();
        }
        len = 0;
        for (register int i = n; i >= 0; i -= 4) {
            num[len] += s[i];
            i >= 1 && (num[len] += s[i - 1] * 10);
            i >= 2 && (num[len] += s[i - 2] * 100);
            i >= 3 && (num[len] += s[i - 3] * 1000);
            ++len;
        }
        return 1;
    }

    void print() {
        printf("%d", num[len - 1]);
        for (register int i = len - 2; i >= 0; --i)
            printf("%04d", num[i]);
    }
} a;

int main() {
    scanf("%s%d", &oper, &n); a.scan(); b = getchar() - '0';
    (oper == 'M' ? a * b : a / b).print();
    return 0;
}
