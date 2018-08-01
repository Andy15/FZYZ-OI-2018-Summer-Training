#include <bits/stdc++.h>

using namespace std;

#define RG register
#define ll long long
#define IL inline
#define For(i, f, t) for (RG int i = f; i <= t; i++)

int main()
{
	For (t, 1, 10000)
	{
		printf("Case %d\n", t);
		system("maker > dev.in");
		puts("Finish0");
		double cl = clock();
		system("tmp < dev.in > dev.out");
		printf("%lf\n", (clock() - cl) / CLOCKS_PER_SEC);
		puts("Finish1");
		system("baoli < dev.in > dev.ans");
		puts("Finish2");
		if (system("fc dev.out dev.ans /W")) break;
	}
}
