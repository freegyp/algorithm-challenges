tt = int(raw_input())

for t in xrange(tt):
	raw_input()
	n,m = map(int,raw_input().split())
	edges,node2edges = [],{i:{} for i in xrange(1,n+1)}
	for i in xrange(m):
		left,right,length = map(int,raw_input().split())
		node2edges[left][len(edges)] = True
		node2edges[right][len(edges)] = True
		edges.append((left,right,length))
	twos = [i for i in xrange(1,n+1) if len(node2edges[i])==2]
	blacklist = {}
	for i in twos:
		newEdge,newLen = [],0
		for edge in node2edges[i]:
			blacklist[edge] = True
			left,right,length = edges[edge]
			if right==i:
				temp = right
				right = left
				left = temp
			newEdge.append(right)
			del node2edges[right][edge]
			node2edges[right][len(edges)] = True
			newLen += length
		newEdge.append(newLen)
		edges.append(tuple(newEdge))
	print len(edges)-len(blacklist)
	for i in xrange(len(edges)):
		if i not in blacklist:
			print "{0} {1} {2}".format(edges[i][0],edges[i][1],edges[i][2])
	if t!=tt-1:
		print ""