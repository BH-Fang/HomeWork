
def create_map(map_input, select):
    map = [False] * len(map_input)
    for n in select:
        map[map_input.index(n)] = True
    return map

def count_line(map, N):
    count = 0
    #horizental
    for i in range(0, N * N, N):
        bingo = True
        for j in range(i, i + N):
            if not map[j]:
                bingo = False
                break
        if bingo:
            count += 1
    #virtical
    for i in range(N):
        bingo = True
        for j in range(i, N * N, N):
            if not map[j]:
                bingo = False
                break
        if bingo:
            count += 1
    #X
    #\
    xc = 0
    p = 0
    bingo = True
    for i in range(0, N * N, N):
        if not map[i + p]:
                bingo = False
                break
        p += 1
    if bingo:
        xc += 1
    #/
    p = N - 1
    bingo = True
    for i in range(0, N * N, N):
        if not map[i + p]:
                bingo = False
                break
        p -= 1
    if bingo:
            xc += 1
    count += xc
    if xc == 2:
         count += 1
    #L
    bingo = True
    for i in range(0, N * N, N):
        if i == N * N - N:
            for j in range(N):
                if not map[i + j]:
                    bingo = False
                    break
            break          
        if not map[i]:
                bingo = False
                break
    if bingo:
        count += 1
    return count

def main():
    N, M = int(input()), int(input())
    A_map_input = list(map(int, input().split()))
    B_map_input = list(map(int, input().split()))
    select = list(map(int, input().split()))
    A_map = create_map(A_map_input, select)
    B_map = create_map(B_map_input, select)

    A_lines_count = count_line(A_map, N)
    B_lines_count = count_line(B_map, N)

    if A_lines_count > B_lines_count:
        print('A Win')
    elif A_lines_count < B_lines_count:
         print('B Win')
    else:
         print('Tie')

main()