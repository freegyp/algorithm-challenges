#TLE on Python solution, accepted on C++ solution. But the idea is totally the same.

class Group:
	def __init__(self,_id,level=0,parent=None):
		self.id = _id
		self.level = level
		self.parent = parent
	def traceTop(self):
		cur = self
		while cur.parent:
			cur = cur.parent
		return cur
	def sameGroup(self,other):
		return self.traceTop()==other.traceTop()
	def join(self,other,maxId):
		if not self.sameGroup(other):
			left,right = self.traceTop(),other.traceTop()
			if left.level>right.level:
				right.parent = left
			elif left.level<right.level:
				left.parent = right
			else:
				newParent = Group(maxId,left.level+1,None)
				left.parent,right.parent = newParent,newParent
				maxId += 1
		return maxId


def mstLen(edges,n):
	groups,curId,res = [Group(i) for i in xrange(n)],n,0
	for d,left,right in edges:
		if not groups[left].sameGroup(groups[right]):
			curId = groups[left].join(groups[right],curId)
			res += d
	return res

tt = int(raw_input())
for t in xrange(tt):
	m,c = map(int,raw_input().split())
	edges = []
	for i in xrange(c*(c-1)/2):
		left,right,d = map(int,raw_input().split())
		edges.append((d,left,right))
	edges.sort()
	spill = mstLen(edges,c)+c
	if spill<=m:
		print "yes"
	else:
		print "no"