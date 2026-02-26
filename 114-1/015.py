score = 0
p = 0
i1 = int(input())
if i1 != 10:
    score += i1
    i2 = int(input())
    score += i2
    if i1 + i2 == 10:
        p += 1
else:
    score += i1
    p += 2

i1 = int(input())
if i1 != 10:
    score += i1
    if p != 0:
        score += i1
        p -= 1
    i2 = int(input())
    score += i2
    if p != 0:
        score += i2
        p -= 1
    if i1 + i2 == 10:
        p += 1
else:
    score += i1
    if p != 0:
        score += i1
        p -= 1
    p += 2

i1 = int(input())
if i1 != 10:
    score += i1
    if p == 3:
        score += 2 * i1
        p -= 2
    elif p != 0:
        score += i1
        p -= 1
    i2 = int(input())
    score += i2
    if p != 0:
        score += i2
        p -= 1
    if i1 + i2 == 10:
        score += int(input())
else:
    score += i1
    if p == 3:
        score += 2 * i1
        p -= 2
    elif p != 0:
        score += i1
        p -= 1
    if p != 0:
        score += 2 * int(input()) 
    else:
        score += int(input())
    score += int(input())

print(score)