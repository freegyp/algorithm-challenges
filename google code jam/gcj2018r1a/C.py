from math import sqrt

tt = int(raw_input())

for t in xrange(1,tt+1):
	n,p = map(int,raw_input().split())
	p = float(p)
	noCut,cutUpper,incs = 0.0,0.0,0.0,[]
	for i in xrange(n):
		w,h = map(float,raw_input().split())
		noCut += (w+h)*2.0
		cutUpper += (w+h)*2.0 + 2*sqrt(w*w+h*h)
		incs.append((2*min(w,h),2*sqrt(w*w+h*h)))
	incs.sort()
	start,end,i = noCut,noCut,0
	while end<p:
		w,diag = incs[i]
		if end>=start+w:
			end += diag
		else:
			preInc = end-start
			start,end = start+w,end+diag+preInc
	ans = min(p,cutUpper)
	print "Case #{0}: {1}".format(t,ans)