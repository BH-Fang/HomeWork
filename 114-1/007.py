import math
a, b, c = int(input()), int(input()), int(input())

if a < 1 or b < 1 or c < 1 or a + b <= c or a + c <= b or b + c <= a:
    print('Not Triangle')
else:
    if a == b == c:
        print('Equilateral Triangle')
    elif max(a, b, c) == b:
        a, b = b, a
    elif max(a, b, c) == c:
        a, c = c, a
    if b == c:
        print('Isosceles Triangle')
    t = math.sqrt(b ** 2 + c ** 2)
    if a > t:
        print('Obtuse Triangle')
    elif a < t:
        print('Acute Triangle')
    else:
        print('Right Triangle')
    
