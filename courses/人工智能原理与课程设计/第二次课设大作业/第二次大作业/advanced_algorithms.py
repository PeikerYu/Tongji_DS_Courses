"""
advanced_algorithms.py - 进阶算法模块
包含：人工势场法（Artificial Potential Field）
      Q-Learning（强化学习）

这两种算法用于高难度场景，作为对经典搜索算法的补充和对比。
"""

import numpy as np
import random
import matplotlib.pyplot as plt


# 人工势场法 
# 思路来源：把终点看成"引力场"，障碍看成"斥力场"，
# 机器人在合力方向上逐步移动，直到到达终点。

class ArtificialPotentialField:
    """
    人工势场法（APF）
    
    核心公式：
        引力 F_att = k_att * (goal - current)
        斥力 F_rep = k_rep * (1/d - 1/d0) * (1/d^2) * 方向向量
                     当 d < d0 时生效，d 为到障碍的距离，d0 为斥力影响范围
        合力 = F_att + sum(F_rep)
    
    优点：实时性好，适合动态环境（障碍可以移动）
    缺点：
        1. 容易陷入局部极小值（某处引力斥力恰好平衡）
        2. 路径不一定最短
        3. 在狭窄通道中可能震荡
    """
    
    def __init__(self, grid, start, end,
                 k_att=1.0,    # 引力系数
                 k_rep=2.0,    # 斥力系数
                 d0=2.5,       # 斥力有效影响范围（格子数）
                 step_size=1,  # 每步移动1格
                 max_iter=500):# 最大迭代步数（防止死循环）
        
        self.grid = grid
        self.start = start
        self.end = end
        self.k_att = k_att
        self.k_rep = k_rep
        self.d0 = d0
        self.step_size = step_size
        self.max_iter = max_iter
        
        self.rows, self.cols = grid.shape
        
        # 预计算所有障碍格子的坐标，避免每步重复遍历地图
        self.obstacles = [(r, c) for r in range(self.rows)
                          for c in range(self.cols) if grid[r][c] == 1]
    
    def _attractive_force(self, current):
        """
        计算引力：指向终点的向量。
        F_att = k_att * (goal_pos - current_pos)
        归一化处理，保证每步移动量一致。
        """
        dr = self.end[0] - current[0]
        dc = self.end[1] - current[1]
        dist = (dr ** 2 + dc ** 2) ** 0.5
        if dist < 1e-6:
            return np.array([0.0, 0.0])
        return self.k_att * np.array([dr, dc]) / dist
    
    def _repulsive_force(self, current):
        """
        计算斥力：所有在影响范围内障碍的斥力之和。
        斥力方向：从障碍指向当前位置（推开机器人）
        斥力大小：距离越近，斥力越大
        """
        F_rep = np.array([0.0, 0.0])
        
        for obs in self.obstacles:
            dr = current[0] - obs[0]
            dc = current[1] - obs[1]
            d = (dr ** 2 + dc ** 2) ** 0.5
            
            if d < 1e-6 or d > self.d0:
                continue  # 太近（在障碍内）或超出影响范围，跳过
            
            # 斥力公式：k_rep * (1/d - 1/d0) / d^2 * 方向向量
            magnitude = self.k_rep * (1.0 / d - 1.0 / self.d0) / (d ** 2)
            F_rep += magnitude * np.array([dr, dc]) / d
        
        return F_rep
    
    def _get_best_neighbor(self, current, force):
        """
        将连续势场力映射到离散格子：
        找四个邻居中，与合力方向最接近（点积最大）的合法格子。
        """
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        best_neighbor = None
        best_score = -float('inf')
        
        for dr, dc in directions:
            nr, nc = current[0] + dr, current[1] + dc
            if not (0 <= nr < self.rows and 0 <= nc < self.cols):
                continue
            if self.grid[nr][nc] == 1:
                continue
            
            # 计算邻居方向向量与合力的点积（越大越符合力的方向）
            move_dir = np.array([dr, dc], dtype=float)
            score = np.dot(force, move_dir)
            if score > best_score:
                best_score = score
                best_neighbor = (nr, nc)
        
        return best_neighbor
    
    def run(self):
        """
        执行人工势场法寻径。
        
        返回:
            path   : 路径节点列表
            success: 是否成功到达终点
        """
        current = self.start
        path = [current]
        visited_set = {current}  # 用于检测振荡（已访问节点重复出现）
        
        for _ in range(self.max_iter):
            if current == self.end:
                return path, True
            
            # 计算合力
            F_att = self._attractive_force(current)
            F_rep = self._repulsive_force(current)
            F_total = F_att + F_rep
            
            # 选择最优邻居
            next_pos = self._get_best_neighbor(current, F_total)
            
            if next_pos is None:
                # 所有邻居都是障碍，被困住了
                print("  [APF] 机器人被障碍包围，无法移动。")
                return path, False
            
            # if next_pos in visited_set and next_pos != self.end:
            #     # 检测到振荡（陷入局部极小值）
            #     # 简单处理：随机选一个合法邻居跳出
            #     directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
            #     candidates = [(current[0]+dr, current[1]+dc)
            #                   for dr, dc in directions
            #                   if 0 <= current[0]+dr < self.rows
            #                   and 0 <= current[1]+dc < self.cols
            #                   and self.grid[current[0]+dr][current[1]+dc] == 0]
            #     if candidates:
            #         next_pos = random.choice(candidates)
            #     else:
            #         print("  [APF] 陷入局部极小值且无法跳出。")
            #         return path, False
            
            current = next_pos
            path.append(current)
            visited_set.add(current)
        
        print(f"  [APF] 达到最大迭代次数 {self.max_iter}，未能到达终点。")
        return path, False


