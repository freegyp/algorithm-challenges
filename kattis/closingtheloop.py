n = int(raw_input())

for i in xrange(n):
	s = int(raw_input())
	comps = raw_input().split()
	reds,blues = [],[]
	for comp in comps:
		if comp[-1]=='B':
			blues.append(int(comp[:len(comp)-1]))
		else:
			reds.append(int(comp[:len(comp)-1]))
	reds.sort(key = lambda k:-k)
	blues.sort(key = lambda k:-k)
	while len(reds)!=len(blues):
		if len(reds)>len(blues):
			reds.pop()
		else:
			blues.pop()
	ans = sum(reds)+sum(blues)-len(reds)*2
	print "Case #{0}: {1}".format(i+1,ans)
