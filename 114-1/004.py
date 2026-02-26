przies = [440, 1200, 130]
nums = [int(input()), int(input()), int(input())]
sum = 0
index = 0
for num in nums:
    sum += num * przies[index]
    index  += 1
print(sum)
