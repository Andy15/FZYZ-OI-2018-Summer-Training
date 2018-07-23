#include <bits/stdc++.h>
#define MAXN 10
#define MAXM 10
#define max(a, b) (a > b ? a : b)
using namespace std;

int a[MAXN][MAXM], b[MAXN][MAXM], ans;

void move(register int f, register int k) {
	if (f) {
		register int tmp = a[k][7];
		for (register int i = 8; i > 1; --i)
			a[k][i] = a[k][i - 1];
		a[k][1] = tmp;
	}
	else {
		register int tmp = a[k][1];
		for (register int i = 1; i < 7; ++i)
			a[k][i] = a[k][i + 1];
		a[k][7] = tmp;
	}
	switch (k) {
		case 1 : {
			a[3][3] = a[1][3];
			a[4][3] = a[1][5];
			break;
		}
		case 2 : {
			a[3][5] = a[2][3];
			a[4][5] = a[2][5];
			break;
		}
		case 3 : {
			a[1][3] = a[3][3];
			a[2][3] = a[3][5];
			break;
		}
		case 4 : {
			a[1][5] = a[4][3];
			a[2][5] = a[4][5];
			break;
		}
	}
}

int func() {
	register int num[5]; num[1] = num[2] = num[3] = 0; ++num[a[3][4]]; ++num[a[4][4]];
	for (register int j = 3; j < 6; ++j) {
		++num[a[1][j]]; ++num[a[2][j]];
	}
	return 8 - max(max(num[1], num[2]), num[3]);
}

bool ida_star(register int dep, register int last, register int dir) {
	register int tmp = func();
	if (!tmp)
		return 1;
	if (dep + tmp > ans)
		return 0;
	for (register int i = 1; i < 5; ++i) {
		if (last == i && (!dir))
			continue;
		move(1, i);
		if (ida_star(dep + 1, i, 1))
			return 1;
		move(0, i);
	}
	for (register int i = 1; i < 5; ++i) {
		if (last == i && dir)
			continue;
		move(0, i);
		if (ida_star(dep + 1, i, 0))
			return 1;
		move(1, i);
	}
	return 0;
}

int main() {
	while (1) {
		scanf("%d", &a[1][1]);
		if (!a[1][1]) break;
		scanf("%d%d%d", &a[2][1], &a[1][2], &a[2][2]);
		for (register int i = 1; i < 8; ++i)
			scanf("%d", &a[3][i]);
		a[1][3] = a[3][3]; a[2][3] = a[3][5];
		scanf("%d%d", &a[1][4], &a[2][4]);
		for (register int i = 1; i < 8; ++i)
			scanf("%d", &a[4][i]);
		a[1][5] = a[4][3]; a[2][5] = a[4][5];
		scanf("%d%d%d%d", &a[1][6], &a[2][6], &a[1][7], &a[2][7]);
		memcpy(b, a, sizeof(b));
		for (ans = 1; ans <= 12; ++ans)
			if (ida_star(0, -1, -1))
				break;
		printf("%d\n", ans);
	}
	return 0;
}
