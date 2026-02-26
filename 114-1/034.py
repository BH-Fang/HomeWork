
def getAns(weight_list, N, M):
    sum_of_weight_list =  sum(weight_list)
    
    if sum_of_weight_list % N != 0:
        return 'fail'
    target_weight = sum_of_weight_list / N
    
    def dfs(index, weight_now, counts_now):
        if index == len(weight_list):
            return True
        for i in range(N):
            if weight_now[i] + weight_list[index] <= target_weight and counts_now[i] + 1 <= M:
                weight_now[i] += weight_list[index]
                counts_now[i] += 1
                if dfs(index + 1, weight_now, counts_now):
                    return True
                else:
                    weight_now[i] -= weight_list[index]
                    counts_now[i] -= 1
                    continue
            else:
                continue
        return False
            
    weight = [0] * N
    count = [0] * N
    if dfs(0, weight, count):
        return 'ok'
    return 'fail'

def main():
    input_line1 = input()
    N = int(input())
    M = int(input())
    weight_list = []
    
    for ch in input_line1:
        weight = ord(ch) - (ord('A') - 1)
        if weight < 1 or weight > ord('Z') - (ord('A') + 1):
            print('error')
            return
        else:
            weight_list.append(weight)
    print(getAns(weight_list, N, M))

main()