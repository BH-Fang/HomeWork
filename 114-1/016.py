"""
chs = input().split(' ')
while len(chs) != 1:
    if '*' in chs or '/' in chs:
        for i in range(1, 8, 2):
            if i < len(chs):
                op = chs[i]
                if op == '*':
                    chs[i] = float(chs[i - 1]) * float(chs[i + 1])
                    del chs[i + 1]
                    del chs[i - 1]
                elif op == '/':
                    chs[i] = float(chs[i - 1]) / float(chs[i + 1])
                    del chs[i + 1]
                    del chs[i - 1]
    else:
        for i in range(1, 8, 2):
            if i < len(chs):
                op = chs[i]
                if op == '+':
                    chs[i] = float(chs[i - 1]) + float(chs[i + 1])
                    del chs[i + 1]
                    del chs[i - 1]
                elif op == '-':
                    chs[i] = float(chs[i - 1]) - float(chs[i + 1])
                    del chs[i + 1]
                    del chs[i - 1]
    
print('{:.2f}'.format(chs[0]))
"""

def calc(chs):
    high = ['*', '/']
    low = ['+', '-']
    op_index = -1
    
    for index, item in enumerate(chs):
        if item in high:
            op_index = index
            break
    
    if op_index == -1:
        for index, item in enumerate(chs):
            if item in low:
                op_index = index
                break
    
    leftIndex = op_index - 1
    rightIndex = op_index + 1
    left = float(chs[leftIndex])
    right = float(chs[rightIndex])
    #print(chs)
    if chs[op_index] == '*':
        chs[op_index] = str(left * right)
    elif chs[op_index] == '/':
        chs[op_index] = str(left / right)
    elif chs[op_index] == '+':
        chs[op_index] = str(left + right)
    elif chs[op_index] == '-':
        chs[op_index] = str(left - right)
    del chs[rightIndex]
    del chs[leftIndex]
    

chs = input().split()

while len(chs) != 1:
    calc(chs)
    
#ans = float(int(chs[0] * 100) / 100)
print('{:.2f}'.format(float(chs[0])))
