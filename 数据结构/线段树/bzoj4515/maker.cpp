#include <bits/stdc++.h>

using namespace std;

#define RG register
#define ll long long
#define IL inline
#define For(i, f, t) for (RG int i = f; i <= t; i++)

int N = 100000, M = 100000, S = 1e9;

int main()
{
	srand(time(0) + clock());
	printf("%d %d\n", N, M);
	For (i, 2, N) printf("%d %d %d\n", rand() % (i - 1) + 1, i, rand() % S + 1);
	For (i, 1, M)
	{
		int opt = rand() % 2 + 1; printf("%d ", opt);
		if (opt == 1)
		{
			printf("%d %d %d %d\n", rand() % N + 1, rand() % N + 1, rand() % (2 * S + 1) - S, rand() % (2 * S + 1) - S);
		}
		else
		{
			printf("%d %d\n", rand() % N + 1, rand() % N + 1);
		}
	}
	return 0;
}

