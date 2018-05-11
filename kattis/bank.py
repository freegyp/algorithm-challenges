import heapq

n,t = map(int,raw_input().split())

customers = []

for i in xrange(n):
	cc,tt = map(int,raw_input().split())
	if tt<=t:
		customers.append((tt,cc))

customers.sort()

heap = []

for tt,cc in customers:
	if len(heap)>tt and heap[0]<cc:
		heapq.heappop(heap)
	if len(heap)<=tt:
		heapq.heappush(heap,cc)

print sum(heap)