def isolationTags(graph):
    tags,curId = {},0
    for node in graph:
        if node not in tags:
            stack,tags[node] = [node],curId
            while len(stack)>0:
                cur = stack.pop()
                for neigh in graph[cur]:
                    if neigh not in tags:
                        stack.append(neigh)
                        tags[neigh] = curId
            curId += 1
    return tags,curId

def safeInsert(graph,left,right):
    if left not in graph:
        graph[left] = {}
    graph[left][right] = True
    if right not in graph:
        graph[right] = {}
    graph[right][left] = True

n,m,k = map(int,raw_input().split())

graph,redList = {},[]

for i in xrange(m):
    c,left,right = raw_input().split()
    left,right = int(left),int(right)
    if c=='B':
        safeInsert(graph,left,right)
    else:
        redList.append((left,right))

tags,groups = isolationTags(graph)

maxBlueTree = len(graph)-groups

if maxBlueTree<k or len(redList)+k<n-1:
    print 0
else:
    print 1