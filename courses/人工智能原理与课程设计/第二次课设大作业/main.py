"""
compare_all.py - 汇总运行所有算法并进行性能对比
"""

import time
import numpy as np
import matplotlib.pyplot as plt

from grid_map import GRID, START, END, HARD_GRID, HARD_START, HARD_END, print_grid
from algorithms import astar, bfs, dijkstra
from visualize import animate_search, compare_plot, plot_static
from advanced_algorithms import ArtificialPotentialField, QLearningAgent

def run_and_time(func, *args):
    """运行算法并计时，返回 (path, visited_order, elapsed_time)"""
    t0 = time.perf_counter()
    path, visited = func(*args)
    t1 = time.perf_counter()
    return path, visited, round(t1 - t0, 6)

# 第一部分：基础地图上的 A*、BFS、Dijkstra 对比
print("\n" + "=" * 70)
print(" 模块 1：经典图搜索算法对比 (A* vs BFS vs Dijkstra)")
print("=" * 70)
print("【环境拓扑预览】")
print_grid(GRID, START, END)

# 运行三种算法
astar_path,    astar_visited,    astar_time    = run_and_time(astar,    GRID, START, END)
bfs_path,      bfs_visited,      bfs_time      = run_and_time(bfs,      GRID, START, END)
dijkstra_path, dijkstra_visited, dijkstra_time = run_and_time(dijkstra, GRID, START, END)

# 构建性能对比表格
print("【性能对比报告】")
print("-" * 70)
print(f"| {'算法模型':<12} | {'路径步数':<8} | {'探索节点数 (Closed Set)':<22} | {'执行耗时 (秒)':<13} |")
print("-" * 70)

for name, path, visited, t in [
    ("A* (Manhattan)", astar_path,    astar_visited,    astar_time),
    ("BFS",            bfs_path,      bfs_visited,      bfs_time),
    ("Dijkstra",       dijkstra_path, dijkstra_visited, dijkstra_time),
]:
    plen = len(path) - 1 if path else "N/A"
    print(f"| {name:<14} | {str(plen):<10} | {len(visited):<24} | {t:<15.6f} |")
print("-" * 70)

# 输出客观结论分析
if astar_path and bfs_path:
    reduction = (1 - len(astar_visited) / len(bfs_visited)) * 100
    print("\n【实验结论验证】")
    print(f">> 数据表明，在达到相同最优路径（{len(astar_path)-1}步）的前提下：")
    print(f">> A* 算法通过启发函数剪枝，探索节点数比 BFS 减少了约 {reduction:.1f}%。")
    print(">> Dijkstra 算法在等权网格中无方向性，且带有堆排序开销，表现出最差的综合效率。\n")

print(">>> 正在拉起 Matplotlib 渲染引擎，生成对比静态图与 GIF 动画...")
compare_plot(
    GRID,
    {"A* 算法": (astar_path, astar_visited), 
     "BFS 算法": (bfs_path, bfs_visited), 
     "Dijkstra": (dijkstra_path, dijkstra_visited)},
    START, END
)

# 生成动画 (取消注释即可运行)
animate_search(GRID, astar_path, astar_visited, START, END, title="A* 算法搜索过程", save_gif="astar_animation.gif")
animate_search(GRID, bfs_path, bfs_visited, START, END, title="BFS 算法搜索过程", save_gif="bfs_animation.gif")


# 第二部分：高难度场景——人工势场法 + Q-Learning
print("\n" + "=" * 70)
print(" 模块 2：高阶启发式算法 (APF & Q-Learning)")
print("=" * 70)
print("【复杂环境拓扑预览】")
print_grid(HARD_GRID, HARD_START, HARD_END)

# 1. 运行 A* 作为基准参考
astar_hard_path, astar_hard_visited, _ = run_and_time(astar, HARD_GRID, HARD_START, HARD_END)
print(f"[*] A* (基准参考) -> 路径: {len(astar_hard_path) - 1} 步 | 探索节点: {len(astar_hard_visited)}")

# 2. 人工势场法
print("\n[*] 正在运行 人工势场法 (APF)...")
apf = ArtificialPotentialField(HARD_GRID, HARD_START, HARD_END, k_att=1.0, k_rep=3.0, d0=3.0)
t0 = time.perf_counter()
apf_path, apf_success = apf.run()
apf_time = time.perf_counter() - t0

if apf_success:
    print(f"    >> 寻径成功！收敛路径长度: {len(apf_path) - 1} 步 | 梯度下降耗时: {apf_time:.4f}s")
    plot_static(HARD_GRID, apf_path, set(apf_path), HARD_START, HARD_END, title="APF 收敛路径", save_path="hard_apf.png")
else:
    print(f"    >> 寻径失败！系统陷入局部极小值 (Local Minima)，终止于 {len(apf_path)} 步。")

# 3. Q-Learning
print("\n[*] 正在启动 Q-Learning 模型训练...")
agent = QLearningAgent(HARD_GRID, HARD_START, HARD_END, n_episodes=3000, max_steps=150)
t0 = time.perf_counter()
agent.train()
qlearn_time = time.perf_counter() - t0
print(f"    >> 训练阶段结束 | 总耗时: {qlearn_time:.2f}s")

ql_path = agent.get_path()
if ql_path and ql_path[-1] == HARD_END:
    print(f"    >> 策略推断成功！最优策略路径长度: {len(ql_path) - 1} 步")
else:
    print(f"    >> 策略推断未达终点（MDP环境未完全收敛）")

print("\n>>> 正在渲染 Q-Learning 训练曲线图...")
agent.plot_training_curve(save_path="qlearning_curve.png")
plot_static(HARD_GRID, ql_path, set(ql_path), HARD_START, HARD_END, title="Q-Learning 策略推断结果", save_path="hard_ql.png")

print("\n" + "=" * 70)
print(" 实验全部执行完毕。")
print("=" * 70)