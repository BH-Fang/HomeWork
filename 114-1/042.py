def getShortestPath(min_node, parentX, parentZ, X, Z):
    current = min_node
    pa = []
    pa.append(current)
    while current != X:
        current = parentX[current]
        pa.append(current)
    pa.reverse()
    th = []
    current = min_node
    while current != Z:  
        current = parentZ[current]
        th.append(current)
    return pa + th


def getShortestNode(Ki, distX, distZ):
    m = 9999999999
    min_node = -1
    Ki.sort()
    for node in Ki:
        if node not in distX or node not in distZ: 
            continue
        distSum = distX[node] + distZ[node]
        if distSum < m:
            m = distSum
            min_node = node
    return min_node

def getDist(start, road, parents):
    queue = []
    dist = dict()
    dist[start] = 0
    queue.append(start)
    while len(queue) != 0:
        current = queue.pop(0)
        if current not in road:
            continue
        for node in road[current]:
            if not node in dist:
                queue.append(node)
                parents[node] = current
                dist[node] = dist[current] + 1
    return dist

def main():
    input0 = [int(a) for a in input().split()]
    N, X, Z = input0[0], input0[1], input0[2]
    Ki = [int(a) for a in input().split()]
    roads = dict()
    for _ in range(N):
        inputn = [int(a) for a in input().split()]
        roads[inputn[0]] = roads.get(inputn[0], []) + [inputn[1]]
        roads[inputn[1]] = roads.get(inputn[1], []) + [inputn[0]]

    parentX = dict()
    parentZ = dict()
    distX = getDist(X, roads, parentX)
    distZ = getDist(Z, roads, parentZ)
    shortestNode = getShortestNode(Ki, distX, distZ)
    if shortestNode != -1: path = getShortestPath(shortestNode, parentX, parentZ, X, Z)

    if shortestNode != -1:
        print(shortestNode)
        for node in path:
            print(node, end = ' ')
    else:
        print('NO')


main()