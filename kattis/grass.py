from math import sqrt
import heapq

while True:
	try:
		n,l,w = raw_input().split()
	except:
		break
	n,l,w = int(n),float(l),float(w)
	circles = []
	for i in xrange(n):
		x,r = map(float,raw_input().split())
		try:
			offset = sqrt(r*r-0.25*w*w)
			circles.append((x-offset,x+offset))
		except:
			pass
	circles.sort()
	heap,impossible = [(0,0.0)],False
	for start,end in circles:
		while len(heap)>0 and heap[0][1]<start:
			heapq.heappop(heap)
		if len(heap)==0:
			impossible = True
			break
		heapq.heappush(heap,(heap[0][0]+1,end))
	if not impossible:
		while len(heap)>0 and heap[0][1]<l:
			heapq.heappop(heap)
		if len(heap)==0:
			impossible = True
	if impossible:
		print -1
	else:
		print heap[0][0]