n = int(raw_input())

pred,depth,v2node = {0:{(1<<i):0 for i in xrange(19)}},{0:0},[0]

def lcaDepth(left,right,pred,depth):
	if depth[right]>depth[left]:
		temp = right
		right = left
		left = temp
	dDepth = depth[left]-depth[right]
	while dDepth>0:
		left = pred[left][dDepth&-dDepth]
		dDepth -= dDepth&-dDepth
	base = 1<<18
	while base>0:
		if pred[left][base]!=pred[right][base]:
			left,right = pred[left][base],pred[right][base]
		base >>= 1
	if left==right:
		return depth[left]
	else:
		return depth[left]-1

for i in xrange(1,n+1):
	line = raw_input().split()
	if len(line)==3:
		v2node.append(v2node[int(line[1])])
		print lcaDepth(v2node[-1],v2node[int(line[2])],pred,depth)
	elif line[0]=='a':
		v2node.append(i)
		pred[i] = {1:v2node[int(line[1])]}
		depth[i] = depth[pred[i][1]]+1
		for j in xrange(1,19):
			pred[i][1<<j] = pred[pred[i][1<<(j-1)]][1<<(j-1)]
	elif line[0]=='b':
		print v2node[int(line[1])]
		v2node.append(pred[v2node[int(line[1])]][1])