import math

def isOk(s):
    for c in s:
        if c not in 'ATCG':
            return False
    return True

def isPrime(n):
    if n < 2:
        return False
    elif n == 2:
        return True
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True

def isConform(S, subStr):
    for i, ch in enumerate(S):
        if ch == '?':
            continue
        elif ch != subStr[i]:
            return False
    return True

def getLeadIndexs(L, S):
    indexs = []
    S_len = len(S)

    for i in range(len(L) - S_len + 1):
        subStr = L[i: i + S_len]
        if isConform(S, subStr):
            indexs.append(i + S_len)
    return indexs

def getLastIndexs(L, Ei):
    indexs = []
    for item in Ei:
        item_len = len(item)
        for i in range(len(L) - item_len + 1):
            if item == L[i: i + item_len]:
                indexs.append(i)
    return indexs

def main():
    S = input()
    Ei = input().split()
    L = input()

    leadIndexs, lastIndexs = getLeadIndexs(L, S), getLastIndexs(L, Ei)
    tmp, ans = set(), []
    for leadindex in leadIndexs:
        for lastIndex in lastIndexs:
            tmp.add(L[leadindex:lastIndex])
    for s in tmp:
        if isPrime(len(s)) and isOk(s):
            ans.append(s)

    if len(ans) == 0:
        print('No gene')
    else:
        ans.sort(key = lambda a: (len(a), a))
        for item in ans:
            print(item)

main()