
def removeCount(s):
    leftRemoveCount = 0
    rightRemoveCount = 0
    for ch in s:
        if ch == '(':
            leftRemoveCount += 1
        elif ch == ')':
            if leftRemoveCount > 0:
                leftRemoveCount -= 1
            else:
                rightRemoveCount += 1
    return leftRemoveCount, rightRemoveCount

def main():
    s = input()  
    
    leftRemoveCount, rightRemoveCount = removeCount(s)
    totalRemove = leftRemoveCount + rightRemoveCount
    mySet = set()
    
    def dfs(index, leftRemoveCount, rightRemoveCount, current):
        if index == len(s):
            current_leftRemoveCount, current_rightRemoveCount = removeCount(current)
            if leftRemoveCount + rightRemoveCount == 0 and current_leftRemoveCount + current_rightRemoveCount == 0:
                mySet.add(current)
                return
            else:
                return
        dfs(index + 1, leftRemoveCount, rightRemoveCount, current + s[index])
        if s[index] == '(' and leftRemoveCount > 0:
            dfs(index + 1, leftRemoveCount - 1, rightRemoveCount, current)
        elif s[index] == ')' and rightRemoveCount > 0:
            dfs(index + 1, leftRemoveCount, rightRemoveCount - 1, current)
    
    dfs(0, leftRemoveCount, rightRemoveCount, '')
    result = ' '.join(sorted(list(mySet)))
    
    print(totalRemove)
    print(result)

main()