tt = int(raw_input())

for t in xrange(1,tt+1):
	c = int(raw_input())
	nums = map(int,raw_input().split())
	if nums[0]==0 or nums[-1]==0:
		print "Case #{0}: IMPOSSIBLE".format(t)
	else:
		cdf = []
		for num in nums:
			if len(cdf)==0:
				cdf.append(num)
			else:
				cdf.append(cdf[-1]+num)
		j = 0
		columns = [[] for i in xrange(c)]
		for i in xrange(c):
			while cdf[j]<=i:
				j += 1
			if j<i:
				for k in xrange(i,j,-1):
					columns[k].append('/')
			elif j>i:
				for k in xrange(i,j):
					columns[k].append('\\')
		ans = 1
		for cc in columns:
			ans = max(ans,len(cc)+1)
		print "Case #{0}: {1}".format(t,ans)
		for i in xrange(ans):
			row = []
			for j in xrange(c):
				if i>=len(columns[j]):
					row.append('.')
				else:
					row.append(columns[j][i])
			print "".join(row)