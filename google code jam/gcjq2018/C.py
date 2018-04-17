import heapq
import sys

#ftest = open("Clog.txt",'w')

tt = int(raw_input())
for t in xrange(1,tt+1):
	a = int(raw_input())
	x,y,area = 9,9,0
	while area<a:
		mask = 0
		coords = [(x-1,y-1),(x-1,y),(x-1,y+1),(x,y-1),(x,y),(x,y+1),(x+1,y-1),(x+1,y),(x+1,y+1)]
		coord2mask = {coord:(1<<i) for i,coord in enumerate(coords)}
		while mask!=511:
			print "{0} {1}".format(x,y)
			sys.stdout.flush()
			xx,yy = map(int,raw_input().split())
			if (xx,yy)==(0,0):
				area = a
				break
			mask |= coord2mask[(xx,yy)]
		x += 3
		area += 9