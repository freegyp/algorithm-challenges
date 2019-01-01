def kmpTable(s):
	table = [0 for i in xrange(len(s)+1)]
	i,j = 1,0
	while i<len(s):
		if s[i]==s[j]:
			table[i+1] = j+1
			i,j = i+1,j+1
		elif j==0:
			i += 1
		else:
			j = table[j]
	return table

fin = open("ethan_searches_for_a_string.txt",'r')

tt = int(fin.readline())

fout = open("output.out",'w')

for t in xrange(1,tt+1):
	s = fin.readline()
	if s[-1]=='\n':
		s = s[:len(s)-1]
	table = kmpTable(s)
	pivot = None
	for i in xrange(len(s)):
		if table[i]>0 and s[i]!=s[table[i]]:
			pivot = i
			break
	if pivot==None:
		fout.write("Case #{0}: Impossible\n".format(t))
	else:
		fout.write("Case #{0}: {1}\n".format(t,s[:pivot]+s[table[pivot]:]))