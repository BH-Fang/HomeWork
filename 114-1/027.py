'''
def printMatrix(matrix):
    for i in matrix:
        for j in i:
            print(j, end=' ')
        print()
        
def AiEffect(matrix, row, col):
    for i in range(5):
        if i != row and matrix[i][col] != '__':
            matrix[row][col] = 'Cn'
            return

def CnEffect(matrix, row, col):
    if row - 1 >= 0 and matrix[row - 1][col] != '__':
        matrix[row][col] = 'Hy'
        
def HyEffect(matrix, row, col):
    count = 0
    l = [(row, col + 1), (row + 1, col), (row, col - 1), (row - 1, col)]
    for pos in l:
        if 5 > pos[0] > -1 and 5 > pos[1] > -1 and matrix[pos[0]][pos[1]] != '__':
            count += 1
    if count >= 2:
        for pos in l:
            if 5 > pos[0] > -1 and 5 > pos[1] > -1:
                now = matrix[pos[0]][pos[1]]
                if now == '__':
                    matrix[pos[0]][pos[1]] = 'Na'       

def NaEffect(matrix, row, col):
    if col + 1 < 5 and matrix[row][col + 1] == '__':
        matrix[row][col + 1] = 'Qx'
    if col - 1 > -1:
        matrix[row][col - 1] = 'Hy'
        
def QxEffect(matrix, row, col):
    count = dict()
    for c in range(5):
        now = matrix[row][c]
        if now != '__':
            count[now] = count.get(now, 0) + 1
    if count and max(count.values()) >= 3:
        maxPlant = max(count, key = count.get)
        for c in range(5):
            if matrix[row][c] == maxPlant:
                matrix[row][c] = 'Ai'

def afteraDay(matrix):
    spPlant = []
    for i, row in enumerate(matrix):
        for j, plant in enumerate(row):
            if plant != '__':
                spPlant.append((plant, i, j))
    
    for sp in spPlant:
        if sp[0] == 'Ai' and matrix[sp[1]][sp[2]] == sp[0]:
            AiEffect(matrix, sp[1], sp[2])
        elif sp[0] == 'Cn' and matrix[sp[1]][sp[2]] == sp[0]:
            CnEffect(matrix, sp[1], sp[2])
        elif sp[0] == 'Hy' and matrix[sp[1]][sp[2]] == sp[0]:
            HyEffect(matrix, sp[1], sp[2])
        elif sp[0] == 'Na' and matrix[sp[1]][sp[2]] == sp[0]:
            NaEffect(matrix, sp[1], sp[2])
        elif sp[0] == 'Qx' and matrix[sp[1]][sp[2]] == sp[0]:
            QxEffect(matrix, sp[1], sp[2])

days = int(input())
matrix = [input().split(), input().split(), input().split(), input().split(), input().split()]
for day in range(days):
    afteraDay(matrix)
printMatrix(matrix)
'''

# 定義菜園大小和空格
ROWS = 5
COLS = 5
EMPTY = "__"

def is_valid(r, c):
    """檢查座標 (r, c) 是否在 5x5 網格內"""
    return 0 <= r < ROWS and 0 <= c < COLS

def get_adjacent_cells(r, c):
    """獲取 (r, c) 上下左右的有效相鄰座標"""
    cells = []
    # (dr, dc) 分別代表 (上, 下, 左, 右)
    for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        nr, nc = r + dr, c + dc
        if is_valid(nr, nc):
            cells.append((nr, nc))
    return cells

def get_adjacent_plants_count(r, c, garden):
    """計算 (r, c) 相鄰有多少株植物"""
    count = 0
    for nr, nc in get_adjacent_cells(r, c):
        if garden[nr][nc] != EMPTY:
            count += 1
    return count

def print_garden(garden):
    """以指定格式輸出菜園"""
    for row in garden:
        print(" ".join(row))

