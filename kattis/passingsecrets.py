import heapq

def dijkstra(dist,traceStack):
	past,preDec,checked,heap = {0:0},{0:None},False,[(0,0)]
	while not checked and len(heap)>0:
		d,cur = heapq.heappop(heap)
		if d==past[cur]:
			if cur==1:
				checked = True
				break
			for neigh in dist[cur]:
				if neigh not in past or past[neigh]>d+dist[cur][neigh]:
					past[neigh] = d+dist[cur][neigh]
					preDec[neigh] = cur
					heapq.heappush(heap,(past[neigh],neigh))
	if not checked:
		return -1
	else:
		cur = 1
		while cur!=None:
			traceStack.append(cur)
			cur = preDec[cur]
		return past[1]

def safeInsert(dist,left,right,size):
	if left!=1 and right!=0:
		lNode = left if left==0 else left+1
		if right in dist[lNode]:
			dist[lNode][right] = min(size,dist[lNode][right])
		else:
			dist[lNode][right] = size
	if right!=1 and left!=0:
		rNode = right if right==0 else right+1
		if left in dist[rNode]:
			dist[rNode][left] = min(size,dist[rNode][left])
		else:
			dist[rNode][left] = size

while True:
	try:
		inName,outName = raw_input().split()
	except:
		break
	n = int(raw_input())
	id2name,name2id,curId,dist = {0:inName,1:outName},{inName:0,outName:1},2,{0:{}}
	for i in xrange(n):
		club = raw_input().split()
		for name in club:
			if name not in name2id:
				name2id[name] = curId
				id2name[curId] = name
				dist[curId],dist[curId+1] = {curId+1:1},{}
				curId += 2
		for j in xrange(len(club)):
			for k in xrange(j+1,len(club)):
				safeInsert(dist,name2id[club[j]],name2id[club[k]],len(club)-2)
	stack = []
	ans = dijkstra(dist,stack)
	if ans==-1:
		print "impossible"
	else:
		res = [str(ans)]
		while len(stack)>0:
			cur = stack.pop()
			if cur in id2name:
				res.append(id2name[cur])
		print ' '.join(res)

