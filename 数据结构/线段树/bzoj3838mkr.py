from random import *
from sys import stdout

N = 500000
K = randint(1, N)
S = 1000000000
print N, K
for i in range(1, N + 1):
	print randint(1, S),
print
for i in range(1, N + 1):
	print randint(1, S),
print

