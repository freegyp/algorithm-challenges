from collections import deque

def safeInsert(graph,left,right):
	if left not in graph:
		graph[left] = {}
	graph[left][right] = True
	if right not in graph:
		graph[right] = {}
	graph[right][left] = True

def trace(graph,start,end):
	queue = deque([start])
	pred = {start:None}
	while len(queue)>0:
		cur = queue.popleft()
		if cur in graph:
			for neigh in graph[cur]:
				if neigh not in pred:
					pred[neigh] = cur
					queue.append(neigh)
	if end not in pred:
		return "no route found"
	else:
		stack = [end]
		while pred[stack[-1]]!=None:
			stack.append(pred[stack[-1]])
		stack = stack[::-1]
		return " ".join(stack)

graph = {}

n = int(raw_input())

for i in xrange(n):
	line = raw_input().split()
	for neigh in line[1:]:
		safeInsert(graph,line[0],neigh)

start,end = raw_input().split()

print trace(graph,start,end)