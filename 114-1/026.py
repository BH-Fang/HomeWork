def p(num, ch):
    for i in range(num):
        print(ch, end='')

def pn(start, end, step):
    for i in range(start, end, step):
        print(i, end = '')

def printFish(n, isOdd):
    if isOdd:
        for i in range(n):
            p(n - i - 1, '_')
            p(2 * i + 1, '*')
            p(2 * (n - i -1), '_')
            p(i + 1, '*')
            print()
        for i in range(n - 2, -1, -1):
            p(n - i - 1, '_')
            p(2 * i + 1, '*')
            p(2 * (n - i -1), '_')
            p(i + 1, '*')
            print()
    else:
        for i in range(n):
            p(i + 1, '*')
            p(2 * (n - i - 1), '_')
            p(2 * i + 1, '*')
            p(n - i - 1, '_')
            print()
        for i in range(n - 2, -1, -1):
            p(i + 1, '*')
            p(2 * (n - i - 1), '_')
            p(2 * i + 1, '*')
            p(n - i - 1, '_')
            print()

def printTri(n, isOdd):
    if isOdd:
        for i in range(n):
            p(n - i - 1, '_')
            pn(i + 1, 0, -1)
            pn(2, i + 2, 1)
            p(n - i - 1, '_')
            print()
    else:
        for i in range(n - 1, -1, -1):
            p(n - i - 1, '_')
            pn(i + 1, 0, -1)
            pn(2, i + 2, 1)
            p(n - i - 1, '_')
            print()

n, m, c = int(input()), int(input()), int(input())
isOdd = True if m % 2 != 0 else False
if c == 1:
    printFish(n, isOdd)
elif c == 2:
    printTri(n, isOdd)