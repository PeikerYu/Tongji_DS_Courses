# method4_search.py
import time
from collections import deque
from utils import print_board

def check_safe(board, row, col):
    """
    检查在第row行第col列放皇后是否安全
    遍历已经放好的每一行，检查列冲突和斜线冲突
    """
    for r in range(row):
        c = board[r]
        if c == col:                        # 同一列
            return False
        if abs(r - row) == abs(c - col):    # 同一斜线
            return False
    return True

def solve_dfs(N=8):
    solutions = []

    def dfs(board, row):
        # 递归出口：当行索引达到 N 时，表示 0 至 N-1 行均已合法排布
        if row == N:
            # 必须存储 board 的副本，以防回溯操作修改已找到的解
            solutions.append(board[:]) 
            return
            
        # 遍历当前行的每一列，寻找安全位置
        for col in range(N):
            # 实时检查：在进入下一层递归前验证当前冲突
            if check_safe(board, row, col):
                board.append(col)    # 记录当前行的选择
                dfs(board, row + 1)  # 递归探索下一行
                board.pop()          # 回溯：撤销当前选择，恢复棋盘状态以尝试下一列

    dfs([], 0)
    return solutions

def solve_bfs(N=8):
    solutions = []
    # 队列中存储的是每一层搜索产生的局部合法解
    queue = deque([[]])    

    while queue:
        board = queue.popleft() # 弹出当前最浅层的状态
        row = len(board)        # 根据列表长度确定当前处理的行号
        
        if row == N:
            solutions.append(board) # 达到目标深度，记录完整解
            continue
            
        for col in range(N):
            if check_safe(board, row, col):
                # 产生新的列表对象并入队，利用对象独立性避免手动回溯
                queue.append(board + [col])   

    return solutions

if __name__ == "__main__":
    print("方法4：DFS和BFS")
    print("-" * 40)

    start = time.time()
    dfs_results = solve_dfs(N=12)
    t_dfs = time.time() - start
    print(f"DFS：找到 {len(dfs_results)} 个解，耗时 {t_dfs:.6f} 秒")
    print("第一个解：")
    print_board(dfs_results[0])

    start = time.time()
    bfs_results = solve_bfs(N=12)
    t_bfs = time.time() - start
    print(f"BFS：找到 {len(bfs_results)} 个解，耗时 {t_bfs:.6f} 秒")
    print("第一个解：")
    print_board(bfs_results[0])

    print(f"两种方法结果数量一致：{len(dfs_results) == len(bfs_results)}")