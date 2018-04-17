class Node:
	def __init__(self,s):
		self.id = None
		self.val = None
		self.range = [None,None]
		self.neighbors = []
		try:
			val = float(s)
			self.val = val
		except:
			pass

def dfs(graph,maxDist):
	stack,past = [],{}
	for k in graph:
		if graph[k].val==None:
			graph[k].range = [None,None]
		elif len(stack)==0:
			stack.append(graph[k])
			past[k] = True
	while len(stack)>0:
		cur = stack.pop()
		for neigh in cur.neighbors:
			if neigh.id not in past:
				if neigh.val==None:
					if cur.val==None:
						neigh.range = [cur.range[0]-maxDist,cur.range[1]+maxDist]
					else:
						neigh.range = [cur.val-maxDist,cur.val+maxDist]
				else:
					if cur.val==None:
						if neigh.val<cur.range[0]-maxDist or neigh.val>cur.range[1]+maxDist:
							return False
					else:
						if abs(neigh.val-cur.val)>maxDist:
							return False
				past[neigh.id] = True
				stack.append(neigh)
	return True

def minMaxDist(graph):
	lower,upper = 0.0,60000000.0
	while upper-lower>=0.0000001:
		mid = (upper+lower)/2.0
		if dfs(graph,mid):
			upper = mid
		else:
			lower = mid
	return upper


n = int(raw_input())

nodes = map(Node,raw_input().split())

graph = {}

for i in xrange(n):
	nodes[i].id = i+1
	graph[i+1] = nodes[i]

for i in xrange(n-1):
	left,right = map(int,raw_input().split())
	graph[left].neighbors.append(graph[right])
	graph[right].neighbors.append(graph[left])

ans = minMaxDist(graph)

print "{0:.7f}\n".format(ans)



