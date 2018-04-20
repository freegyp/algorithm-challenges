n = int(raw_input())

times = 0

for i in xrange(n):
	c = raw_input()
	times<<=1
	if c=="O":
		times += 1

print times