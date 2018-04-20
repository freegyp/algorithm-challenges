#Not accepted yet.

from math import sqrt

def minDist(x10,y10,x11,y11,x20,y20,x21,y21):
	#This function is wrong, will fix later.
	dist1 = sqrt((x20-x10)*(x20-x10)+(y20-y10)*(y20-y10))
	dist2 = sqrt((x21-x11)*(x21-x11)+(y21-y11)*(y21-y11))
	return min(dist1,dist2)

def searchTime(lineSegs1,timeSegs1,lineSegs2,timeSegs2):
	lower,upper = 0.0,min(timeSegs1[-1][1],timeSegs2[-1][1])
	while upper-lower>0.00000001:
		i,j,mid,found = 0,0,(upper+lower)/2.0,False
		while i<len(lineSegs1) and j<len(lineSegs2):
			t10 = max(timeSegs1[i][0],timeSegs2[j][0]-mid)
			t11 = min(timeSegs1[i][1],timeSegs2[j][1]-mid)
			t20 = max(timeSegs1[i][0]+mid,timeSegs2[j][0])
			t21 = min(timeSegs1[i][1]+mid,timeSegs2[j][1])
			x1,y1 = lineSegs1[i][0]
			x2,y2 = lineSegs2[j][0]
			x10 = x1 + (lineSegs1[i][1][0]-x1)*(t10-timeSegs1[i][0])/(timeSegs1[i][1]-timeSegs1[i][0])
			x11 = x1 + (lineSegs1[i][1][0]-x1)*(t11-timeSegs1[i][0])/(timeSegs1[i][1]-timeSegs1[i][0])
			y10 = y1 + (lineSegs1[i][1][1]-y1)*(t10-timeSegs1[i][0])/(timeSegs1[i][1]-timeSegs1[i][0])
			y11 = y1 + (lineSegs1[i][1][1]-y1)*(t11-timeSegs1[i][0])/(timeSegs1[i][1]-timeSegs1[i][0])
			x20 = x2 + (lineSegs2[j][1][0]-x2)*(t20-timeSegs2[j][0])/(timeSegs2[j][1]-timeSegs2[j][0])
			x21 = x2 + (lineSegs2[j][1][0]-x2)*(t21-timeSegs2[j][0])/(timeSegs2[j][1]-timeSegs2[j][0])
			y20 = y2 + (lineSegs2[j][1][1]-y2)*(t20-timeSegs2[j][0])/(timeSegs2[j][1]-timeSegs2[j][0])
			y21 = y2 + (lineSegs2[j][1][1]-y2)*(t21-timeSegs2[j][0])/(timeSegs2[j][1]-timeSegs2[j][0])
			if minDist(x10,y10,x11,y11,x20,y20,x21,y21)<mid:
				found = True
				break
			if timeSegs1[i][1]+mid>timeSegs2[j][0]:
				j += 1
			elif timeSegs1[i][1]+mid<timeSegs2[j][0]:
				i += 1
			else:
				i,j = i+1,j+1
		if found:
			upper = mid
		else:
			lower = mid
	return upper

def normalize(coords):
	timeSegs,lineSegs,curStart = [],[],0.0
	for i in xrange(1,len(coords)):
		d = sqrt((coords[i][0]-coords[i-1][0])*(coords[i][0]-coords[i-1][0])+(coords[i][1]-coords[i-1][1])*(coords[i][1]-coords[i-1][1]))
		lineSegs.append((coords[i-1],coords[i]))
		timeSegs.append((curStart,curStart+d))
		curStart += d
	return lineSegs,timeSegs

n = int(raw_input())
coords = []
for i in xrange(n):
	x,y = map(float,raw_input().split())
	coords.append((x,y))
lineSegs1,timeSegs1 = normalize(coords)

n = int(raw_input())
coords = []
for i in xrange(n):
	x,y = map(float,raw_input().split())
	coords.append((x,y))
lineSegs2,timeSegs2 = normalize(coords)

time = searchTime(lineSegs1,timeSegs1,lineSegs2,timeSegs2)

print time



