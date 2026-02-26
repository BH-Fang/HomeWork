import math

def getSum(List):
    total = 0
    for i in List:
        total += math.ceil(i[0])
    return total
    
prizes = [380, 1200, 180]
In = [list(map(int, input().split(' '))), list(map(int, input().split(' '))), list(map(int, input().split(' ')))]
sum = 0
List = []
for i in range(len(In)):
    if i == 0:
        n = 'A'
    elif i == 1:
        n = 'B'
    else:
        n = 'C'

    if In[i][0] < 11:
        List += [(prizes[i] * In[i][0], n)]
    elif In[i][0] < 21:
        List += [(prizes[i] * In[i][0] * In[i][1] * 0.01, n)]
    elif In[i][0] < 31:
        List += [(prizes[i] * In[i][0] * In[i][2] * 0.01, n)]
    else:
        List += [(prizes[i] * In[i][0] * In[i][3] * 0.01, n)]

List.sort()
Out = '{0}: {1}\n{2}: {3}\n{4}'.format(List[2][1], math.ceil(List[2][0]), List[0][1], math.ceil(List[0][0]), getSum(List))

print(Out)