# method3_neq.py
import time
from kanren import run, var, membero, lall
from kanren import isvar
from unification.core import walk
from utils import print_board

# ============================================
# 核心：自定义neq（不等约束）
#
# kanren标准库没有提供neq，需要手动实现。
# 原理：
#   goal是一个函数：输入当前变量替换状态s，
#   输出满足约束的所有新状态（用yield生成）
#
#   neq的逻辑：
#     - walk(u, s) 在当前状态s里查出u绑定的值
#     - walk(v, s) 在当前状态s里查出v绑定的值
#     - 若 u_val != v_val：yield s（约束满足，继续）
#     - 若 u_val == v_val：return（约束失败，剪枝）
# ============================================
def neq(u, v):
    """
    自定义列约束：确保两个变量绑定的值不相等
    """
    def goal(s):
        # 从当前搜索状态 s 中解析出变量 u 和 v 的具体数值
        u_val = walk(u, s)
        v_val = walk(v, s)
        
        # 逻辑判断：如果数值相等，说明违反了列约束
        if u_val == v_val:
            return        # 停止该分支，引擎会自动回溯
            
        yield s           # 约束通过，将当前状态传递给下一个目标
    return goal

def no_diag(qi, qj, diff):
    """
    自定义斜线约束：根据行差 diff 判断列差是否会导致斜线冲突  
    """
    def goal(s):
        qi_val = walk(qi, s)
        qj_val = walk(qj, s)
        
        # 延迟检查：如果变量尚未确定数值，则先跳过检查
        if isvar(qi_val) or isvar(qj_val):
            yield s
        else:
            # 核心公式：|qi_val - qj_val| != diff
            if abs(qi_val - qj_val) != diff:
                yield s
    return goal

def solve_with_neq(N=5):
    q = [var() for _ in range(N)]
    cols = list(range(N))
    constraints = [membero(q[i], cols) for i in range(N)]
    for i in range(N):
        for j in range(i + 1, N):
            constraints.append(neq(q[i], q[j]))           # 使用封装好的neq
            constraints.append(no_diag(q[i], q[j], j - i))
    return run(0, q, lall(*constraints))

if __name__ == "__main__":
    print("方法3：自定义neq函数 + kanren（N=5演示）")
    print("-" * 40)
    start = time.time()
    results = solve_with_neq(N=5)
    elapsed = time.time() - start
    print(f"N=5：找到 {len(results)} 个解，耗时 {elapsed:.3f} 秒")
    print()
    print("第一个解的棋盘：")
    if results:
        print_board(list(results[0]))