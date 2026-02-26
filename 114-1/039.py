
def main():
    caves = dict()
    inputLine1 = list(map(int, input().split()))
    N = int(inputLine1[0])
    start = int(inputLine1[1])
    M = int(input())
    for _ in range(N):
        inputLine = list(map(int, input().split()))
        caves[inputLine[0]] = (inputLine[1], inputLine[2], inputLine[3], inputLine[4])
    
    maxValue = -1
    def dfs(currentCave, currentValue, currentWeight, visited):
        nonlocal maxValue
        if currentCave == 0 or currentCave in visited:
            return
        caveData = caves[currentCave]
        currentWeight += caveData[1]
        if currentWeight > M:
            return
        visited.add(currentCave)
        currentValue += caveData[0]
        if currentValue > maxValue:
            maxValue = currentValue
        dfs(caveData[2], currentValue, currentWeight, visited) 
        dfs(caveData[3], currentValue, currentWeight, visited) 
        visited.remove(currentCave)
    dfs(start, 0, 0, set())

    print(maxValue)
   
main()