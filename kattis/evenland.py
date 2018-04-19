mod = 10**9 + 9

n,m = map(int,raw_input().split())

graph = {i:{} for i in xrange(1,n+1)}

for i in xrange(m):
	a,b = map(int,raw_input().split())
	graph[a][b] = True
	graph[b][a] = True

past,islands = {},0

for i in xrange(1,n+1):
	if i not in past:
		islands,past[i],stack = islands+1,True,[i]
		while len(stack)>0:
			cur = stack.pop()
			for neigh in graph[cur]:
				if neigh not in past:
					past[neigh] = True
					stack.append(neigh)

ans = (2**(m-n+islands))%mod

print ans