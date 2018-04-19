class Group:
	def __init__(self,_id,depth=0,total=1):
		self.id = _id
		self.parent = None
		self.depth = depth
		self.total = total
	def traceTop(self):
		cur = self
		while cur.parent:
			cur = cur.parent
		return cur
	def inSameGroup(self,other):
		left,right = self.traceTop(),other.traceTop()
		return left==right
	def join(self,other,maxId):
		if not self.inSameGroup(other):
			left,right = self.traceTop(),other.traceTop()
			if left.depth>right.depth:
				right.parent = left
				left.total += right.total
			elif right.depth>left.depth:
				left.parent = right
				right.total += left.total
			else:
				newParent = Group(maxId,left.depth+1,left.total+right.total)
				left.parent = newParent
				right.parent = newParent
				maxId += 1
		return maxId

tt = int(raw_input())

for t in xrange(tt):
	n = int(raw_input())
	name2group,curId = {},0
	for i in xrange(n):
		left,right = raw_input().split()
		if left not in name2group:
			name2group[left] = Group(curId)
			curId += 1
		if right not in name2group:
			name2group[right] = Group(curId)
			curId += 1
		name2group[left].join(name2group[right],curId)
		top = name2group[left].traceTop()
		print top.total


























