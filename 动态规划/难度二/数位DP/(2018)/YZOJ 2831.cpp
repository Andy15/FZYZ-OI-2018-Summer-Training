#include <bits/stdc++.h>
using namespace std;

int a, b, dp[2][2][2];

int solve(register int n) {
    register int i, x;
    typeof(dp[0][0]) *f = dp[0]; typeof(dp[1][0]) *g = dp[1];
	f[0][0] = f[0][1] = f[1][1] = 0; f[1][0] = 1;
	for (i = 1e9; n < i; i /= 10);
    for ( ; i; i /= 10) {
        swap(f, g); f[0][0] = f[0][1] = f[1][0] = f[1][1] = 0; x = n / i % 10;
		register int j;
        for (j = 0; j < x; ++j) {
            switch (j) {
                case 3 :
                    f[0][1] += g[0][0] + g[0][1] + g[1][0] + g[1][1];
                    break;
                case 7 :
                    f[0][0] += g[0][0] + g[1][0];
                    break;
                default :
                    (j != 4) && (f[0][0] += g[0][0] + g[0][1] + g[1][0] + g[1][1]);
                    break;
            }
		}
		switch (j) {
		    case 3 :
		        f[0][1] += g[0][0] + g[0][1];
		        f[1][1] += g[1][0] + g[1][1];
                break;
            case 7 :
                f[0][0] += g[0][0];
                f[1][0] += g[1][0];
                break;
            default :
                (j != 4) && (f[0][0] += g[0][0] + g[0][1], f[1][0] += g[1][0] + g[1][1]);
                break;
        }
		while (++j < 10) {
		    switch (j) {
		        case 3 :
		            f[0][1] += g[0][0] + g[0][1];
                    break;
                case 7 :
                    f[0][0] += g[0][0];
                    break;
                default :
                    (j != 4) && (f[0][0] += g[0][0] + g[0][1]);
                    break;
            }
		}
    }
    return f[0][0] + f[0][1] + f[1][0] + f[1][1];
}

int main() {
    scanf("%d%d", &a, &b);
    printf("%d", solve(b) - solve(a - 1));
    return 0;
}
