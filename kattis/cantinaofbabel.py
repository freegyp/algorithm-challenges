langIds,langTargets,speaking,neighbors,reachable = {},{},[],{},{}

n = int(raw_input())

for i in xrange(n):
	comps = raw_input().split()
	neighbors[i] = {}
	for lang in comps[1:]:
		if lang not in langIds:
			langIds[lang] = len(langIds)
			langTargets[langIds[lang]] = []
		langTargets[langIds[lang]].append(i)
	speaking.append(langIds[comps[1]])

for i in xrange(n):
	for j in langTargets[speaking[i]]:
		neighbors[i][j] = True

for i in xrange(n):
	reachable[i],stack = {i:True},[i]
	while len(stack)>0:
		cur = stack.pop()
		for neigh in neighbors[cur]:
			if neigh not in reachable[i]:
				reachable[i][neigh] = True
				stack.append(neigh)

mutGraph = {i:{} for i in xrange(n)}

for i in xrange(n):
	for j in xrange(i+1,n):
		if j in reachable[i] and i in reachable[j]:
			mutGraph[i][j] = True
			mutGraph[j][i] = True

checked,remain = {},0

for i in xrange(n):
	if i not in checked:
		checked[i],stack,curRem = True,[i],0
		while len(stack)>0:
			cur = stack.pop()
			curRem += 1
			for neigh in mutGraph[cur]:
				if neigh not in checked:
					checked[neigh] = True
					stack.append(neigh)
		remain = max(remain,curRem)

print n-remain