def simulate_day(garden):
    """模擬一天的植物效果"""
    
    # 核心規則：
    # 建立一個 5x5 列表，追蹤哪些植物在"這一天"被種下或改變了種類
    # 被標記為 True 的植物，其效果在"這一天"不會生效
    has_triggered = [[False for _ in range(COLS)] for _ in range(ROWS)]

    # 依照規則：由左上至右下 (row-major order) 依序生效
    for r in range(ROWS):
        for c in range(COLS):
            
            # 1. 檢查此格是否已被(同天)其他植物效果影響
            if has_triggered[r][c]:
                continue

            # 2. 獲取當前植物種類
            plant = garden[r][c]

            # 3. 如果是空格，跳過
            if plant == EMPTY:
                continue

            # --- 根據植物種類，應用效果 ---

            # 效果：Ai
            # "若自身所在行(Column)有其他植物，則自身變成Cn"
            if plant == 'Ai':
                has_other_in_col = False
                for i in range(ROWS):
                    if i != r and garden[i][c] != EMPTY:
                        has_other_in_col = True
                        break
                if has_other_in_col:
                    garden[r][c] = 'Cn'
                    has_triggered[r][c] = True

            # 效果：Cn
            # "若自身上方有相鄰的植物，則自身變成Hy"
            elif plant == 'Cn':
                # 檢查上方 (r-1, c)
                if is_valid(r - 1, c) and garden[r - 1][c] != EMPTY:
                    garden[r][c] = 'Hy'
                    has_triggered[r][c] = True

            # 效果：Hy
            # "若自身相鄰至少兩株植物，則在自身相鄰的空格種Na"
            elif plant == 'Hy':
                if get_adjacent_plants_count(r, c, garden) >= 2:
                    # 遍歷所有相鄰格子
                    for nr, nc in get_adjacent_cells(r, c):
                        # 如果是空格
                        if garden[nr][nc] == EMPTY:
                            garden[nr][nc] = 'Na'
                            has_triggered[nr][nc] = True # 新種下的 Na 當天不生效

            # 效果：Na
            elif plant == 'Na':
                # 1. "在自身右方相鄰的空格種Qx"
                nr_right, nc_right = r, c + 1
                if is_valid(nr_right, nc_right) and garden[nr_right][nc_right] == EMPTY:
                    garden[nr_right][nc_right] = 'Qx'
                    has_triggered[nr_right][nc_right] = True # 新種下的 Qx 當天不生效

                # 2. "在自身左方相鄰的空格種Hy"
                # 3. "若自身左方相鄰的格子有植物，將其變成Hy"
                # (規則 2 和 3 可以合併：只要左方有效，就將其變為 Hy)
                nr_left, nc_left = r, c - 1
                if is_valid(nr_left, nc_left):
                    garden[nr_left][nc_left] = 'Hy'
                    has_triggered[nr_left][nc_left] = True # 被改變的 Hy 當天不生效

            # 效果：Qx
            # "若所在列(Row)有至少三株種類彼此相同的植物，將它們都變為Ai"
            elif plant == 'Qx':
                counts = {}
                row_plants = garden[r] # 獲取 Qx 所在的整列 (row)
                
                # 計算該列中每種植物的數量
                for p in row_plants:
                    if p != EMPTY:
                        counts[p] = counts.get(p, 0) + 1
                
                target_plant = None
                # 檢查是否有任何一種植物數量 >= 3
                for p_type, count in counts.items():
                    if count >= 3:
                        target_plant = p_type
                        break
                
                # 如果找到了
                if target_plant:
                    # 將該列所有 "target_plant" 變為 "Ai"
                    for j in range(COLS):
                        if garden[r][j] == target_plant:
                            garden[r][j] = 'Ai'
                            has_triggered[r][j] = True # 被改變的 Ai 當天不生效

    # 返回模擬一天後的菜園狀態
    return garden

def main():
    try:
        # 讀取天數
        days = int(sys.stdin.readline().strip())
        
        # 讀取初始菜園
        garden = []
        for _ in range(ROWS):
            garden.append(sys.stdin.readline().strip().split())

        # 進行 T 天模擬
        for _ in range(days):
            garden = simulate_day(garden)

        # 輸出最終結果
        print_garden(garden)

    except EOFError:
        pass
    except Exception as e:
        print(f"An error occurred: {e}", file=sys.stderr)

main()