"""
grid_map.py - 地图环境配置模块
"""
import numpy as np

# 基础地图（作业给定场景）
GRID = np.array([
    [0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 1, 0, 0, 0],
    [0, 1, 0, 0, 1, 0, 0, 0],
    [0, 1, 0, 0, 1, 0, 0, 0],
    [0, 0, 0, 0, 1, 0, 0, 0],
    [0, 0, 0, 0, 1, 0, 0, 0],
    [0, 0, 0, 0, 1, 0, 0, 0],
    [0, 1, 1, 1, 1, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0]
])

START = (2, 3)   # 起点 S
END   = (4, 7)   # 终点 E

# 高难度地图（用于进阶算法）
HARD_GRID = np.array([
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0, 0, 1, 1, 1, 0],
    [0, 1, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 0, 0, 1, 1, 1, 1, 0, 1, 0],
    [0, 0, 0, 1, 0, 0, 1, 0, 0, 0],
    [0, 1, 0, 1, 0, 0, 1, 0, 1, 0],
    [0, 1, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 1, 1, 1, 1, 0, 1, 1, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
])

HARD_START = (0, 0)
HARD_END   = (9, 9)

def print_grid(grid, start, end, path=None):
    """
    终端等宽打印矩阵，确保不会因为全角/半角字符混用导致错位。
    [S]=起点  [E]=终点  ███=障碍   * =路径   . =空地
    """
    rows, cols = grid.shape
    print("\n    " + "-" * (cols * 3 + 2))
    for r in range(rows):
        row_str = "    |"
        for c in range(cols):
            pos = (r, c)
            if pos == start:
                row_str += "[S]"
            elif pos == end:
                row_str += "[E]"
            elif grid[r][c] == 1:
                row_str += "███"
            elif path and pos in path:
                row_str += " * "
            else:
                row_str += " . "
        row_str += "|"
        print(row_str)
    print("    " + "-" * (cols * 3 + 2) + "\n")