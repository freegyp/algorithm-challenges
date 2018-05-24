#Not accepted yet...
tt = int(raw_input())

for t in xrange(1,tt+1):
	n = int(raw_input())
	rows,cols = {i:{} for i in xrange(n)},{i:{} for i in xrange(n)}
	stage,total = [],0
	for i in xrange(n):
		row = map(int,raw_input().split())
		stage.append(row)
	for i in xrange(n):
		for j in xrange(n):
			if stage[i][j] not in rows[i]:
				rows[i][stage[i][j]] = 1
			else:
				rows[i][stage[i][j]] += 1
	for i in xrange(n):
		for j in xrange(n):
			if stage[i][j]<=n and stage[i][j] not in cols[j]:
				cols[j][stage[i][j]] = 1
			else:
				cols[j][stage[i][j]] += 1
	for i in xrange(n):
		for j in xrange(n):
			if rows[i][stage[i][j]]>1 and cols[j][stage[i][j]]>1:
				rows[i][stage[i][j]] -= 1
				cols[j][stage[i][j]] -= 1
				stage[i][j] = n+1
				total += 1
	for i in xrange(n):
		for j in xrange(n):
			if stage[i][j]<=n and rows[i][stage[i][j]]>1:
				rows[i][stage[i][j]] -= 1
				total += 1
			elif stage[i][j]<=n and cols[j][stage[i][j]]>1:
				cols[j][stage[i][j]] -= 1
				total += 1
	print "Case #{0}: {1}".format(t,total)