def play(M, In, matrix):
    who = M
    for i in In:
        matrix[i - 1] = who
        if who == 1:
            who = 2
        else:
            who = 1

def printMatrix(matrix):
    for i in range(0, 9, 3):
        print('{0} {1} {2}'.format(matrix[i], matrix[i + 1], matrix[i + 2]))
    
def whoWin(matrix):
    for i in range(1, 3):
        if (matrix[0] == matrix[i] == matrix[2] == i or matrix[3] == matrix[4] == matrix[5] == i or matrix[6] == matrix[7] == matrix[8] == i or 
            matrix[0] == matrix[3] == matrix[6] == i or matrix[i] == matrix[4] == matrix[7] == i or matrix[2] == matrix[5] == matrix[8] == i or
            matrix[0] == matrix[4] == matrix[8] == i or matrix[2] == matrix[4] == matrix[6] == i):
            return i
    else:
        return 0
    
M = int(input())
In = input().split()
for index, item in enumerate(In):
    In[index] = int(item)
matrix = [0, 0, 0, 0, 0, 0, 0, 0, 0]
play(M, In, matrix)
winner = whoWin(matrix)

printMatrix(matrix)
if winner == 1:
    print('Player win')
elif winner == 2:
    print('Computer win')
else:
    print('Undecided')