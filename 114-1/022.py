def getRoration(LRString : str):
    rotation = 0
    for ch in LRString:
        if ch == 'R':
            rotation += 1
        else:
            rotation -= 1
        if rotation == -2:
            rotation = -rotation
        elif rotation == 3:
            rotation = -1 
    return rotation

def r1(i, n):
    x = (i - 1) // n
    y = (i - 1) % n
    return (n - y - 1) * n + x + 1

def r2(i, n):
    x = (i - 1) // n
    y = (i - 1) % n
    return (n - x - 1)* n + (n - y)

def l1(i, n):
    x = (i - 1) // n
    y = (i - 1) % n
    return y * n + (n - x)

def printMatrix(n, rotation):
    for i in range(1, n*n + 1):
        if rotation == 0:
            print(i, end = ' ')
        elif rotation == 1:
            print(r1(i, n), end = ' ')
        elif rotation == 2:
            print(r2(i, n), end = ' ')
        else:
            print(l1(i, n), end = ' ')
            
        if i % n == 0:
            print()
            
n = int(input())
rotation = getRoration(input())
printMatrix(n, rotation)

'''
common
1 2 3
4 5 6
7 8 9
r1
7 4 1
8 5 2
9 6 3
r2
9 8 7
6 5 4
3 2 1
l1
3 6 9
2 5 8
1 4 7
'''