s = raw_input()

cum = 0
for c in s:
	if c=='W':
		cum += 1
	elif c=='B':
		cum -= 1

if cum==0:
	print 1
else:
	print 0