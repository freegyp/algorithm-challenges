tt = int(raw_input())

fout = open("output.out",'w')

for t in xrange(1,tt+1):
	n = int(raw_input())
	coefs = []
	for i in xrange(n+1):
		c = int(raw_input())
		if i==n:
			coefs.append(c)
		else:
			coefs.append(i+1+c)
	possible = False
	if n%2==1:
		possible = True
		#for i in xrange(n):
		#	if i%2==0 and coefs[i]<0:
		#		possible = False
		#		break
	if possible:
		fout.write("Case #{0}: 1\n".format(t))
		fout.write("0.0\n")
	else:
		fout.write("Case #{0}: 0\n".format(t))