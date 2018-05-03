word2nums = {}
n = int(raw_input())
for i in xrange(n):
	left,right = raw_input().split()
	if left not in word2nums:
		word2nums[left] = []
	word2nums[left].append(int(right))
for k in word2nums:
	word2nums[k].sort()
q = int(raw_input())
for i in xrange(q):
	left,right = raw_input().split()
	print word2nums[left][int(right)-1]