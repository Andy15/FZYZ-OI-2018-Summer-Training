from random import *
from sys import stdout

N = 100000
P = 1000000000
M = 100000
S = 1000000000

print N, P
for i in range(1, N + 1):
	print randint(1, S),
print
print M
for i in range(1, M + 1):
	opt, l, r, v = randint(1, 3), randint(1, N), randint(1, N), randint(1, S)
	if l > r:
		l, r = r, l
	print opt, l, r,
	if opt < 3:
		print v,
	print
