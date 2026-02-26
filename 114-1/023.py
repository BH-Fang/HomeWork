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
if correct:    
    correct = draw(p2, cpu, d2)
if correct:    
    correct = draw(cpu, p1, d3)

if correct:
    printCards(p1)
    printCards(p2)
    printCards(cpu)
else:
    print('Error')
