def get_matrix(r):
    matrix = []
    for _ in range(r):
        matrix.append([int(n) for n in input().strip().split()])
    return matrix

def print_matrix(matrix):
    for line in matrix:
        print(' '.join([str(n) for n in line]))
        
def is_safe(matrix, row, col, num):
    r = len(matrix)
    for i in range(r):
        if matrix[row][i] == num: return False
        if matrix[i][col] == num: return False
    
    block = int(r ** 0.5)
    sr = (row // block) * block
    sc = (col // block) * block
    for i in range(block):
        for j in range(block):
            if matrix[sr + i][sc + j] == num:
                return False
    
    return True

def solve_matrix(matrix, r):  
    empty = -1
    for i in range(r):
        for j in range(r):
            if matrix[i][j] == 0:
                empty = (i, j)
                break
    if empty == -1: return True
    row, col = empty
    for n in range(1, r + 1):         
        if is_safe(matrix, row, col, n):
            matrix[row][col] = n
            if solve_matrix(matrix, r):
                return True
            else:
                matrix[row][col] = 0
    return False

def main():
    r = 9
    matrix = get_matrix(r)
    print('-------------------------------------------------------')
    if solve_matrix(matrix, r): print_matrix(matrix)
    
main()