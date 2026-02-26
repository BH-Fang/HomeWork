
def permutation(exist, n, string = ''):
    if len(string) == n:
        yield string
    else:
        for c in exist:
            yield from permutation(exist, n, string + c)

def isEffective(string, n, m, c, condition):
    for i in range(len(string) - m + 1):
        sub = string[i : i+m]
        if sub.count(c) < condition:
            return False
        
    return True
    
        
def main():
    exist, n, m, condition, c = input(), int(input()), int(input()), int(input()), input()   
    count = 0
    
    for s in permutation(exist, n):
        if isEffective(s, n, m, c, condition):
            count += 1
             
    print(count)

main()