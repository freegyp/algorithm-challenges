tt = int(raw_input())

for t in xrange(tt):
	n,m,l = map(int,raw_input().split())
	neighbors,fallen = {i:{} for i in xrange(1,n+1)},{}
	for i in xrange(m):
		left,right = map(int,raw_input().split())
		neighbors[left][right] = True
	for i in xrange(l):
		cur = int(raw_input())
		stack,fallen[cur] = [cur],True
		while len(stack)>0:
			j = stack.pop()
			for neigh in neighbors[j]:
				if neigh not in fallen:
					fallen[neigh] = True
					stack.append(neigh)
	print len(fallen)