In = [int(input()), int(input()), int(input()), int(input()), int(input()), int(input())]
noLine = 0
for i in range(2, 5, 2):
    if In[i] > In[i - 1]:
        noLine += In[i] - In[i - 1]
    elif In[i - 1] > In[i + 1]:
        In[i - 1], In[i + 1] = In[i + 1], In[i - 1]
In.sort()
ans = In[5] - In[0] - noLine
print(ans)