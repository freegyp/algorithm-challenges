class BIT:
	def __init__(self,bound):
		self.tree = {}
		self.bound = bound
		self.total = 0
	def addOneAt(self,i):
		self.total += 1
		while i<=self.bound:
			if i not in self.tree:
				self.tree[i] = 0
			self.tree[i] += 1
			i += i&-i
	def sumB4(self,i):
		res = 0
		while i>0:
			if i in self.tree:
				res += self.tree[i]
			i -= i&-i
		return res
	def clear(self):
		self.tree = {}
		self.total = 0
n = int(raw_input())

tree = BIT(n)

nums = map(int,raw_input().split())

greater,revSmaller = [],[]

for num in nums:
	greater.append(tree.total-tree.sumB4(num))
	tree.addOneAt(num)

tree.clear()

for num in nums[::-1]:
	revSmaller.append(tree.sumB4(num-1))
	tree.addOneAt(num)

revSmaller = revSmaller[::-1]

ans = 0

for i in xrange(n):
	ans += greater[i]*revSmaller[i]

print ans