words = {}

while True:
	try:
		s = raw_input()
	except:
		break
	l = s.split()
	res = []
	for word in l:
		if word.lower() in words:
			res.append('.')
		else:
			res.append(word)
		words[word.lower()] = True
	print " ".join(res)