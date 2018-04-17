tt = int(raw_input())

def timeSearch(r,b,cashiers):
	lower,upper = 0,10**19
	while upper-lower>1:
		mid = (upper+lower)/2
		items = []
		for m,s,p in cashiers:
			num = max(min((mid-p)/s,m),0)
			items.append(num)
		items.sort(key = lambda x:-x)
		total = sum(items[:r])
		if total>=b:
			upper = mid
		else:
			lower = mid
	return upper

for t in xrange(1,tt+1):
	r,b,c = map(int,raw_input().split())
	cashiers = []
	for i in xrange(c):
		m,s,p = map(int,raw_input().split())
		cashiers.append((m,s,p))
	time = timeSearch(r,b,cashiers)
	print "Case #{0}: {1}".format(t,time)