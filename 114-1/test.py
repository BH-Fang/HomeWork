'''
def forOps():
    i = 1
    myList = ['asm', 'C', 'python', 'C++', 'Java', 'iOS', 'Ruby', 'perl', 'delphi']
    for index in myList:
        if index == 'python':
            print(i, index)
        elif index == 'Java':
            print(i, index)
        elif i % 3 != 0:
            print(i, index)
            i = i + 1
        else:
            i = i + 1
forOps()
'''
'''
def f(N):
    N_clone = N.copy()
    Max = N_clone[0]
    for n in N_clone:
        if n > Max:
            Max = n
    while Max in N_clone:
        N_clone.remove(Max)
    if len(N_clone) != 0:
        Max = N_clone[0]
        for n in N_clone:
                if n > Max:
                    Max = n
    else:
        return 
    return Max

N = int(input())
In = input().split()
numbers = []
for i in range(N):
    numbers.append(In[i])
print(f(numbers))
'''
'''
def printOneRow(m, n, s, mark):
    i = m
    if (m==n): return
    while (i!=n):
        if (mark=='0'): print("%d" %i, end='')
        else: print("%c" %mark, end='')
        i = i + s
        
def myPrint(n):
    for i in range(n):
        printOneRow(i, 0, -1 , '#')
        printOneRow(2*(n-i-1), -2, -2 , '0')
        printOneRow(2, 2*(n-i), 2 , '0')
        printOneRow(i, 0, -1 , '#')
        print()
myPrint(2)
'''
'''
def myPrint(row, n):
    for i in range(row):
        print('#', end='')
    for i in range(2 * (n - row - 1), 0, -2):
        print(i, end='')
    for i in range(0, 2 * (n - row - 1) + 1, 2):
        print(i, end='')
    print()
def printTri(n):
    for row in range(n):
        myPrint(row, n)
        
printTri(int(input()))
'''
'''
def t(i, n):
    return (n - i // n - 1) * n + i % n
    
def printSquare(n):
    for i in range(0, n * n):
        print('%3d'%t(i, n), end = '')
        if i % n == n - 1:
            print()
            
printSquare(int(input()))  
'''
'''
def t(i, n):
    x = i % n
    y = i // n
    return (n - x - 1) * n + y

def printSquare(n):
    for i in range(0, n * n):
        print('%3d'%t(i, n), end = '')
        if i % n == n - 1:
            print()

printSquare(int(input()))  
'''
            
'''
def printSquare(n):
    x = y = 0
    for i in range(n * n):
        x = i % n
        print('(%2d,%2d)' %(y, x), end='')
        if i % n == n - 1:
            y += 1
            print()

printSq
uare(int(input()))
'''

'''
def organizeHands(cardList):
    nums = [card[1:] for card in cardList]
    count = dict()
    for num in nums:
        count[num] = count.get(num, 0) + 1
    return [card for card in cardList if count[card[1:]] == 1]    

def printCards(cardList):
    for card in cardList:
        print(card, end=' ')
    print()        
def draw(c1, c2, card):
    if card in c2:
        c1.append(c2.pop(c2.index(card)))
        c1[:] = organizeHands(c1)
    else:
        return False
    return True

p1 = organizeHands(input().split())
p2 = organizeHands(input().split())
cpu = organizeHands(input().split())

d1, d2, d3 = input(), input(), input()

correct = draw(p1, p2, d1)
if correct:    correct = draw(p2, cpu, d2)
if correct:    correct = draw(cpu, p1, d3)

if correct:
    printCards(p1)
    printCards(p2)
    printCards(cpu)
else:
    print('error')
'''

'''

def func(x, y):
    l = []
    i = 2
    while(True):
        if x % i == 0 and y % i == 0:
            l.append(i)
            x /= i
            y /= i
        else:
            i += 1
            if i > min(x, y):
                break
    o = 1
    for n in l:
        o *= n
    return o

def noOfDigits(n):
    if n == 1:
        return 1
    else: return noOfDigits(n // 10) + 1
    
def digitSum(n):
    if n == 1:
        return 1
    else: return noOfDigits(n // 10) + n % 10
    
print(noOfDigits(123465))

'''

'''
def GCD(a, b):
    if a < b: a, b = b, a
    while True:
        r = a % b
        if not r:
            return b
        else: a, b = b, r

print(GCD(60, 36))
'''

'''
def digitSum(n):
    if n == 0:
        return 0
    else:
        return n % 10 + digitSum(n // 10)

print(digitSum(456))
'''

'''
def sum(l: list):
    if len(l) == 0:
        return 0
    else:
        return l[0] + sum(l[1:])
    
def factorial(n):
    if n == 1:
        return 1
    else:
        return factorial(n - 1) * n

def Fibonacci(n, d = dict()):
    if n in d:
        return d[n]
    if n == 0 or n == 1:
        return n
    else:
        result = Fibonacci(n - 1, d) + Fibonacci(n - 2, d)
        d[n] = result
        return result
    
print(Fibonacci(500))
'''

'''
def quickSort(l):
    Len = len(l)
    if Len == 1 or Len == 0:
        return l
    else:
        pivot = l[0]
        i, j = 1, Len - 1
        while True:
            while j > -1 and l[j] > pivot:
                j -= 1
            while i < Len and l[i] < pivot:
                i += 1
            if i >= j:
                break
            else:
                l[i], l[j] = l[j], l[i]
        l[0], l[j] = l[j], l[0]
        return quickSort(l[:j]) + l[j:j+1] + quickSort(l[j + 1:])
'''
'''
def quickSort(l, low, high):
    if high <= low:
        return
    else:
        pivot = l[low]
        i = low + 1
        j = high
        while True:
            while i <= high and l[i] < pivot:
                i += 1
            while j > low and l[j] > pivot:
                j -= 1
            if j > i:
                l[i], l[j] = l[j], l[i]  
            else:
                break   
        l[low], l[j] = l[j], l[low] 
        quickSort(l, low, j - 1)
        quickSort(l, j + 1, high)                     

        
        
l = [3, 6, 5, 1, 2, 9, 4, 7, 8]
quickSort(l, 0, 8)
print(l)
'''
'''

a=["apple", "banana", "cherry"]
b=["apple", "banana", "watermelon"]

def difference_update(a, b):
    for item in b:
        if not item in a:
            a.append(item)

def difference(a, b):
    result = a.copy()
    for item in b:
        if not item in a:
            result.append(item)
    return result

print(difference(a, b))
'''

dict = {'a':15, 'b':10, 'c':3, 'd':15}
print(max(dict, key = dict.get))