# method1_brute.py
# 方法1：非逻辑编程穷举 + kanren逻辑编程筛选

import itertools
import time
from kanren import run, var, eq, lall
from utils import print_board


def no_diag_goal(col_i, col_j, row_diff):
    """
    斜线约束的kanren goal形式。
    col_i、col_j是已经确定的整数（不是逻辑变量），
    直接判断是否满足斜线约束，满足就yield s，不满足就拦截。
    """
    def goal(s):
        if abs(col_i - col_j) != row_diff:
            yield s   # 约束满足，通过
        # 否则什么都不返回，相当于筛选掉
    return goal


def solve_brute_with_kanren(N=8):
    solutions = []

    # 第一步：非逻辑编程穷举
    # 生成所有全排列，列约束天然满足，还不知道斜线是否合法
    all_permutations = list(itertools.permutations(range(N)))

    # 第二步：kanren逻辑编程筛选
    # 对每个排列，构造斜线约束的goal，交给kanren判断是否合法
    for perm in all_permutations:
        diag_constraints = []
        for i in range(N):
            for j in range(i + 1, N):
                diag_constraints.append(
                    no_diag_goal(perm[i], perm[j], j - i)
                )

        # run(1,...) 只要能找到1个解就说明约束全部满足
        x = var()
        result = run(1, x, lall(*diag_constraints), eq(x, True))

        if result:
            solutions.append(list(perm))

    return solutions


if __name__ == "__main__":
    print("方法1：非逻辑编程穷举 + kanren逻辑编程筛选")

    start = time.time()
    results = solve_brute_with_kanren(N=8)
    elapsed = time.time() - start

    print(f"候选排列总数：{len(list(itertools.permutations(range(8))))} 个（8!）")
    print(f"筛选后合法解：{len(results)} 个")
    print(f"耗时：{elapsed:.4f} 秒")
    print()
    print("前3个解的棋盘：")
    for i, sol in enumerate(results[:3]):
        print(f"解 {i+1}：{sol}")
        print_board(sol)