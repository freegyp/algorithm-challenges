while True:
	n,k = map(int,raw_input().split())
	if (n,k)==(0,0):
		break
	table = [[-1,-1,-1] for i in xrange(k+1)]
	table[0] = [-1,-1,0]
	for i in xrange(n):
		a,b = map(int,raw_input().split())
		nextTable = [[-1,-1,-1] for i in xrange(k+1)]
		for j in xrange(k+1):
			if max(table[j])>=0:
				nextTable[j][2] = a+b+max(table[j])
			if j>0 and max(table[j-1])>=0:
				nextTable[j][0] = a+max(table[j-1][0],table[j-1][2])
				nextTable[j][1] = b+max(table[j-1][1],table[j-1][2])
		table = nextTable
	print max(table[-1])