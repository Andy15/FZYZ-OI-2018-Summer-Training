from random import *
from sys import stdout

N = 1000000
S = 1000
print N
for i in range(1, N + 1):
	a, b = randint(1, S), randint(1, S);
	if a > b:
		a, b = b, a
	print a, b
print
