fin = open("ethan_finds_the_shortest_path.txt",'r')
fout = open("A.out",'w')

tt = int(fin.readline())

for t in xrange(1,tt+1):
	n,k = map(int,fin.readline().split())
	if n<3 or k<3:
		fout.write("Case #{0}: 0\n".format(t))
		fout.write("1\n1 n k\n")
	else:
		total,edges = -k,[[1,n,k]]
		for i in xrange(1,min(n,k)):
			if i==min(n,k)-1:
				edges.append([i,n,k-i])
			else:
				edges.append([i,i+1,k-i])
			total += k-i
		fout.write("Case #{0}: {1}\n".format(t,total))
		fout.write("{0}\n".format(len(edges)))
		for start,end,weight in edges:
			fout.write("{0} {1} {2}\n".format(start,end,weight))