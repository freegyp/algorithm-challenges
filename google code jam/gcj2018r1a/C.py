from math import sqrt

def merge(intervals):
	intervals.sort()
	res = []
	for start,end in intervals:
		if len(res)==0 or start>res[-1][1]:
			res.append([start,end])
		else:
			res[-1][1] = max(res[-1][1],end)
	return res

tt = int(raw_input())

for t in xrange(1,tt+1):
	n,p = map(int,raw_input().split())
	p = float(p)
	noCut,incs = 0.0,[]
	for i in xrange(n):
		w,h = map(float,raw_input().split())
		noCut += (w+h)*2.0
		incs.append((2.0*min(w,h),2.0*sqrt(w*w+h*h)))
	incs.sort()
	allIntervals = [[noCut,noCut]]
	for start,end in incs:
		toPush = []
		for i in xrange(len(allIntervals)):
			toPush.append([allIntervals[i][0]+start,allIntervals[i][1]+end])
		for i in xrange(len(toPush)):
			allIntervals.append(toPush[i])
		allIntervals = merge(allIntervals)
	ans = noCut
	for start,end in allIntervals:
		if start<=p:
			ans = max(ans,min(end,p))
	print "Case #{0}: {1}".format(t,ans)