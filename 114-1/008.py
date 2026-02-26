total = [0, 0, 0]
rates = [
    [0.08, 0.07, 0.06],       
    [0.1393, 0.1304, 0.1087], 
    [0.1349, 0.1217, 0.1018], 
    [1.1287, 1.1127, 0.9572],
    [1.4803, 1.2458, 1.1243]  
]

In = [int(input()), int(input()), int(input()), int(input()), int(input())]

for i in range(len(total)):
    for j in range(len(In)):
        total[i] += In[j] * rates[j][i]
List = [183, 383, 983]
for i in range(len(total)):
    if total[i] < List[i]:
        total[i] = List[i]

ans = total.index(min(total[0], total[1], total[2]))

print('%d' %total[ans])
if ans == 0:
    print('183')
elif ans == 1:
    print('383')
else:
    print('983')