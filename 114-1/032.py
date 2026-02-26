
def OOO(Str):
    newStr = Str
    n = 6 - len(Str)
    for i in range(n):
        newStr = '0' + newStr
    return newStr

def binary2decimal(decStr : str):
    r = 0
    for i, ch in enumerate(decStr[::-1]):
        if ch == '1':
            r += 2 ** i
    return r    
        
def decimal2base3(decInt : int):
    base = 3
    餘數 = []
    while decInt != 0:
        餘數.append(str(decInt % 3))
        decInt = decInt // base
    餘數.reverse()
    return ''.join(餘數)
        
def C(M):
    if M == 0 or M == 1: return M, 1
    elif M % 2 == 0:
        result, count = C(M / 2)
        return result, count + 1
    else:
        result1, count1 = C((M + 1) / 2)
        result2, count2 = C((M - 1) / 2)
        return result1 + result2, count1 + count2 + 1
        
def main():  
    Out = []
    while True:
        In = input()
        if In == '-1': break
        result, count = C(binary2decimal(In))
        Out.append(count - 1)
    
    for line in Out:
        print(OOO(decimal2base3(line)))

main()