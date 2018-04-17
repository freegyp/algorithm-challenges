tt = int(raw_input())

def getCum(cdf,low,left,up,right):
	return cdf[up][right]-cdf[low][right]-cdf[up][left]+cdf[low][left]

def cdfSplit(cdf,r,c,h,v,each):
	table,found = {},{}
	for i in xrange(1,h):
		for j in xrange(1,v):
			table[(i*j*each,i*(v-j)*each,(h-i)*j*each,(h-i)*(v-j)*each)] = True
	for i in xrange(1,r):
		for j in xrange(1,c):
			ll,lr = getCum(cdf,0,0,i,j),getCum(cdf,0,j,i,c)
			ul,ur = getCum(cdf,i,0,r,j),getCum(cdf,i,j,r,c)
			if (ll,lr,ul,ur) in table:
				found[ll,lr,ul,ur] = True
	return len(table)==len(found)

for t in xrange(1,tt+1):
	r,c,h,v = map(int,raw_input().split())
	cdf = [[0 for j in xrange(c+1)] for i in xrange(r+1)]
	for i in xrange(r):
		row = raw_input()
		for j in xrange(c):
			cdf[i+1][j+1] = cdf[i][j+1]+cdf[i+1][j]-cdf[i][j]
			if row[j]=='@':
				cdf[i+1][j+1] += 1
	ans = cdf[-1][-1]%((h+1)*(v+1))==0
	if ans:
		each = cdf[-1][-1]/((h+1)*(v+1))
		ans = cdfSplit(cdf,r,c,h+1,v+1,each)
	if ans:
		print "Case #{0}: POSSIBLE".format(t)
	else:
		print "Case #{0}: IMPOSSIBLE".format(t)