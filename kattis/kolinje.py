from fractions import *

n = int(raw_input())

records = []

for i in xrange(n):
	a,b = map(int,raw_input().split())
	records.append((a,b))

possible = True

lowers,uppers = [],[]

for i in xrange(n-1):
	a1,b1,a2,b2 = records[i][0],records[i][1],records[i+1][0],records[i+1][1]
	if b1>b2:
		lowers.append(Fraction(a2-a1,b1-b2))
	elif b1<b2:
		uppers.append(Fraction(a1-a2,b2-b1))
	elif a1<a2:
		possible = False
		break

lower,upper = 0,0

if possible:
	lower,upper = max(lowers),min(uppers)
	if upper<lower:
		possible = False

if possible:
	fact = 0
	for _,x in records:
		fact += x
	print float(lower*fact)
else:
	print -1