def pop(stack : list):
    l = len(stack)
    if l == 0: return None
    else:
        o = stack[l - 1]
        del stack[l - 1]
        return o
    
def top(stack : list):
    return stack[len(stack) - 1]

def st(text):
    newText = ''
    sp = text.split(',')
    for s in sp:
        indexOfPlus = s.find('+')
        indexOfTimes = s.find('*')
        if indexOfPlus != -1: newText += s[:indexOfPlus] + s[indexOfPlus + 1:]
        elif indexOfTimes != -1: newText += s[:indexOfTimes] * int(s[indexOfTimes + 1:]) if s[indexOfTimes + 1:].isdigit() else int(s[:indexOfTimes]) * s[indexOfTimes + 1:]
        else: newText += s
            
    return newText

def main():
    bracket = ['{', '}', '[', ']', '(', ')']
    N = int(input())
    Out = []
    for i in range(N):
        In = input()
        isViolation = False
        isUnbalance = False
        stack = []
        text = ''
        for index, ch in enumerate(In):
            if ch in bracket:
                brIndex =  bracket.index(ch)
                if brIndex % 2 == 0:
                    if len(stack) != 0 and bracket.index(top(stack)) > brIndex:
                        isViolation = True
                    stack.append(ch)
                else:
                    if len(stack) != 0 and bracket.index(top(stack)) == brIndex - 1:
                        pop(stack)
                    else:
                        isUnbalance = True 
                        break
            else:
                text += ch
                if index != len(In) - 1 and In[index + 1] in bracket:
                    text += ','
                
        if len(stack) != 0: isUnbalance = True
        
        if isUnbalance: Out.append('Unbalanced')
        elif isViolation: Out.append('Hierarchy Violation')
        else:
            text = st(text)
            Out.append(text)
            
    for line in Out:
        print(line)

main()