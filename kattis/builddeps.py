def toposort(depends,revDepends,skip=None):
	zeros,sequence = [i for i in depends if len(depends[i])==0 and i!=skip],[]
	while len(zeros)>0:
		cur = zeros.pop()
		del depends[cur]
		sequence.append(cur)
		if cur in revDepends:
			for neigh in revDepends[cur]:
				del depends[neigh][cur]
				if neigh!=skip and len(depends[neigh])==0:
					zeros.append(neigh)
	return sequence

n = int(raw_input())

depends,revDepends = {},{}

for i in xrange(n):
	left,right = raw_input().split(':')
	_deps = right.split()
	depends[left] = {}
	for dep in _deps:
		if len(dep)>0:
			if dep not in revDepends:
				revDepends[dep] = {}
			revDepends[dep][left] = True
			depends[left][dep] = True

f = raw_input()

toposort(depends,revDepends,skip = f)

seq = toposort(depends,revDepends)

for f in seq:
	print f
