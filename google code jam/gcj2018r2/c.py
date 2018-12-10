#Not accepted yet...
tt = int(raw_input())

for t in xrange(1,tt+1):
    n = int(raw_input())
    val2ijs = {}
    for i in xrange(n):
        row = map(int,raw_input().split())
        for j in xrange(n):
            if row[j] not in val2ijs:
                val2ijs[row[j]] = []
            val2ijs[row[j]].append((i,j))
    ans = 0
    for i in xrange(-n,n+1):
        if i in val2ijs:
            total,rows,cols = 0,{},{}
            for x,y in val2ijs[i]:
                total += 1
                rows[x] = True
                cols[y] = True
            ans += total-min(len(rows),len(cols))
    print "Case #{0}: {1}".format(t,ans)