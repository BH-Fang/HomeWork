ids = []
times = []
conflict = []
for i in range(3):
    ids += [int(input())]
    times += [(int(input()), int(input()))]

for i in range(len(ids) - 1):
    for j in range(len(times[i])):
        for k in range(i + 1, len(ids)):
            for l in range(len(times[k])):
                if times[i][j] == times[k][l]:
                    t = sorted([ids[i], ids[k]])
                    conflict += [(t[0], t[1], times[i][j])]
conflict.sort()
if len(conflict) == 0:
    print('correct')
else:
    for i in conflict:
        print('%d and %d conflict on %d' %(i[0], i[1], i[2]))
