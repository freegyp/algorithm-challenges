def bashGraph(total):
	preNode = {}
	for i in xrange(3,70):
		preNode[1<<(i-3)] = i
	initialNeighs = []
	while total>0:
		initialNeighs.append(preNode[total&-total])
		total -= total&-total
	print "YES"
	print "{0} {1}".format(max(initialNeighs),(max(initialNeighs)-2)*(max(initialNeighs)-1)/2+len(initialNeighs))
	for i in xrange(3,max(initialNeighs)+1):
		for j in xrange(i-1,1,-1):
			print "{0} {1} {2}".format(i,j,i-j)
	for i in initialNeighs:
		print "{0} {1} {2}".format(1,i,max(initialNeighs)+1-i)

def chiGraph(total):
	fib = [1,1]
	while sum(fib)<(10**18):
		fib.append(sum(fib[-2:]))
	initialNeighs = []
	for i in xrange(len(fib)-1,-1,-1):
		if total>=fib[i]:
			initialNeighs.append(i+2)
			total -= fib[i]
	if total>0:
		print "NO"
		return
	print "YES"
	print "{0} {1}".format(max(initialNeighs),(max(initialNeighs)-3)*2+1+len(initialNeighs))
	for i in xrange(3,max(initialNeighs)+1):
		for j in xrange(i-1,max(1,i-3),-1):
			print "{0} {1} {2}".format(i,j,i-j)
	for i in initialNeighs:
		print "{0} {1} {2}".format(1,i,max(initialNeighs)+1-i)

while True:
	a = int(raw_input())
	if a==-1:
		break
	elif a==0:
		print "YES"
		print "2 0"
		print "YES"
		print "2 0"
	else:
		bashGraph(a)
		chiGraph(a)