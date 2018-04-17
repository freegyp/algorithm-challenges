tt = int(raw_input())

def sortCheck(nums):
	odds,evens = [],[]
	for i in xrange(len(nums)):
		if i%2==0:
			evens.append(nums[i])
		else:
			odds.append(nums[i])
	odds.sort()
	evens.sort()
	expected,actual = sorted(nums),[(odds[i/2] if i%2==1 else evens[i/2]) for i in xrange(len(nums))]
	for i in xrange(len(nums)):
		if expected[i]!=actual[i]:
			return i
	return -1

for t in xrange(1,tt+1):
	n = int(raw_input())
	nums = map(int,raw_input().split())
	res = sortCheck(nums)
	if res>=0:
		print "Case #{0}: {1}".format(t,res)
	else:
		print "Case #{0}: OK".format(t)