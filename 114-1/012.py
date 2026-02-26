def poker2Score(poker):
    Poker = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K']
    score = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0.5, 0.5, 0.5]
    return score[Poker.index(poker)]

xScore, yScore = 0, 0

for i in range(3):
    xScore += poker2Score(input())
for i in range(3):
    yScore += poker2Score(input())
if xScore > 10.5:
    xScore = 0
if yScore > 10.5:
    yScore = 0
winner = 'Tie'
if xScore > yScore:
    winner = 'X Win'
elif xScore < yScore:
    winner = 'Y Win'

if xScore / 1 == xScore //1:
    print('%d' %xScore)
else:
    print('%.1f' %xScore)
if yScore / 1 == yScore //1:
    print('%d' %yScore)
else:
    print('%.1f' %yScore)
print(winner)

