import sys

sys.setrecursionlimit(3000)

class TreeNode:
	def __init__(self,val):
		self.val = val
		self.left = None
		self.right = None
	def preOrder(self,arr):
		arr.append(self.val)
		if self.left:
			self.left.preOrder(arr)
		if self.right:
			self.right.preOrder(arr)
	def postOrder(self,arr):
		if self.left:
			self.left.postOrder(arr)
		if self.right:
			self.right.postOrder(arr)
		arr.append(self.val)

fin = open("ethan_traverses_a_tree.txt",'r')
fout = open("B.out",'w')

tt = int(fin.readline())

for t in xrange(1,tt+1):
	n,k = map(int,fin.readline().split())
	nodes = [TreeNode(i) for i in xrange(1,n+1)]
	for i in xrange(n):
		left,right = map(int,fin.readline().split())
		if left>0:
			nodes[i].left = nodes[left-1]
		if right>0:
			nodes[i].right = nodes[right-1]
	preorder,postorder = [],[]
	nodes[0].preOrder(preorder)
	nodes[0].postOrder(postorder)
	graph = {i:{} for i in xrange(1,n+1)}
	for i in xrange(n):
		if preorder[i]!=postorder[i]:
			graph[preorder[i]][postorder[i]] = True
			graph[postorder[i]][preorder[i]] = True
	groupOf,curGroup = {},0
	for i in xrange(1,n+1):
		if i not in groupOf:
			curGroup += 1
			stack,groupOf[i] = [i],curGroup
			while len(stack)>0:
				cur = stack.pop()
				for neigh in graph[cur]:
					if neigh not in groupOf:
						groupOf[neigh] = curGroup
						stack.append(neigh)
	if curGroup<k:
		fout.write("Case #{0}: Impossible\n".format(t))
	else:
		fout.write("Case #{0}: ".format(t))
		for i in xrange(1,n+1):
			groupOf[i] = min(groupOf[i],k)
		labels = [str(groupOf[i]) for i in xrange(1,n+1)]
		ans = " ".join(labels)
		fout.write(ans)
		fout.write("\n")
