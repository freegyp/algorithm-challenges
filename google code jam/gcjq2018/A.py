tt = int(raw_input())

for t in xrange(1,tt+1):
	d,p = raw_input().split()
	d = int(d)
	total,layerCount = 0,[0]
	for c in p:
		if c=='S':
			total += 1<<(len(layerCount)-1)
			layerCount[-1] += 1
		else:
			layerCount.append(0)
	if total>d:
		ops = 0
		while len(layerCount)>1 and total>d:
			if layerCount[-1]==0:
				layerCount.pop()
			else:
				total -= 1<<(len(layerCount)-2)
				layerCount[-1] -= 1
				layerCount[-2] += 1
				ops += 1
		if total>d:
			print "Case #{0}: IMPOSSIBLE".format(t)
		else:
			print "Case #{0}: {1}".format(t,ops)
	else:
		print "Case #{0}: 0".format(t)