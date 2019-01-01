tt = int(raw_input())

fout = open("output.out",'w')

for t in xrange(1,tt+1):
	n,k,v = map(int,raw_input().split())
	names,toVisit = [],[]
	for i in xrange(n):
		name = raw_input()
		names.append(name)
		toVisit.append(False)
	offset = ((v-1)*k)%n
	for i in xrange(k):
		toVisit[(offset+i)%n] = True
	ans = []
	for i in xrange(n):
		if toVisit[i]:
			ans.append(names[i])
	fout.write("Case #{0}: {1}\n".format(t," ".join(ans)))