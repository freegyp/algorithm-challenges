from collections import deque
tt = int(raw_input())

for t in xrange(tt):
	empty = raw_input()
	n = int(raw_input())
	nums = []
	for i in xrange(n):
		name,rank = raw_input().split()
		rank = int(rank)
		nums.append(rank)
	ans = 0
	queue,left,missing,cur = deque(sorted(nums)),deque([]),deque([]),1
	while len(queue)>0:
		num = queue.popleft()
		if num==cur:
			cur += 1
		elif num>cur:
			while cur<num:
				missing.append(cur)
				cur += 1
			cur += 1
		else:
			left.append(num)
	while cur<=n:
		missing.append(cur)
		cur += 1
	while len(left)>0:
		l,m = left.popleft(),missing.popleft()
		ans += abs(l-m)
	print ans