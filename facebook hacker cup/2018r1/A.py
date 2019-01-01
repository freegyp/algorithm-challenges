fin = open("let_it_flow.txt","r")
fout = open("A.out",'w')

tt = int(fin.readline())

for t in xrange(1,tt+1):
	n = int(fin.readline())
	house = [[False,False,False] for i in xrange(n)]
	for j in xrange(3):
		line = fin.readline()
		for i in xrange(n):
			house[i][j] = True if line[i]=='.' else False
	table = [1,0,0]
	for i in xrange(n):
		vTable = []
		for j in xrange(3):
			if house[i][j]:
				vTable += [table[j],table[j]]
			else:
				vTable += [0,0]
		table = [0,0,0]
		table[0] = vTable[2] if house[i][0] else 0
		table[1] = vTable[1]+vTable[4] if house[i][1] else 0
		table[2] = vTable[3] if house[i][2] else 0
		table = map(lambda x:x%1000000007,table)
	fout.write("Case #{0}: {1}\n".format(t,table[2]))