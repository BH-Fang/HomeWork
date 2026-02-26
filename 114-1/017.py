def totalPoints_calc(HCP, numsOfPattern):
    totalPoint = HCP
    if 5 in numsOfPattern:
        totalPoint += 2
    return totalPoint

def HCP_calc(cardsPoints):
    total = 0
    for cardPoint in cardPoints:
        if cardPoint == 'A':
            total += 4
        elif cardPoint == 'K':
            total += 3
        elif cardPoint == 'Q':
            total += 2
        elif cardPoint == 'J':
            total += 1
    return total

def patternsCount(patterns):
    patternIndex = ['S', 'H', 'D', 'C']
    count = [0, 0, 0, 0] #[S, H, D, C]
    for pattern in patterns:
        count[patternIndex.index(pattern)] += 1
    return count

def stoppedSuits_find(patterns, cardPoints, numsOfPattern):
    dirc = {'S': 0, 'H': 1, 'D': 2, 'C': 3}
    stopSuits = []
    for index, item in enumerate(cardPoints):
        pattern = patterns[index]
        isStoppedSuit = False
        if item == 'A':
            isStoppedSuit = True
        elif item == 'K' and numsOfPattern[dirc[pattern]] > 1:
            isStoppedSuit = True
        elif item == 'Q' and numsOfPattern[dirc[pattern]] > 2:
            isStoppedSuit = True
        if isStoppedSuit and not pattern in stopSuits:
            stopSuits.append(pattern)
    stopSuits = sorted(stopSuits, key= lambda a:dirc[a])
    return stopSuits
        
def get_suggestion(totalPoints, numsOfPattern):
    if totalPoints < 8:
        return 'Pass'
    elif totalPoints >= 15:
        return 'Strong Open'
    else:
        indexOfLongest = numsOfPattern.index(max(numsOfPattern))
        pattern = 'Club'
        if indexOfLongest == 0:
            pattern = 'Spade'
        elif indexOfLongest == 1:
            pattern = 'Heart'
        elif indexOfLongest == 2:
            pattern = 'Diamond'
        return 'Open {}'.format(pattern)    
    
patterns = input().split()
cardPoints = input().split()
HCP = HCP_calc(cardPoints)
numsOfPattern = patternsCount(patterns)
totalPoints = totalPoints_calc(HCP, numsOfPattern)
stoppedSuits = stoppedSuits_find(patterns, cardPoints, numsOfPattern)

print('HCP: {0}\nTotal Points: {1}\nDistribution (S-H-D-C): {2}-{3}-{4}-{5}\nStopped Suits: {6}\nOpening Bid: {7}'.format(HCP, totalPoints, numsOfPattern[0], numsOfPattern[1], numsOfPattern[2], numsOfPattern[3], stoppedSuits, get_suggestion(totalPoints, numsOfPattern)))