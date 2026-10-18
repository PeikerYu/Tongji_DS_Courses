import time

def solve_optimized_queens(N=8):
    solutions = []
    # 用于存放位运算结果转换回来的坐标格式
    def store_solution(board):
        solutions.append(board[:])

    def backtrack(row, cols_mask, diag1_mask, diag2_mask, board):
        if row == N:
            store_solution(board)
            return

        # 计算当前行所有可以放的位置 (1表示可以放)
        # (1 << N) - 1 是生成一个长度为 N 的全 1 掩码
        available_positions = (~(cols_mask | diag1_mask | diag2_mask)) & ((1 << N) - 1)

        # 对称性优化：如果是第一行，只搜左半边
        if row == 0:
            available_positions &= ((1 << (N // 2)) - 1)

        while available_positions:
            # 取出最低位的 1 (即尝试最左边的一个空位)
            position = available_positions & -available_positions
            # 算出这个 1 是在第几列
            col = bin(position - 1).count('1')
            
            board.append(col)
            # 递归下一行，更新列、左斜线、右斜线掩码
            # diag1 是左下斜线，向下移动一行需要左移 1 位
            # diag2 是右下斜线，向下移动一行需要右移 1 位
            backtrack(row + 1, 
                      cols_mask | position, 
                      (diag1_mask | position) << 1, 
                      (diag2_mask | position) >> 1, 
                      board)
            board.pop()
            
            # 把试过的这个 1 去掉
            available_positions &= available_positions - 1

    start_time = time.time()
    backtrack(0, 0, 0, 0, [])
    
    # 镜像生成另一半解
    base_count = len(solutions)
    for i in range(base_count):
        mirrored = [N - 1 - c for c in solutions[i]]
        solutions.append(mirrored)
        
    # 特殊处理：如果 N 是奇数，中间那一列的解在上面没搜到，这里 N=8 不涉及
    return solutions, time.time() - start_time

if __name__ == "__main__":
    N = 12
    res, duration = solve_optimized_queens(N)
    print(f"【优化版】找到 {len(res)} 个解，耗时: {duration:.6f} 秒")