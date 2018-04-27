from math import sqrt,pi,sin,cos

#fin = open("D.txt",'r')
#fout = open("D.out",'w')

tt = int(raw_input())

_mid = sqrt(2.0)

_max = sqrt(3.0)

def findRad(lower,upper,target,func):
	if upper-lower<0.00000001:
		return upper
	mid = (upper+lower)/2.0
	if func(mid-0.000001)>func(mid) or target<=func(mid):
		return findRad(lower,mid,target,func)
	else:
		return findRad(mid,upper,target,func)

for t in xrange(1,tt+1):
	area = float(raw_input())
	print "Case #{0}:".format(t)
	if area<_mid-0.000001:
		rad = findRad(0.0,pi/4.0,area,lambda r:cos(r)+sin(r))
		print "{0} {1} {2}".format(cos(rad)/2.0,sin(rad)/2.0,0)
		print "{0} {1} {2}".format(-sin(rad)/2.0,cos(rad)/2.0,0)
		print "0 0 0.5"
	elif abs(area-_mid)<0.000001:
		print "0.3535533905932738 0.3535533905932738 0"
		print "-0.3535533905932738 0.3535533905932738 0"
		print "0 0 0.5"
	elif abs(area-_max)<0.000001:
		print "0.3535533905932738 {0} {1}".format(0.5/_max,-0.5/sqrt(6))
		print "-0.3535533905932738 {0} {1}".format(0.5/_max,-0.5/sqrt(6))
		print "{0} {1} {2}".format(0,0.5/_max,0.5*_mid/_max)
	else:
		x = sqrt(2.0)/4.0
		rad = findRad(0.0,pi/4.0,area,lambda r:sqrt(2)*cos(r)+sin(r))
		print "{0} {1} {2}".format(x,x*cos(rad),-x*sin(rad))
		print "{0} {1} {2}".format(-x,x*cos(rad),-x*sin(rad))
		print "{0} {1} {2}".format(0,sin(rad)/2.0,cos(rad)/2.0)