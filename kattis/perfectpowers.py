while True:
	num = int(raw_input())
	if num<0:
		sign = -1
	elif num==0:
		break
	else:
		sign = 1
	num *= sign
	ans = 1
	for i in xrange(1,33):
		lower,upper = 1,num+1
		while upper-lower>1:
			mid = (upper+lower)/2
			res = 1
			for j in xrange(i):
				res *= mid
			if res<=num:
				lower = mid
			else:
				upper = mid
		res = 1
		for j in xrange(i):
			res *= lower
		if res==num:
			if i%2==0 and sign==-1:
				continue
			else:
				ans = i
	print ans