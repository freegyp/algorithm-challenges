w,h = map(int,raw_input().split())

grids = []

px,py = -1,-1

for i in xrange(h):
	line = raw_input()
	for j in xrange(w):
		if line[j]=='P':
			px,py = i,j
	grids.append(line)

stack,checked,ans = [(px,py)],{(px,py):True},0


while len(stack)>0:
	x,y = stack.pop()
	if grids[x][y]=='G':
		ans += 1
	ok = True
	for i,j in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
		if i>=0 and i<h and j>=0 and j<w and grids[i][j]=='T':
			ok = False
			break
	if ok:
		for i,j in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
			if i>=0 and i<h and j>=0 and j<w and grids[i][j]!='#' and (i,j) not in checked:
				checked[(i,j)] = True
				stack.append((i,j))

print ans