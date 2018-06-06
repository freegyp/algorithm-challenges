table = []
for i in xrange(65):
	table.append(3**i)

while True:
	i = int(raw_input())
	if i==0:
		break
	i -= 1
	res = []
	for j in xrange(65):
		if i&(1<<j):
			res.append(str(table[j]))
	ans = ", ".join(res)
	if len(ans)>0:
		print "{ "+ans+" }"
	else:
		print "{ }"