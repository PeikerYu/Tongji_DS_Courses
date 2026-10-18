# compare_all.py
import time
from method1_brute import solve_brute_force
from method2_kanren import solve_kanren
from method3_neq import solve_with_neq
from method4_search import solve_dfs, solve_bfs
from utils import print_board

def main():
    print("=" * 55)
    print("         八皇后问题  各方法汇总对比")
    print("=" * 55)

    print("\n【方法1】全排列 + 两层循环  (N=8)")
    start = time.time()
    r1 = solve_brute_force(N=8)
    t1 = time.time() - start
    print(f"  找到 {len(r1)} 个解，耗时 {t1:.4f} 秒")

    print("\n【方法2】kanren逻辑编程  (N=5)")
    start = time.time()
    r2 = solve_kanren(N=5)
    t2 = time.time() - start
    print(f"  N=5 找到 {len(r2)} 个解，耗时 {t2:.4f} 秒")

    print("\n【方法3】自定义neq + kanren  (N=5)")
    start = time.time()
    r3 = solve_with_neq(N=5)
    t3 = time.time() - start
    print(f"  N=5 找到 {len(r3)} 个解，耗时 {t3:.4f} 秒")

    print("\n【方法4a】DFS回溯  (N=8)")
    start = time.time()
    r4a = solve_dfs(N=8)
    t4a = time.time() - start
    print(f"  找到 {len(r4a)} 个解，耗时 {t4a:.6f} 秒")

    print("\n【方法4b】BFS  (N=8)")
    start = time.time()
    r4b = solve_bfs(N=8)
    t4b = time.time() - start
    print(f"  找到 {len(r4b)} 个解，耗时 {t4b:.6f} 秒")

    print()
    print("=" * 55)
    print(f"  {'方法':<28} {'规模':<6} {'耗时(秒)'}")
    print("-" * 55)
    print(f"  {'方法1 全排列+两层循环':<28} {'N=8':<6} {t1:.4f}")
    print(f"  {'方法2 kanren逻辑编程':<28} {'N=5':<6} {t2:.4f}")
    print(f"  {'方法3 自定义neq+kanren':<28} {'N=5':<6} {t3:.4f}")
    print(f"  {'方法4a DFS回溯':<28} {'N=8':<6} {t4a:.6f}")
    print(f"  {'方法4b BFS':<28} {'N=8':<6} {t4b:.6f}")
    print("=" * 55)

    print("\n方法1 第一个解的棋盘：")
    print_board(r1[0])
    print("方法4a(DFS) 第一个解的棋盘：")
    print_board(r4a[0])

if __name__ == "__main__":
    main()