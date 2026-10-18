"""
windy_abyss.py
"风口深渊" 场景 — A* vs Q-Learning 对比可视化
科研配色，Noto CJK 字体，布局参考 Nature 论文双栏插图风格
"""

import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib.patheffects as pe
from matplotlib import font_manager, rcParams
import random
import os

# ─── 字体 ────────────────────────────────────────────────────────────────────
def setup_fonts():
    # 兼容 Linux/Windows 的常见中文字体路径，找不到时回退系统字体。
    candidates = [
        '/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc',
        'C:/Windows/Fonts/msyh.ttc',
        'C:/Windows/Fonts/simhei.ttf',
    ]
    for font_path in candidates:
        if os.path.exists(font_path):
            font_manager.fontManager.addfont(font_path)

    rcParams['font.sans-serif'] = [
        'Noto Sans CJK SC', 'Microsoft YaHei', 'SimHei', 'DejaVu Sans'
    ]


setup_fonts()
rcParams['axes.unicode_minus'] = False

# ─── 科研配色 (色盲友好，参考 Wong 2011 Nature Methods) ─────────────────────
PAL = {
    'bg'      : '#FAFAF8',
    'bridge'  : '#EEF2F7',       # 桥面：冷灰白
    'wall'    : '#4A5568',        # 实体墙：深石板灰
    'abyss'   : '#FFF0F0',        # 深渊：极淡警示红
    'abyss_hatch': '#FFCDD2',     # 深渊斜线颜色
    'safe_path': '#2166AC',       # Q-Learning 路径：钴蓝
    'risk_path': '#B2182B',       # A* 路径：深红
    'wind'     : '#F4A261',       # 阵风箭头：琥珀橙
    'fall'     : '#E63946',       # 坠落虚线
    'label_bg' : '#2D3748',       # 标注框背景
    'grid_line': '#CBD5E0',       # 网格线
    'text_main': '#1A202C',       # 主文字
    'text_sub' : '#4A5568',       # 辅助文字
    'accent'   : '#553C9A',       # 强调色（紫）
}

# ─── 环境定义 ─────────────────────────────────────────────────────────────────
class WindyAbyssEnv:
    def __init__(self):
        self.rows, self.cols = 5, 12
        self.start = (2, 0)
        self.end   = (2, 11)
        # grid: 0=可通行  1=实体墙  2=深渊
        self.grid = np.zeros((self.rows, self.cols), dtype=int)
        self.grid[0, :] = 1          # 顶部实体墙（保护屏障）
        self.grid[3:5, 1:11] = 2     # 下方深渊
        self.actions = [(-1,0),(1,0),(0,-1),(0,1)]

    def step(self, state, action_idx):
        dr, dc = self.actions[action_idx]
        nr, nc = state[0]+dr, state[1]+dc
        # 20% 概率向下偏移（水平移动时）
        if random.random() < 0.2 and action_idx in [2, 3]:
            nr += 1
        nr = max(0, min(self.rows-1, nr))
        nc = max(0, min(self.cols-1, nc))
        if self.grid[nr, nc] == 1:
            nr, nc = state
        next_s = (nr, nc)
        if self.grid[nr, nc] == 2: return self.start, -100, True
        if next_s == self.end:     return next_s,  100,  True
        return next_s, -1, False

# A*：走几何最短路（中间直线桥）
def get_astar_path(env):
    return [(2, c) for c in range(12)]

# Q-Learning：训练 + 贪婪推断
def train_q(env, episodes=5000):
    Q = np.zeros((env.rows, env.cols, 4))
    for ep in range(episodes):
        state = env.start
        eps = max(0.01, 1.0 * (0.995**ep))
        for _ in range(120):
            a = (random.randint(0,3) if random.random()<eps
                 else int(np.argmax(Q[state])))
            ns, r, done = env.step(state, a)
            Q[state][a] += 0.1*(r + 0.95*np.max(Q[ns]) - Q[state][a])
            state = ns
            if done: break
    return Q

