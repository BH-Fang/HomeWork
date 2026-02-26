def get_time():
    timeStr = input()
    sp = timeStr.split()
    date = tuple([int(n) for n in sp[0].split('/')])
    time = tuple([int(n) for n in sp[1].split(':')])
    return (date, time)

def isAcountLegal(accountStr):
    area_code = ord(accountStr[0]) - 55
    check_code = int(accountStr[-1])
    weight = [1, 9, 8, 7, 6, 5, 4, 3, 2, 1]
    accountStr = str(area_code) + accountStr[1:-1]
    l = [int(n) for n in accountStr]
    s = 0
    for i in range(len(l)):
        s += l[i] * weight[i]
    return 10 - s % 10 == check_code or (s % 10 == 0 and check_code == 0)

def get_account():
    accountStr = ''
    while(True):
        accountStr = input()
        if not 'Z' >= accountStr[0] >= 'A': print('wrong area code')
        elif accountStr[1] not in ['1', '2']:print('wrong gender code')
        elif not isAcountLegal(accountStr): print('illegal')
        else:
            print('pass')
            break
    return accountStr
       
def isStrongEnough(passwordStr):
    score = 0
    任兩個數字在密碼中的位置不相鄰 = True
    digit_num = 0
    for index, ch in enumerate(passwordStr):
        if ch.islower(): score += 1
        elif ch.isupper(): score += 3
        elif ch.isdigit():
            score += 2
            digit_num += 1
            if index - 1 > -1 and passwordStr[index - 1].isdigit(): 任兩個數字在密碼中的位置不相鄰 = False
            if index + 1 < len(passwordStr) and passwordStr[index + 1].isdigit(): 任兩個數字在密碼中的位置不相鄰 = False
        elif ch in '{ ~!@#$%^&*<>_+=}': score += 5
    if digit_num >= 5 and 任兩個數字在密碼中的位置不相鄰: score += 15
    return score >= 30   

def get_password(passwords, account):
    passwordStr = ''
    while(True):
        passwordStr = input()
        if not isStrongEnough(passwordStr): print('not strong enough')
        else: 
            print('ok good password')
            if account in passwords: 
                if passwordStr == passwords[account]:
                    print('correct')
                    break
                else:
                    print('wrong')
            else: 
                print('new')
                break
    return passwordStr

def get_new_password(account, last3password):
    passwordStr = ''
    while(True):
        passwordStr = input()
        if not isStrongEnough(passwordStr): print('not strong enough')
        else: 
            print('ok good password')
            if passwordStr in last3password[account]:
                print('same password')
            else:
                print('password changed')
                break
    return passwordStr

def get_total_min(time):
    days_in_months = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    (y, m, d), (h, min) = time
    total_min = y * 365 * 24 * 60
    for i in range(m - 1):
        total_min += days_in_months[i] * 24 * 60
    total_min += (d - 1) * 24 * 60 + h * 60 + min
    return total_min

def isNeedToChange(time_now, last_time, limit):
    if last_time == 0:
        print('0t')
        return False
    if get_total_min(time_now) - get_total_min(last_time) >= limit: return True
    return False

def main():
    limit, n = int(input()), int(input())
    passwords = dict()
    last3passwords = dict()
    last_time = dict()
    for _ in range(n):
        time_now = get_time() # ((2025, 1, 1), (10, 0))
        account = get_account()
        password = get_password(passwords, account)
        passwords[account] = password
        if account not in last3passwords: 
            last3passwords[account] = [password]
            last_time[account] = time_now
            continue
        if isNeedToChange(time_now, last_time.get(account, 0), limit):
            print('need to change')
            password = get_new_password(account, last3passwords)
            passwords[account] = password
            if len(last3passwords[account]) == 3: last3passwords[account].pop(0)
            last3passwords[account].append(password)
            last_time[account] = time_now
        else: 
            print('no need to change')
        
main()