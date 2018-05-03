class BIT:
	def __init__(self,bound):
		self.tree = {}
		self.set = {}
		self.bound = bound
	def flip(self,idx):
		if idx not in self.set:
			self.set[idx] = True
			toAdd = 1
		else:
			del self.set[idx]
			toAdd = -1
		while idx<=self.bound:
			if idx not in self.tree:
				self.tree[idx] = 0
			self.tree[idx] += toAdd
			idx += idx&-idx
	def sumB4(self,idx):
		res = 0
		while idx>0:
			if idx in self.tree:
				res += self.tree[idx]
			idx -= idx&-idx
		return res
	def rangeSum(self,left,right):
		return self.sumB4(right)-self.sumB4(left-1)

n,k = map(int,raw_input().split())
tree = BIT(n)

for i in xrange(k):
	line = raw_input().split()
	if len(line)==2:
		tree.flip(int(line[1]))
	else:
		print tree.rangeSum(int(line[1]),int(line[2]))