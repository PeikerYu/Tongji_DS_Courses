# method2_kanren.py
import time
from kanren import run, var, membero, lall
from kanren import isvar
from unification.core import walk
from utils import print_board

# kanren没有内置不等约束，需要自己写
# goal的结构：接受状态s，约束满足就yield s，不满足就return
def not_equal(u, v):
    def goal(s):
        val_u = walk(u, s)   # 在当前绑定状态s里查u的值
        val_v = walk(v, s)   # 在当前绑定状态s里查v的值
        if val_u == val_v:
            return            # 相等，约束失败，这条路剪掉
        yield s               # 不相等，约束通过，继续搜索
    return goal

# 斜线约束：|q_i - q_j| != 行差
def not_diagonal(qi, qj, row_diff):
    def goal(s):
        val_i = walk(qi, s)
        val_j = walk(qj, s)
        if isvar(val_i) or isvar(val_j):
            yield s           # 变量还没被赋值，先放过，等后续绑定
        else:
            if abs(val_i - val_j) != row_diff:
                yield s
    return goal

def solve_kanren(N=5):
    q = [var() for _ in range(N)]   # 创建N个逻辑变量
    cols = list(range(N))

    constraints = []
    # 约束1：每行皇后的列号必须在0到N-1之间
    for i in range(N):
        constraints.append(membero(q[i], cols))
    # 约束2：任意两行不同列、不同斜线
    for i in range(N):
        for j in range(i + 1, N):
            constraints.append(not_equal(q[i], q[j]))
            constraints.append(not_diagonal(q[i], q[j], j - i))

    # run(0, q, ...) 表示找所有解
    return run(0, q, lall(*constraints))

if __name__ == "__main__":
    print("方法2：kanren逻辑编程")
    print("-" * 40)
    print("kanren无约束传播，N=8极慢，下面展示N=4/5/6的耗时增长趋势：")
    print()
    for n in [4, 5, 6]:
        start = time.time()
        results = solve_kanren(N=n)
        elapsed = time.time() - start
        print(f"N={n}：找到 {len(results)} 个解，耗时 {elapsed:.3f} 秒")
    print()
    print("N=5 第一个解的棋盘：")
    r5 = solve_kanren(N=5)
    if r5:
        print_board(list(r5[0]))