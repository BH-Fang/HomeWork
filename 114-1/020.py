
def In(N):
    passwords = []
    for i in range(N):
        passwords.append(input())
    return passwords
        
def getLowerPoint(password):
    point = 0
    for ch in password:
        if ch.islower():
            point += 1
    return point

def getUpperPoint(password):
    point = 0
    for ch in password:
        if ch.isupper():
            point += 1
    return point * 3

def getSpecialPoint(password):
    dirc = ' ~!@#$%^&*<>_+='
    point = 0
    for ch in password:
        if ch in dirc:
            point += 1
    return point * 4.5

def p10(indexOfNums, password):
    good = True
    if len(indexOfNums) < 5:
        good = False
    else:
        for i in indexOfNums:
            if (i + 1 < len(password) and password[i + 1].isdecimal()) or (i - 1 > -1 and password[i - 1].isdecimal()):
                good = False
                break
    return good
    
def getNumberPoint(password):
    indexOfNumbers = []
    for index, ch in enumerate(password):
        if ch.isdecimal():
            indexOfNumbers.append(index)
    point = len(indexOfNumbers) * 2
    if p10(indexOfNumbers, password):
        point += 10
    return point
    
def calcPoint(password):
    point = getLowerPoint(password) + getUpperPoint(password) + getNumberPoint(password) + getSpecialPoint(password)
    add = len(password) - 8
    if add > 0:
        point += add
    if '1234' in password:
        point -= 10
    return point

N = int(input())
passwords = In(N)
points = []
for password in passwords:
    points.append((calcPoint(password), password))
higest = max(points)
lowest = min(points)
print('{0} {1:.1f}'.format(higest[1], higest[0]))
print('{0} {1:.1f}'.format(lowest[1], lowest[0]))