
def pn(str, rightSp):
    
    if len(rightSp) == 3:
        if rightSp[0] == '': rightSp[0] = 0
        else: rightSp[0] = int(rightSp[0])
        if rightSp[1] == '': rightSp[1] = len(str)
        else: rightSp[1] = int(rightSp[1])
        if rightSp[2] == '': rightSp[2] = 1
        else: rightSp[2] = int(rightSp[2])
        print(str[rightSp[0]:rightSp[1]:rightSp[2]])
    elif len(rightSp) == 2:
        if rightSp[0] == '': rightSp[0] = 0
        else: rightSp[0] = int(rightSp[0])
        if rightSp[1] == '': rightSp[1] = len(str)
        else: rightSp[1] = int(rightSp[1])
        print(str[rightSp[0]:rightSp[1]])
    elif len(rightSp) == 1:
        print(str[int(rightSp[0])])
        

def prin(di, s):
    if '[' in s:
        sp = s.split('[')
        left = sp[0]
        right = sp[1].strip().strip(']')
        rightSp = right.split(':')
        pn(di[sp[0]], rightSp)
    else:
        print(di[s])

def exdefine(de):
    di = dict()
    for line in de:
        sp = line.split('=')
        left = sp[0].split(',')
        right = sp[1].split(',')
        for i in range(len(left)):
            di[left[i].strip()] = right[i].strip().strip("'")
    return di

def exsta(sta, di):
    for line in sta:
        if line[:5] == 'print':
            prin(di, line[6: -1])
        else:
            sp = line.split('=')
            left = sp[0].strip()
            right = list(map(lambda a: a.strip(), sp[1].split('+')))
            if len(right) == 2:
                di[left] = di[right[0]] + di[right[1]]
            else:
                di[left] = di[right[0]]

def main():
    M, N = map(int, input().split())
    de = []
    sta = []
    for _ in range(M):
        de.append(input())
    for _ in range(N):
        sta.append(input())
    di = exdefine(de)
    exsta(sta, di)
    
main()