def get_q_path(env, Q):
    state = env.start
    path  = [state]
    seen  = {state}
    for _ in range(30):
        if state == env.end: break
        a  = int(np.argmax(Q[state]))
        dr, dc = env.actions[a]
        nr, nc = state[0]+dr, state[1]+dc
        nr = max(0, min(env.rows-1, nr))
        nc = max(0, min(env.cols-1, nc))
        ns = (nr, nc)
        if ns in seen or env.grid[nr,nc] in [1,2]: break
        path.append(ns)
        seen.add(ns)
        state = ns
    return path

# ─── 绘图核心 ─────────────────────────────────────────────────────────────────
def draw_map(ax, env, path, path_color, panel_label,
             show_wind=False, show_fall=False, show_shield=False):
    rows, cols = env.rows, env.cols
    ax.set_facecolor(PAL['bg'])

    # ── 格子底色 ──────────────────────────────────────────────────────────────
    for r in range(rows):
        for c in range(cols):
            v = env.grid[r, c]
            if v == 1:
                fc = PAL['wall']
            elif v == 2:
                fc = PAL['abyss']
            else:
                fc = PAL['bridge']
            rect = plt.Rectangle((c-0.5, r-0.5), 1, 1,
                                  facecolor=fc,
                                  edgecolor=PAL['grid_line'], lw=0.8, zorder=1)
            ax.add_patch(rect)
            # 深渊斜线填充
            if v == 2:
                hatch = plt.Rectangle((c-0.5, r-0.5), 1, 1,
                                      facecolor='none',
                                      edgecolor=PAL['abyss_hatch'],
                                      hatch='/////', lw=0, zorder=2)
                ax.add_patch(hatch)

    # ── 深渊标注 ─────────────────────────────────────────────────────────────
    ax.text(5.5, 3.8, '深  渊  区  域', ha='center', va='center',
            fontsize=11, color='#C62828', alpha=0.55,
            fontweight='bold', zorder=3)

    # ── 阵风标注（A* 面板）────────────────────────────────────────────────────
    if show_wind:
        for c in [3, 5, 7, 9]:
            ax.annotate('', xy=(c, 2.55), xytext=(c, 1.9),
                        arrowprops=dict(arrowstyle='->', color=PAL['wind'],
                                        lw=2.2, mutation_scale=18), zorder=8)
        ax.text(5.5, 1.55,
                '↓  20% 概率向下阵风  ↓',
                ha='center', va='center', fontsize=10.5,
                color=PAL['wind'], fontweight='bold', zorder=8)

    # ── 坠落标注（A* 面板）────────────────────────────────────────────────────
    if show_fall:
        ax.plot([6, 6], [2.1, 2.85], color=PAL['fall'],
                ls='--', lw=2.2, zorder=7)
        ax.annotate('', xy=(6, 2.88), xytext=(6, 2.1),
                    arrowprops=dict(arrowstyle='->', color=PAL['fall'],
                                    lw=1.8, mutation_scale=14), zorder=7)
        ax.text(6.4, 2.5, '随机坠落\n进入深渊', ha='left', va='center',
                fontsize=9, color=PAL['fall'], fontweight='bold',
                linespacing=1.4, zorder=8)

    # ── 防护屏障标注（Q-Learning 面板）────────────────────────────────────────
    if show_shield:
        # 在实体墙上加 "防护屏障" 括号标注
        ax.annotate('', xy=(-0.5, 0.5), xytext=(11.5, 0.5),
                    arrowprops=dict(arrowstyle='<->', color=PAL['accent'],
                                    lw=1.5), zorder=8)
        ax.text(5.5, 0.5, '  实体墙 · 天然防风屏障  ',
                ha='center', va='center', fontsize=10,
                color=PAL['accent'], fontweight='bold',
                bbox=dict(facecolor=PAL['bg'], edgecolor='none', pad=2),
                zorder=9)

    # ── 路径绘制 ──────────────────────────────────────────────────────────────
    xs = [p[1] for p in path]
    ys = [p[0] for p in path]
    ax.plot(xs, ys, color=path_color, lw=3.5, zorder=6,
            solid_capstyle='round', solid_joinstyle='round')
    ax.scatter(xs[1:-1], ys[1:-1], s=38, color=path_color,
               edgecolors='white', lw=1.4, zorder=7)

    # 起点 / 终点圆形标记
    for (r, c), label in [(env.start, 'S'), (env.end, 'E')]:
        circle = plt.Circle((c, r), 0.38, color=PAL['label_bg'],
                             zorder=9, ec='white', lw=1.5)
        ax.add_patch(circle)
        ax.text(c, r, label, ha='center', va='center',
                fontsize=12, fontweight='bold', color='white', zorder=10)

    # ── 坐标轴清理 ────────────────────────────────────────────────────────────
    ax.set_xlim(-0.65, cols - 0.35)
    ax.set_ylim(-0.6, rows - 0.4)
    ax.invert_yaxis()
    ax.set_xticks([])
    ax.set_yticks([])
    for sp in ax.spines.values():
        sp.set_visible(False)

    # 外边框（细线，显得规整）
    border = plt.Rectangle((-0.5, -0.5), cols, rows,
                            fill=False, edgecolor='#B0BEC5', lw=1.5, zorder=11)
    ax.add_patch(border)

    # 面板编号
    ax.text(-0.45, -0.35, panel_label,
            ha='left', va='top', fontsize=12,
            fontweight='bold', color=PAL['text_main'], zorder=12)


