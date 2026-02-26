'''def str2Int(strNum):
    if strNum == 'A':
        return 1
    elif strNum == 'J':
        return 11
    elif strNum == 'Q':
        return 12
    elif strNum == 'K':
        return 13
    else:
        return int(strNum)

def isInputCorrect(cards):
    allCards = {
                'AS', '2S', '3S', '4S', '5S', '6S', '7S', '8S', '9S', '10S', 'JS', 'QS', 'KS',
                'AH', '2H', '3H', '4H', '5H', '6H', '7H', '8H', '9H', '10H', 'JH', 'QH', 'KH',
                'AD', '2D', '3D', '4D', '5D', '6D', '7D', '8D', '9D', '10D', 'JD', 'QD', 'KD',
                'AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', '10C', 'JC', 'QC', 'KC'
               }
    for card in cards:
        if not card in allCards:
            return False
    return True

def isDuplicate(cards):
    s = set()
    for card in cards:
        if card in s:
            return True
        s.add(card)
    return False
        
def counter(a):
    count = dict()
    for i in a:
        count[i] = count.get(i, 0) + 1
    return count

def haveOnePair(numbers):
    if 2 in counter(numbers).items:
        return True
    else:
        return False

def haveTwoPair(numbers):
    c = counter(numbers)
    s = set()
    for nn in c.items:
        if nn in s:
            return True
        s.add(nn)
    return False

def haveThreeOfaKind(numbers):
    if 3 in counter(numbers).items:
        return True
    else:
        return False
    
def haveStraight(numbers):
    numbers = sorted(numbers)
    nowNum = numbers[0]
    for i in range(1, numbers):
        if numbers[i] != nowNum + 1:    
            return False
        if nowNum == 13:
            nowNum = 0
        else:
            nowNum = numbers[i]
    return True

def haveFlush(colors):
    if 5 in counter(colors).items:
        return True
    else:
        return False
    
def haveFullHouse(numbers):
    c = counter(numbers)
    if 2 in c and 3 in c:
        return True
    else:
        return False
    
def haveFourOfaKind(numbers):
    if 4 in counter(numbers).items:
        return True
    else:
        return False

def findCardType(cards, numbers, colors):
    cardType = 1
    if haveOnePair(numbers):      cardType = 2
    if haveTwoPair(numbers):      cardType = 3
    if haveThreeOfaKind(numbers): cardType = 4
    if haveStraight(numbers):     cardType = 5
    if haveFlush(colors):         cardType = 6
    if haveFullHouse(numbers):    cardType = 7
    if haveFourOfaKind(numbers):  cardType = 8
    if haveFlush(colors) and haveStraight(numbers): cardType = 9
    return cardType

def main(): 
    cards = input().split()
    if not isInputCorrect(cards):
        print('Error input')
        return
    if isDuplicate(cards):
        print('Duplicate deal')
        return
    numbers = [str2Int(card[0:-1]) for card in cards]
    colors = [card[1] for card in cards]
    print(findCardType(cards, numbers, colors))
    
main()'''
def str2Int(strNum):
    if strNum == 'A':
        return 1
    elif strNum == 'J':
        return 11
    elif strNum == 'Q':
        return 12
    elif strNum == 'K':
        return 13
    else:
        return int(strNum)

def isInputCorrect(cards):
    allCards = {
                'AS', '2S', '3S', '4S', '5S', '6S', '7S', '8S', '9S', '10S', 'JS', 'QS', 'KS',
                'AH', '2H', '3H', '4H', '5H', '6H', '7H', '8H', '9H', '10H', 'JH', 'QH', 'KH',
                'AD', '2D', '3D', '4D', '5D', '6D', '7D', '8D', '9D', '10D', 'JD', 'QD', 'KD',
                'AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', '10C', 'JC', 'QC', 'KC'
               }
    for card in cards:
        if not card in allCards:
            return False
    return True

def isDuplicate(cards):
    s = set()
    for card in cards:
        if card in s:
            return True
        s.add(card)
    return False
        
def counter(a):
    count = dict()
    for i in a:
        count[i] = count.get(i, 0) + 1
    return count

def haveOnePair(numbers):
    if 2 in counter(numbers).values():
        return True
    else:
        return False

def haveTwoPair(numbers):
    c = counter(numbers)
    s = set()
    for nn in c.values():
        if nn != 1 and nn in s:
            return True
        s.add(nn)
    return False

def haveThreeOfaKind(numbers):
    if 3 in counter(numbers).values():
        return True
    else:
        return False
    
def haveStraight(numbers):
    numbers = sorted(numbers)
    gap = []
    for i in range(len(numbers) - 1):
        gap.append(numbers[i + 1] - numbers[i])
    gap.sort()
    if gap == [1, 1, 1, 9] or gap == [1, 1, 1, 1]:
        return True
    else:
        return False

def haveFlush(colors):
    if 5 in counter(colors).values():
        return True
    else:
        return False
    
def haveFullHouse(numbers):
    c = counter(numbers)
    if 2 in c.values() and 3 in c.values():
        return True
    else:
        return False
    
def haveFourOfaKind(numbers):
    if 4 in counter(numbers).values():
        return True
    else:
        return False

def findCardType(cards, numbers, colors):
    cardType = 1
    if haveOnePair(numbers):      cardType = 2
    if haveTwoPair(numbers):      cardType = 3
    if haveThreeOfaKind(numbers): cardType = 4
    if haveStraight(numbers):     cardType = 5
    if haveFlush(colors):         cardType = 6
    if haveFullHouse(numbers):    cardType = 7
    if haveFourOfaKind(numbers):  cardType = 8
    if haveFlush(colors) and haveStraight(numbers): cardType = 9
    return cardType

def main(): 
    cards = input().split()
    if not isInputCorrect(cards):
        print('Error input')
        return
    if isDuplicate(cards):
        print('Duplicate deal')
        return
    numbers = [str2Int(card[0:-1]) for card in cards]
    colors = [card[-1] for card in cards]
    print(findCardType(cards, numbers, colors))
    
main()

