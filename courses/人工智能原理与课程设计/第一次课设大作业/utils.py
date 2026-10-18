# utils.py
# 公共工具函数，其他文件都会用到

def print_board(solution):
    """
    打印棋盘
    solution是一个列表，solution[i] 表示第i行的皇后放在第几列
    """
    n = len(solution)
    for row in range(n):
        line = ""
        for col in range(n):
            if solution[row] == col:
                line += "♕ "
            else:
                line += "□ "
        print(line)
    print()

    