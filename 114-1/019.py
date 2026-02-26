def In(N, ids, time):
    legalTime = ('11', '12', '13', '14', '15', '16', '17', '18', '19', '1a', '1b', '1c',
                 '21', '22', '23', '24', '25', '26', '27', '28', '29', '2a', '2b', '2c',
                 '31', '32', '33', '34', '35', '36', '37', '38', '39', '3a', '3b', '3c',
                 '41', '42', '43', '44', '45', '46', '47', '48', '49', '4a', '4b', '4c',
                 '51', '52', '53', '54', '55', '56', '57', '58', '59', '5a', '5b', '5c')
    try:
        for i in range(N):
            ids.append(input())
            H = int(input())
            timeT = []
            for j in range(H):
                t = input()
                if t in legalTime and not(t in timeT):
                    timeT.append(t)
                else:
                    return False
            time.append(timeT) 
        return True
    except:
        return False

def Conflict(ids, time, conflict):
    isCorrect = True
    for index, item in enumerate(time):
        for item1 in item:
            for index1 in range(index + 1, len(time)):
                for index2 in range(0, len(time[index1])):
                    if item1 == time[index1][index2]:
                        isCorrect = False
                        conflict.append((ids[index], ids[index1], item1))
                        
    return isCorrect

ids = []
time = []
conflict = []
N = int(input())
isInputCorrect = In(N, ids, time)
if not isInputCorrect:
    print(-1)
else:
    correct = Conflict(ids, time, conflict)
    if correct:
        print('correct')
    else:
        for c in conflict:
            print('{0},{1},{2}'.format(c[0], c[1], c[2]))