# Q-Learning 强化学习 
class QLearningAgent:
    """
    Q-Learning 强化学习寻径
    
    原理：
        将地图中每个可通行格子视为"状态"，上下左右四个方向为"动作"。
        Agent 在地图上反复探索，每次到达终点获得正奖励，
        撞障碍或走重复路获得负奖励。
        经过大量训练（episode），Q表收敛，
        最终 Agent 能根据 Q 值贪心地找到较优路径。
    
    这是强化学习（RL）的最基础形式，属于无模型（model-free）方法。
    Agent 一开始完全不知道地图结构，完全靠"试错"积累经验。
    
    核心公式（Q值更新，Bellman方程）：
        Q(s,a) ← Q(s,a) + α * [r + γ * max_a' Q(s',a') - Q(s,a)]
        
        其中：
        α (alpha)  = 学习率（0~1），控制新信息覆盖旧信息的程度
        γ (gamma)  = 折扣因子（0~1），控制对未来奖励的重视程度
        r          = 即时奖励
        s'         = 执行动作后到达的新状态
    """
    
    def __init__(self, grid, start, end,
                 alpha=0.1,      # 学习率
                 gamma=0.9,      # 折扣因子
                 epsilon=1.0,    # 初始探索率（ε-贪婪策略）
                 epsilon_min=0.01,
                 epsilon_decay=0.995,
                 n_episodes=5000,
                 max_steps=200):
        
        self.grid = grid
        self.start = start
        self.end = end
        self.alpha = alpha
        self.gamma = gamma
        self.epsilon = epsilon
        self.epsilon_min = epsilon_min
        self.epsilon_decay = epsilon_decay
        self.n_episodes = n_episodes
        self.max_steps = max_steps
        
        self.rows, self.cols = grid.shape
        self.actions = [(-1,0),(1,0),(0,-1),(0,1)]  # 上下左右
        
        # Q 表：状态 (r,c) × 动作 4 个方向
        # 初始化为 0
        self.Q = {}
        for r in range(self.rows):
            for c in range(self.cols):
                if grid[r][c] == 0:
                    self.Q[(r, c)] = [0.0] * 4
        
        self.episode_rewards = []  # 记录训练过程
    
    def _reward(self, state, next_state, done):
        """
        奖励函数设计：
        - 到达终点：+100（强正奖励，激励 Agent 找到终点）
        - 撞墙或越界：-10（惩罚无效动作）
        - 普通移动：-1（轻微惩罚，激励 Agent 走最短路）
        """
        if next_state == self.end:
            return 100
        if next_state is None:
            return -10
        return -1
    
    # def _step(self, state, action_idx):
    #     """
    #     执行一个动作，返回 (新状态, 奖励, 是否结束)。
    #     若动作撞墙/越界，原地不动，给负奖励。
    #     """
    #     dr, dc = self.actions[action_idx]
    #     nr, nc = state[0] + dr, state[1] + dc
        
    #     # 边界或障碍检查
    #     if not (0 <= nr < self.rows and 0 <= nc < self.cols):
    #         return state, -10, False  # 越界，原地
    #     if self.grid[nr][nc] == 1:
    #         return state, -10, False  # 撞墙，原地
        
    #     next_state = (nr, nc)
    #     done = (next_state == self.end)
    #     reward = 100 if done else -1
    #     return next_state, reward, done
    def _step(self, state, action_idx):
        """
        执行一个动作，返回 (新状态, 奖励, 是否结束)。
        改进：引入势能奖励塑形 (Potential-based Reward Shaping)
        """
        dr, dc = self.actions[action_idx]
        nr, nc = state[0] + dr, state[1] + dc
        
        # 边界或障碍检查
        if not (0 <= nr < self.rows and 0 <= nc < self.cols):
            return state, -10, False  # 越界，原地
        if self.grid[nr][nc] == 1:
            return state, -10, False  # 撞墙，原地
        
        next_state = (nr, nc)
        done = (next_state == self.end)
        
        # 核心改进：势能奖励塑形计算
        if done:
            reward = 100
        else:
            # 计算旧状态和新状态到终点的曼哈顿距离
            old_dist = abs(state[0] - self.end[0]) + abs(state[1] - self.end[1])
            new_dist = abs(next_state[0] - self.end[0]) + abs(next_state[1] - self.end[1])
            
            # 基础步数惩罚 -1，加上距离势能反馈（向终点走+2，远离终点-2）
            reward = -1 + 2.0 * (old_dist - new_dist)
            
        return next_state, reward, done
    
    def _choose_action(self, state):
        """
        ε-贪婪策略：
        - 以 ε 的概率随机探索（避免陷入局部最优）
        - 以 1-ε 的概率选择当前 Q 值最大的动作（利用已有知识）
        训练初期 ε 大（多探索），后期 ε 小（多利用）。
        """
        if random.random() < self.epsilon:
            return random.randint(0, 3)
        return int(np.argmax(self.Q[state]))
    
    def train(self):
        """训练 Q-Learning Agent"""
        print(f"  开始训练 Q-Learning，共 {self.n_episodes} 个 episode...")
        
        for ep in range(self.n_episodes):
            state = self.start
            total_reward = 0
            
            for _ in range(self.max_steps):
                action = self._choose_action(state)
                next_state, reward, done = self._step(state, action)
                total_reward += reward
                
                # Q 值更新（Bellman方程）
                old_q = self.Q[state][action]
                if next_state in self.Q:
                    max_next_q = max(self.Q[next_state])
                else:
                    max_next_q = 0
                
                self.Q[state][action] = old_q + self.alpha * (
                    reward + self.gamma * max_next_q - old_q
                )
                
                state = next_state
                
                if done:
                    break
            
            self.episode_rewards.append(total_reward)
            
            # ε 衰减
            if self.epsilon > self.epsilon_min:
                self.epsilon *= self.epsilon_decay
            
            if (ep + 1) % 500 == 0:
                avg_reward = np.mean(self.episode_rewards[-500:])
                print(f"    Episode {ep+1}/{self.n_episodes}  "
                      f"ε={self.epsilon:.3f}  近500轮平均奖励={avg_reward:.1f}")
        
        print("  训练完成！")
    
    def get_path(self):
        """
        训练后，用贪婪策略（始终选 Q 值最大动作）推导最终路径。
        """
        state = self.start
        path = [state]
        visited = {state}
        
        for _ in range(self.max_steps):
            if state == self.end:
                return path
            if state not in self.Q:
                break
            
            action = int(np.argmax(self.Q[state]))
            dr, dc = self.actions[action]
            nr, nc = state[0] + dr, state[1] + dc
            next_state = (nr, nc)
            
            if next_state in visited or self.grid[nr][nc] == 1:
                break  # 陷入循环或撞墙，训练可能还不充分
            
            path.append(next_state)
            visited.add(next_state)
            state = next_state
        
        return path
    
    def plot_training_curve(self, save_path=None):
        """绘制训练奖励曲线，观察 Agent 的学习进度"""
        fig, ax = plt.subplots(figsize=(10, 4))
        
        # 平滑处理：每100个 episode 取平均
        window = 100
        smoothed = [np.mean(self.episode_rewards[max(0, i-window):i+1])
                    for i in range(len(self.episode_rewards))]
        
        ax.plot(self.episode_rewards, alpha=0.3, color='steelblue', label='每轮奖励')
        ax.plot(smoothed, color='navy', linewidth=2, label=f'{window}轮滑动平均')
        ax.axhline(y=0, color='gray', linestyle='--', linewidth=0.8)
        ax.set_xlabel('训练轮次 (Episode)')
        ax.set_ylabel('累计奖励')
        ax.set_title('Q-Learning 训练曲线')
        ax.legend()
        ax.grid(True, alpha=0.3)
        
        plt.tight_layout()
        if save_path:
            plt.savefig(save_path, dpi=150)
        plt.show()