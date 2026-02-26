
'''
card2point = {'A': 1,'2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '10': 10, 'J': 0.5, 'Q': 0.5, 'K': 0.5}

def getCard(playersPoint, player):
    while playersPoint[player] < 10.5:
        In = input().split()
        if In[0] == 'Y':
            playersPoint[player] += card2point[In[1]]
           #print(playersPoint)
        else:    break
    if playersPoint[player] == 10.5:
        playersPoint[player] = 0
    elif playersPoint[player] > 10.5:
        playersPoint[player] = -1

def countMoney(cpuPoint, playerPoint, money):
    print(playerPoint)
    print(cpuPoint)
    cpuMoney = 0
    for i, point in enumerate(playerPoint):
        if point == cpuPoint:
            cpuMoney += money[i]
            money[i] = -money[i]
        elif cpuPoint == 0:
            cpuMoney += money[i]
            money[i] = -money[i]
        elif point == 0:
            cpuMoney -= money[i]
        elif cpuPoint > point:
            cpuMoney += money[i]
            money[i] = -money[i]
        else:    cpuMoney -= money[i]
    return cpuMoney
    
def printMoney(money, cpuMoney):
    for i,m in enumerate(money):
        print('Player{0} {1}{2}'.format(i + 1, '+' if m > 0 else '', m))
    print('Computer {0}{1}'.format('+' if cpuMoney > 0 else '', cpuMoney))

def Min(nums):
    m = 11
    for i in nums:
        if i < m and i > 0:
            m = i
    if m == 11:    return 0.1
    return m
    
n = int(input())
money = [int(i) for i in input().split()]
cards = input().split()
cpuPoint = card2point[cards[0]]
playersPoint = []
for i in range(1, n + 1):    playersPoint.append(card2point[cards[i]])

for i in range(n):
    getCard(playersPoint, i)
    #print('-------------------------------------------------------')

canCpuGetCard = False
if Min(playersPoint) >= cpuPoint or Min(playersPoint) == 0:
    canCpuGetCard = True 
        
while canCpuGetCard:
    cpuPoint += card2point[input()]
    if cpuPoint == 10.5:
        cpuPoint = 0
        break
    elif cpuPoint > 10.5:
        cpuPoint = -1
        break
    canCpuGetCard = False
    if Min(playersPoint) >= cpuPoint or Min(playersPoint) == 0:
        canCpuGetCard = True


cpuMoney = countMoney(cpuPoint, playersPoint, money)
#print(playersPoint)
#print(cpuPoint)
printMoney(money, cpuMoney)
'''
card2point = {'A': 1,'2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '10': 10, 'J': 0.5, 'Q': 0.5, 'K': 0.5}

def getCard(playersPoint, player):
    while playersPoint[player] < 10.5:
        In = input().split()
        if In[0] == 'Y':
            playersPoint[player] += card2point[In[1]]
        else:
            break
    if playersPoint[player] == 10.5:
        playersPoint[player] = 0  # 玩家10.5，電腦立賠
    elif playersPoint[player] > 10.5:
        playersPoint[player] = -1  # 玩家爆掉

def Min(nums):
    m = 11
    for i in nums:
        if i < m and i > 0:
            m = i
    if m == 11:
        return 0.1
    return m

def countMoney(cpuPoint, playerPoint, money):
    cpuMoney = 0
    for i, point in enumerate(playerPoint):
        if point == -1:  # 玩家爆掉 → 玩家立賠
            cpuMoney += money[i]
            money[i] = -money[i]
        elif point == 0:  # 玩家10.5 → 電腦立賠
            cpuMoney -= money[i]
        elif cpuPoint == 0:  # 電腦10.5 → 玩家立賠
            cpuMoney += money[i]
            money[i] = -money[i]
        elif cpuPoint == -1:  # 電腦爆掉 → 電腦立賠
            cpuMoney -= money[i]
        elif cpuPoint >= point:  # 一般比大小（莊家勝含平手）
            cpuMoney += money[i]
            money[i] = -money[i]
        else:  # 玩家勝
            cpuMoney -= money[i]
    return cpuMoney

def printMoney(money, cpuMoney):
    for i,m in enumerate(money):
        print(f'Player{i+1} {"+" if m > 0 else ""}{m}')
    print(f'Computer {"+" if cpuMoney > 0 else ""}{cpuMoney}')

# 主程式
n = int(input())
money = [int(i) for i in input().split()]
cards = input().split()

cpuPoint = card2point[cards[0]]
playersPoint = [card2point[cards[i]] for i in range(1, n + 1)]

# 玩家要牌階段
for i in range(n):
    getCard(playersPoint, i)

# 判斷莊家是否要牌
while True:
    if Min(playersPoint) >= cpuPoint or Min(playersPoint) == 0:
        cpuPoint += card2point[input()]
        if cpuPoint == 10.5:
            cpuPoint = 0
            break
        elif cpuPoint > 10.5:
            cpuPoint = -1
            break
    else:
        break

cpuMoney = countMoney(cpuPoint, playersPoint, money)
printMoney(money, cpuMoney)
