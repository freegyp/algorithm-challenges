#TLE with Python. Same method accepted in C++.

import sys

sys.setrecursionlimit(8000)

def isSubseq(fossils,left,right,mem):#Check if left is a substr of right
	if (left,right) not in mem:
		j = 0
		for c in fossils[right]:
			if c==fossils[left][j]:
				j += 1
				if j>=len(fossils[left]):
					mem[(left,right)] = True
					return True
		mem[(left,right)] = False
	return mem[(left,right)]

def recoverAns(fossils,ans1,ans2,i,j,pred):
	if (i,j)==(0,0):
		return
	x,y = pred[(i,j)]
	if y==i:
		recoverAns(fossils,ans2,ans1,x,y,pred)
	else:
		recoverAns(fossils,ans1,ans2,x,y,pred)
	ans2.append(j)

n = int(raw_input())

fossils = []

for i in xrange(n+1):
	s = raw_input()
	fossils.append(s)

fossils.sort(key = lambda s:-len(s))

stack,pred,mem = [(0,0)],{},{}

while len(stack)>0 and stack[-1][1]<n:
	i,j = stack.pop()
	if (j,j+1) not in pred and isSubseq(fossils,j+1,i,mem):
		pred[(j,j+1)] = (i,j)
		stack.append((j,j+1))
	if (i,j+1) not in pred and isSubseq(fossils,j+1,j,mem):
		pred[(i,j+1)] = (i,j)
		stack.append((i,j+1))

if len(stack)==0:
	print "impossible"
else:
	ans1,ans2 = [],[]
	recoverAns(fossils,ans1,ans2,stack[-1][0],stack[-1][1],pred)
	ans1,ans2 = ans1[::-1],ans2[::-1]
	print "{0} {1}".format(len(ans1),len(ans2))
	for i in ans1:
		print fossils[i]
	for i in ans2:
		print fossils[i]

