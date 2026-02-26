def printRightTriangle(N):
    for i in range(N):
        for j in range(1, i + 2):
            print(j, end = '')
        for j in range(i, 0, -1):
            print(j, end = '')
        print('')

def prinTequilateralTriangle(N):
    for i in range(N):
        for j in range(N - i - 1):
            print('_', end = '')
        for j in range(1, i + 2):
            print(j, end = '')
        for j in range(i, 0, -1):
            print(j, end = '')
        for j in range(N - i - 1):
            print('_', end = '')
        print()

def printInverseTriangle(N):
    for i in range(N):
        for j in range(i):
            print('_', end = '')
        for j in range(1, N - i + 1):
            print(j, end = '')
        for j in range(N - i - 1, 0, -1):
            print(j, end = '')
        for j in range(i):
            print('_', end = '')
        print()

M = int(input())
N = int(input())
if 3 <= N <= 50:
    if M == 1:
        printRightTriangle(N)
    elif M == 2:
        prinTequilateralTriangle(N)
    elif M == 3:
        printInverseTriangle(N)
    else:
        print('M Error')
else:
    print('Row Error')