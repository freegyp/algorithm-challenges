class Waiter:
	def __init__(self):
		self.table1 = 0
		self.table2 = 0
	def clear(self):
		self.table1 = 0
		self.table2 = 0
		print ""
	def drop(self,amount):
		self.table2 += amount
		print "DROP 2 {0}".format(amount)
	def take(self,amount):
		while amount>0:
			if self.table1==0:
				self.table1 += self.table2
				self.table2 = 0
				print "MOVE 2->1 {0}".format(self.table1)
			red = min(self.table1,amount)
			self.table1 -= red
			amount -= red
			print "TAKE 1 {0}".format(red)

waiter = Waiter()
while True:
	n = int(raw_input())
	if n==0:
		break
	for i in xrange(n):
		left,right = raw_input().split()
		if left=="DROP":
			waiter.drop(int(right))
		else:
			waiter.take(int(right))
	waiter.clear()