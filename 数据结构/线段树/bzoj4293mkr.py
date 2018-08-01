from random import *
from sys import stdout

N = 500000
M = 500000
S = 1000000
S2 = 1000000000000
print N, M
for i in range(0, N):
	print randint(1, S),
print
for i in range(0, M):
	print i * randint(1, S), randint(1, S2)
print
