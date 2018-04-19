#Not accepted yet.

mod = 10**9 + 7

def gcd(x,y):
	while y>0:
		z = x%y
		x = y
		y = z
	return x

def dpCount(nums):
	if len(nums)<2:
		return 1
	elif len(nums)==2:
		return 1 if gcd(nums[0],nums[1])>1 else 0
	res = 0
	for i in xrange(1,len(nums)):
		if gcd(nums[i],nums[0])>1:
			if i>1:
				res += dpCount(nums[:i])*dpCount(nums[i:])
			if i!=len(nums)-1:
				res += dpCount(nums[1:i+1])*dpCount(nums[i+1:]+nums[:1])
			res %= mod
	return res

n = int(raw_input())

nums = []

for i in xrange(n):
	num = int(raw_input())
	nums.append(num)

print dpCount(nums)
