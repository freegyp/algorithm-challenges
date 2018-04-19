import heapq

tt = int(raw_input())

for t in xrange(tt):
	n = int(raw_input())
	ans = 0
	heap = map(int,raw_input().split())
	heapq.heapify(heap)
	while len(heap)>1:
		first = heapq.heappop(heap)
		second = heapq.heappop(heap)
		ans += first+second
		heapq.heappush(heap,first+second)
	print ans