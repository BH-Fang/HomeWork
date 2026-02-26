def T_effect(password):
    password_len = len(password)
    ch_set = set()
    has_upper = False
    has_special = False
    if password_len < 3 or password_len > 5:return False
    for ch in password: 
        if not('D' >= ch >= 'A') and not('d' >= ch >= 'a') and not('9' >= ch >= '0') and ch not in '@#$!_': return False
        if ch in ch_set: return False
        if str.isupper(ch): has_upper = True
        if ch in '@#$!_': has_special = True
        ch_set.add(ch)
    return has_upper and has_special

def S_effect(str1, str2):
    A_count = 0
    B_count = 0
    for i in range(len(str1)):
        if str1[i] in str2: B_count += 1
        if str1[i] == str2[i]: A_count += 1
    B_count -= A_count
    return A_count, B_count

def G_effect(pw_len, data, c):
    current = ['']
    result = []
    def Permutation():
        if len(current[0]) == pw_len:
            if not T_effect(current[0]): return
            for key, value in data[pw_len].items():
                X, Y = S_effect(current[0], key)
                if (X, Y) != value: return
            result.append(current[0])
        else:
            for ch in c:
                if ch not in current[0]:
                    current[0] += ch
                    Permutation()
                    current[0] = current[0][:-1]
    Permutation()
    return result

def main():
    cmd = input()
    N = int(input())
    if cmd == 'T':
        result = ''
        for _ in range(N):
            if T_effect(input()): result += 'T'
            else: result += 'F'
        print(result)
    elif cmd == 'S':
        result = ''
        for _ in range(N):
            str_input = input().split()
            X, Y = S_effect(str_input[0], str_input[1])
            result += '{}A{}B'.format(X, Y)  + '\n'
        print(result, end = '')
    elif cmd == 'G':
        c = 'ABCDabcd0123456789@#$!_'
        data = {3:{}, 4:{}, 5:{}} # {3:pw:(X, Y)...}
        for _ in range(N):
            In = input().split()
            data[len(In[0])][In[0]] = (int(In[1][0]), int(In[1][2]))
        result = []
        for i in range(3, 6):
            if len(data[i]): result.append(G_effect(i, data, c))
        for q in result:
            for w in q:
                print(w, end = ' ')
            print()

main()