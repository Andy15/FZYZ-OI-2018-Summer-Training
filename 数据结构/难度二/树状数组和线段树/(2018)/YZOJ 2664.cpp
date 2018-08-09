#include <stdio.h>

int n, m, k, op, x;
unsigned long long y, a[300010];
struct P {
	unsigned long long a, b;

	inline P operator + (const register P &ano) const {
		return (P) {a | ano.a, (ano.a & ano.b) | ((~ano.a) & b)};
	}

	inline P operator - (const register P &ano) const {
		return (P) {a | ano.a, (ano.a & ano.b) | ((~ano.a) & (~b))};
	}
} ano, T[1048576];

void build(register int o, register int l, register int r) {
	if (l == r) {
		T[o] = (P) {~a[l], ~a[l]};
		return;
	}
	register int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	if ((r - mid) & 1)
		T[o] = T[o << 1] - T[o << 1 | 1];
	else
		T[o] = T[o << 1] + T[o << 1 | 1];
}

void modify(register int o, register int l, register int r, register int i, register unsigned long long x) {
	if (l == r) {
		T[o] = (P) {~x, ~x};
		return;
	}
	register int mid = l + r >> 1;
	if (i <= mid)
		modify(o << 1, l, mid, i, x);
	else
		modify(o << 1 | 1, mid + 1, r, i, x);
	if ((r - mid) & 1)
		T[o] = T[o << 1] - T[o << 1 | 1];
	else
		T[o] = T[o << 1] + T[o << 1 | 1];
}

P query(int o,int l,int r,int x,int y){
	if (l == x && r == y)
		return T[o];
	register int mid = l + r >> 1;
	if (y <= mid)
		return query(o << 1, l, mid, x, y);
	else if (x > mid)
		return query(o << 1 | 1, mid + 1, r, x, y);
	else if ((y - mid) & 1)
		return query(o << 1, l, mid, x, mid) - query(o << 1 | 1, mid + 1, r, mid + 1, y);
	else
		return query(o << 1, l, mid, x, mid) + query(o << 1 | 1, mid + 1, r, mid + 1, y);
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (register int i = 1; i <= n; ++i)
		scanf("%llu", a + i);
	build(1, 1, n);
	while (m--) {
		scanf("%d%d%llu", &op, &x, &y);
		switch (op) {
			case 0 : {
				ano = query(1, 1, n, x + 1, y);
				y = ((y - x) & 1) ? ~a[x] : a[x];
				y = (((ano.a & ano.b) | ((~ano.a) & y)) << 64 - k) >> 64 - k;
				printf("%llu\n", y);
				break;
			}
			case 1 : {
				a[x] = y;
				modify(1, 1, n, x, y);
				break;
			}
		}
	}
	return 0;
}
