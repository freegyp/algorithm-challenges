n,m,ds,cs,da,ca = map(int,raw_input().split())

monsters = map(int,raw_input().split())

monsters.sort()

lower,upper = 0,n+1

while upper-lower>1:
	mid = (upper+lower)/2
	maximum,ice,iceCost,minCost = monsters[mid-1],0,0,None
	while ice<maximum+da:
		strikeCost = 0
		for i in xrange(mid):
			if monsters[i]>ice:
				strikeCost += ((monsters[i]-ice)/ds+int((monsters[i]-ice)%ds>0))*cs
		if minCost==None:
			minCost = iceCost + strikeCost
		else:
			minCost = min(minCost,iceCost+strikeCost)
		ice,iceCost = ice+da,iceCost+ca
	if minCost<=m:
		lower = mid
	else:
		upper = mid

print lower