import heapq

def safeInsert(costGraph,capGraph,start,end,cost,capacity):
	if start not in costGraph:
		costGraph[start] = {}
	costGraph[start][end] = cost
	if start not in capGraph:
		capGraph[start] = {}
	capGraph[start][end] = capacity
	if end not in costGraph:
		costGraph[end] = {}
	costGraph[end][start] = -cost
	if end not in capGraph:
		capGraph[end] = {}
	capGraph[end][start] = 0

def minCostFlow(costGraph,capGraph,start,end,flow):
	total = 0
	preCum = {i:0 for i in costGraph}
	while flow>0:
		heap,dist,pred = [(0,start)],{start:0},{start:None}
		while len(heap)>0:
			d,cur = heapq.heappop(heap)
			if d==dist[cur]:
				if cur in capGraph:
					for neigh in capGraph[cur]:
						if capGraph[cur][neigh]>0 and (neigh not in dist or preCum[cur]-preCum[neigh]+d+costGraph[cur][neigh]<dist[neigh]):
							dist[neigh] = preCum[cur]-preCum[neigh]+d+costGraph[cur][neigh]
							heapq.heappush(heap,(dist[neigh],neigh))
							pred[neigh] = cur
		if end not in dist:
			return -1
		cur = end
		while pred[cur]!=None:
			capGraph[pred[cur]][cur] -= 1
			capGraph[cur][pred[cur]] += 1
			cur = pred[cur]
		flow -= 1
		for i in dist:
			preCum[i] += dist[i]
		total += preCum[end]
	return total

while True:
	n,m = map(int,raw_input().split())
	if (n,m)==(0,0):
		break
	start,end,costGraph,capGraph = n+m,n+m+1,{},{}
	for i in xrange(n):
		cap = int(raw_input())
		safeInsert(costGraph,capGraph,i,end,0,cap)
	for i in xrange(n,n+m):
		y,first,second,third,fourth = map(int,raw_input().split())
		safeInsert(costGraph,capGraph,i,first,(3-y)*4,1)
		safeInsert(costGraph,capGraph,i,second,(3-y)*4+1,1)
		safeInsert(costGraph,capGraph,i,third,(3-y)*4+2,1)
		safeInsert(costGraph,capGraph,i,fourth,(3-y)*4+3,1)
		safeInsert(costGraph,capGraph,start,i,0,1)
	offset = minCostFlow(costGraph,capGraph,start,end,m)
	ans = 12*m-offset
	print ans

