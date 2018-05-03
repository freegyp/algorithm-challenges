def safeInsert(graph,left,right):
	graph[left][right] = True
	graph[right][left] = True

def dfs(graph):
	checked,stack = {1:True},[1]
	while len(stack)>0:
		cur = stack.pop()
		for neigh in graph[cur]:
			if neigh not in checked:
				checked[neigh] = True
				stack.append(neigh)
	return checked

n,m = map(int,raw_input().split())

graph = {i:{} for i in xrange(1,n+1)}

for i in xrange(m):
	left,right = map(int,raw_input().split())
	safeInsert(graph,left,right)

connected = dfs(graph)

if len(connected)==n:
	print "Connected"
else:
	for i in xrange(1,n+1):
		if i not in connected:
			print i