while True:
	n = int(raw_input())
	if n==0:
		break
	hashes,trie,ans,ansHash = {},{'_count':0},0,0
	for i in xrange(n):
		s = raw_input()
		curTrie,curHash = trie,0
		for c in s:
			if c not in curTrie:
				curTrie[c] = {'_count':0}
			curTrie = curTrie[c]
			curHash ^= ord(c)
		if curHash not in hashes:
			hashes[curHash] = 0
		ansHash += hashes[curHash]-curTrie['_count']
		hashes[curHash] += 1
		if curTrie['_count']==0:
			ans += 1
		curTrie['_count'] += 1
	print "{0} {1}".format(ans,ansHash)