# ─── 主图合成 ─────────────────────────────────────────────────────────────────
def make_figure(env, astar_path, q_path, save_path):
    fig = plt.figure(figsize=(13, 9.5), facecolor=PAL['bg'])

    # ── 总标题 ────────────────────────────────────────────────────────────────
    fig.text(0.5, 0.985,
             '不确定性环境下的策略差异："风口深渊" 验证场景',
             ha='center', va='top',
             fontsize=16, fontweight='bold', color=PAL['text_main'])
    fig.text(0.5, 0.955,
             '实验说明：桥上存在 20% 向下阵风，掉入深渊重置并扣 100 分；'
             '上方实体墙可作防风屏障。',
             ha='center', va='top',
             fontsize=11, color=PAL['text_sub'])

    # ── 子图布局：上下两个地图 + 右侧注释栏 ──────────────────────────────────
    # [地图列] [注释列]
    gs = fig.add_gridspec(2, 2, left=0.04, right=0.98,
                          top=0.86, bottom=0.10,
                          hspace=0.42, wspace=0.18,
                          width_ratios=[3.2, 1])

    ax_top   = fig.add_subplot(gs[0, 0])
    ax_bot   = fig.add_subplot(gs[1, 0])
    ax_note1 = fig.add_subplot(gs[0, 1])
    ax_note2 = fig.add_subplot(gs[1, 1])

    # ── 上图：A* ──────────────────────────────────────────────────────────────
    draw_map(ax_top, env, astar_path, PAL['risk_path'], '(a)',
             show_wind=True, show_fall=True)
    ax_top.set_title(
        'A* 算法：几何最短路（无视环境随机性）',
        fontsize=13, fontweight='bold', pad=10,
        color=PAL['risk_path'])

    # ── 下图：Q-Learning ─────────────────────────────────────────────────────
    draw_map(ax_bot, env, q_path, PAL['safe_path'], '(b)',
             show_shield=True)
    ax_bot.set_title(
        'Q-Learning：风险规避策略（贴墙走安全上路）',
        fontsize=13, fontweight='bold', pad=10,
        color=PAL['safe_path'])

    # ── 右侧注释：A* ─────────────────────────────────────────────────────────
    for sp in ax_note1.spines.values(): sp.set_visible(False)
    ax_note1.set_xticks([]); ax_note1.set_yticks([])
    ax_note1.set_facecolor(PAL['bg'])

    note1_lines = [
        ('策略逻辑', PAL['text_main'], 'bold', 11),
        ('走几何最短路', PAL['text_sub'], 'normal', 10),
        ('f(n) = g(n) + h(n)', '#888888', 'normal', 9),
        ('', PAL['bg'], 'normal', 8),
        ('风险分析', PAL['text_main'], 'bold', 11),
        ('路径跨越深渊区', '#C62828', 'normal', 10),
        ('每步 20% 坠落概率', '#C62828', 'normal', 10),
        ('期望坠落次数 ≈ 2 次', '#C62828', 'normal', 10),
        ('', PAL['bg'], 'normal', 8),
        ('适用条件', PAL['text_main'], 'bold', 11),
        ('[OK] 环境完全确定', PAL['text_sub'], 'normal', 10),
        ('[OK] 无随机干扰', PAL['text_sub'], 'normal', 10),
        ('[NO] 随机物理环境', '#C62828', 'normal', 10),
    ]
    y = 0.95
    for txt, col, wt, fs in note1_lines:
        ax_note1.text(0.05, y, txt, transform=ax_note1.transAxes,
                      ha='left', va='top', fontsize=fs,
                      color=col, fontweight=wt)
        y -= 0.074

    # 右侧注释：Q-Learning
    for sp in ax_note2.spines.values(): sp.set_visible(False)
    ax_note2.set_xticks([]); ax_note2.set_yticks([])
    ax_note2.set_facecolor(PAL['bg'])

    note2_lines = [
        ('策略逻辑', PAL['text_main'], 'bold', 11),
        ('最大化期望累计奖励', PAL['text_sub'], 'normal', 10),
        ('Q ← Q + α(r+γQ′−Q)', '#888888', 'normal', 9),
        ('', PAL['bg'], 'normal', 8),
        ('风险分析', PAL['text_main'], 'bold', 11),
        ('绕行上方安全通道', '#1565C0', 'normal', 10),
        ('靠近实体墙防风偏', '#1565C0', 'normal', 10),
        ('坠落概率 ≈ 0%', '#1565C0', 'normal', 10),
        ('', PAL['bg'], 'normal', 8),
        ('适用条件', PAL['text_main'], 'bold', 11),
        ('[OK] 环境完全确定', PAL['text_sub'], 'normal', 10),
        ('[OK] 随机物理干扰', '#1565C0', 'normal', 10),
        ('[OK] 动态/部分未知', '#1565C0', 'normal', 10),
    ]
    y = 0.95
    for txt, col, wt, fs in note2_lines:
        ax_note2.text(0.05, y, txt, transform=ax_note2.transAxes,
                      ha='left', va='top', fontsize=fs,
                      color=col, fontweight=wt)
        y -= 0.074

    # ── 底部图例 ──────────────────────────────────────────────────────────────
    legend_items = [
        mpatches.Patch(facecolor=PAL['bridge'],  edgecolor=PAL['grid_line'], label='可通行区域'),
        mpatches.Patch(facecolor=PAL['wall'],    edgecolor='none',           label='实体墙（防风屏障）'),
        mpatches.Patch(facecolor=PAL['abyss'],   edgecolor=PAL['abyss_hatch'], hatch='/////', label='深渊区（高风险）'),
        mpatches.Patch(facecolor=PAL['risk_path'], edgecolor='none',         label='A* 路径（高风险）'),
        mpatches.Patch(facecolor=PAL['safe_path'], edgecolor='none',         label='Q-Learning 路径（安全）'),
    ]
    fig.legend(handles=legend_items, loc='lower center', ncol=5,
               bbox_to_anchor=(0.5, 0.01), fontsize=10.5,
               frameon=False, handlelength=1.4, handletextpad=0.5)

    save_dir = os.path.dirname(save_path)
    if save_dir:
        os.makedirs(save_dir, exist_ok=True)
    fig.savefig(save_path, dpi=200, bbox_inches='tight', facecolor=PAL['bg'])
    print(f'图已保存：{save_path}')


# ─── 主程序 ──────────────────────────────────────────────────────────────────
if __name__ == '__main__':
    random.seed(42)
    np.random.seed(42)

    env = WindyAbyssEnv()
    print('训练 Q-Learning...')
    Q = train_q(env)
    print('训练完成。')

    astar_path = get_astar_path(env)
    q_path     = get_q_path(env, Q)

    print(f'A* 路径：{astar_path}')
    print(f'Q路径  ：{q_path}')

    output_path = os.path.join(os.path.dirname(__file__), 'windy_abyss.png')
    make_figure(env, astar_path, q_path, output_path)