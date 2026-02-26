prizes = [380, 1200, 180]
discounts = [[0.9, 0.85, 0.8], [0.95, 0.85, 0.8], [0.85, 0.8, 0.7]]
In = [int(input()), int(input()), int(input())]
sum = 0
for i in range(len(In)):
    if In[i] < 11:
        sum += prizes[i] * In[i]
    elif In[i] < 21:
        sum += prizes[i] * In[i] * discounts[i][0]
    elif In[i] < 31:
        sum += prizes[i] * In[i] * discounts[i][1]
    else:
        sum += prizes[i] * In[i] * discounts[i][2]
print(int(sum))