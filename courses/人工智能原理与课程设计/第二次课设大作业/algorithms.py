"""
algorithms.py - 路径搜索算法模块
包含 A*、BFS、Dijkstra 三种算法的完整实现。
每个函数均返回 (最短路径, 访问节点顺序)，后者用于可视化搜索过程。
"""

import heapq
from collections import deque

# A* 算法 
def heuristic(a, b, mode="manhattan"):
    """
    A* 启发函数 h(n)：估计当前节点到终点的代价。
    
    - Manhattan距离：只允许上下左右移动时的最优选择
      h = |r1-r2| + |c1-c2|
    - Euclidean距离：允许斜向移动时更准确
    
    这里采用 Manhattan 距离，因为地图只允许四方向移动。
    """
    if mode == "manhattan":
        return abs(a[0] - b[0]) + abs(a[1] - b[1])
    elif mode == "euclidean":
        return ((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2) ** 0.5

def astar(grid, start, end):
    """
    A* 算法（A-Star Search）
    
    核心思路：
        f(n) = g(n) + h(n)
        g(n)：从起点到当前节点的实际代价（步数）
        h(n)：从当前节点到终点的启发估计代价（Manhattan距离）
    
    通过 f 值优先级排序的最小堆（open_set）来决定下一个探索节点，
    使得算法优先探索"看起来更近终点"的方向，大幅减少无效搜索。
    
    参数:
        grid  : numpy 二维数组，0=可通行，1=障碍
        start : 起点坐标 (row, col)
        end   : 终点坐标 (row, col)
    
    返回:
        path         : 从起点到终点的最短路径列表，失败返回 None
        visited_order: 节点被访问的顺序列表（用于可视化）
    """
    rows, cols = grid.shape
    
    # open_set: 优先队列，元素为 (f_score, (row, col))
    open_set = []
    heapq.heappush(open_set, (0 + heuristic(start, end), start))
    '''
    什么是 heapq？ Python 里没有专门的堆数据类型，堆其实就是一个普通的列表 []。但是，我们绝对不能用原生的 append() 和 pop() 去操作它。
    必须把这个列表传给 heapq.heappush() 函数，这个函数会在底层用 C 语言自动帮你把元素塞到列表的特定位置，保证列表的第 0 个元素永远是最小的。
    为什么里面要塞一个元组 (f_score, start)？ 这是 Python 堆排序的一个极其关键的语法糖！
    当 heapq 在对元素进行排序找最小值时，如果存的是元组，它会默认按照元组的第 0 个元素（也就是 f_score）进行比大小。
    '''
    
    # came_from: 记录每个节点的前驱，用于路径回溯
    came_from = {}
    
    # g_score[node]: 从起点到 node 的实际步数代价
    g_score = {start: 0}
    
    # closed_set: 已完成评估的节点，不再重复处理
    closed_set = set()
    
    # 记录节点被弹出（正式访问）的顺序，用于后续动画可视化
    visited_order = []
    
    # 四方向：上、下、左、右
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    while open_set:
        # 弹出 f 值最小的节点（最有希望的候选）
        _, current = heapq.heappop(open_set)
        '''
        heapq.heappop(open_set)：这行代码会以 O(\log N) 的极快速度，从堆里把 f 值（综合得分）最小的那个元组弹出来。
        这就是 A* 比 BFS 聪明的核心——它永远先挑离终点看起来最近的格子走。
        '''
        if current in closed_set:
            continue  # 已处理过，跳过（堆中可能有同一节点的旧记录）
        
        closed_set.add(current)
        visited_order.append(current)
        
        # 到达终点，回溯重建路径
        if current == end:
            path = []
            node = end
            while node in came_from:
                path.append(node)
                node = came_from[node]
            path.append(start)
            path.reverse()
            return path, visited_order
        
        # 遍历四个邻居
        for dr, dc in directions:
            nr, nc = current[0] + dr, current[1] + dc
            neighbor = (nr, nc)
            
            # 边界检查 + 障碍检查 + 是否已处理
            if not (0 <= nr < rows and 0 <= nc < cols):
                continue
            if grid[nr][nc] == 1:
                continue
            if neighbor in closed_set:
                continue
            
            # 计算经过 current 到达 neighbor 的实际代价（每步代价为1）
            tentative_g = g_score[current] + 1
            
            # 若找到更优路径，更新记录
            if neighbor not in g_score or tentative_g < g_score[neighbor]:
                came_from[neighbor] = current
                g_score[neighbor] = tentative_g
                f = tentative_g + heuristic(neighbor, end)
                heapq.heappush(open_set, (f, neighbor))
    
    # open_set 耗尽仍未到达终点，说明无路可走
    return None, visited_order


# BFS 算法

def bfs(grid, start, end):
    """
    BFS 算法（广度优先搜索，Breadth-First Search）
    
    核心思路：
        从起点出发，按"距起点步数"由近到远逐层展开搜索。
        先访问所有距起点1步的节点，再访问距起点2步的，以此类推。
        由于每步代价相同（均为1），BFS 第一次到达终点时
        走过的路径必然是步数最少的路径，因此 BFS 保证最优性。
    
    与 A* 的核心区别：
        BFS 没有启发函数，不区分方向好坏，向四周"无脑"展开。
        A* 利用启发函数"有目的"地搜索，通常访问节点更少。
    
    参数 & 返回值同 astar()
    """
    rows, cols = grid.shape
    
    # 使用 deque 实现队列（FIFO），保证按层扩展，deque 是基于双向链表实现的，它的 popleft() 操作是严格的 O(1) 时间复杂度。这是保证 BFS 算法在大地图上不卡死的物理基础。
    queue = deque([start])
    
    # visited: 已加入队列的节点，防止重复入队
    visited = {start}
    
    # came_from: 记录路径，start 的前驱记为 None
    came_from = {start: None}
    
    visited_order = []
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    while queue:
        current = queue.popleft()
        visited_order.append(current)
        
        # 到达终点，回溯路径
        if current == end:
            path = []
            node = end
            while node is not None:
                path.append(node)
                node = came_from[node]
            path.reverse()
            return path, visited_order
        
        for dr, dc in directions:
            nr, nc = current[0] + dr, current[1] + dc
            neighbor = (nr, nc)
            
            if not (0 <= nr < rows and 0 <= nc < cols): # 越界剪枝
                continue
            if grid[nr][nc] == 1: # 碰撞剪枝
                continue
            if neighbor in visited: # 防环剪枝（及其重要！！！防止陷入死循环）
                continue
            
            visited.add(neighbor)
            came_from[neighbor] = current
            queue.append(neighbor)
    
    return None, visited_order


# Dijkstra 算法

def dijkstra(grid, start, end):
    """
    Dijkstra 算法
    
    核心思路：
        本质上是 BFS 的"加权版本"。维护一个"到起点最短距离"的字典，
        每次从未访问节点中选择距离最小的节点进行扩展。
        
        当地图所有边权重相同（如本实验每步代价均为1）时，
        Dijkstra 和 BFS 的结果完全一致，效率也相近。
        
        Dijkstra 的优势体现在边权不同的情况（如地形代价不同），
        A* 可以看作是 Dijkstra + 启发函数的结合。
    
    局限性：
        没有启发函数，会向四周均匀扩展，在大型地图上效率低于 A*。
        对于负权边（如本题不存在）会失效。
    
    参数 & 返回值同 astar()
    """
    rows, cols = grid.shape
    
    # dist: 起点到各节点的最短距离，初始为无穷大
    dist = {start: 0}
    came_from = {} 
    # 优先队列：(距离, 节点)
    pq = [(0, start)]
    closed_set = set()
    visited_order = []
    
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    while pq:
        d, current = heapq.heappop(pq) # 从堆里弹出当前所有已知边界中，累积步数 d 最小的那个节点。
        # 元组解包。我们拿到了当前节点坐标 current，以及走到它的代价 d。
        
        if current in closed_set:
            continue
        
        closed_set.add(current)
        visited_order.append(current)
        
        if current == end:
            path = []
            node = end
            while node in came_from:
                path.append(node)
                node = came_from[node]
            path.append(start)
            path.reverse()
            return path, visited_order
        
        for dr, dc in directions:
            nr, nc = current[0] + dr, current[1] + dc
            neighbor = (nr, nc)
            
            if not (0 <= nr < rows and 0 <= nc < cols):
                continue
            if grid[nr][nc] == 1:
                continue
            if neighbor in closed_set:
                continue
            
            new_dist = dist[current] + 1  # 本实验边权均为1
            if neighbor not in dist or new_dist < dist[neighbor]:
                dist[neighbor] = new_dist
                came_from[neighbor] = current
                heapq.heappush(pq, (new_dist, neighbor))
    
    return None, visited_order