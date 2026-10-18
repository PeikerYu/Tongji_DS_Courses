"""
visualize.py - 可视化模块（科研配色版）
科研配色方案：低饱和度、高辨识度，风格接近 Nature/IEEE 论文插图。
"""

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.patches as mpatches
from matplotlib import rcParams

rcParams['font.sans-serif'] = ['Microsoft YaHei', 'SimHei', 'Noto Sans CJK SC', 'DejaVu Sans']
rcParams['axes.unicode_minus'] = False
rcParams['figure.dpi'] = 120

# ── 科研配色 Palette ────────────────────────────────────────────────────
# 低饱和、色盲友好，参考 Nature / IEEE 论文风格
C = {
    'bg'      : '#FAFAF8',
    'free'    : [0.965, 0.962, 0.957],  # 暖白：空地
    'obstacle': [0.318, 0.380, 0.455],  # 石板灰：障碍
    'visited' : [0.722, 0.843, 0.902],  # 雾霾蓝：已探索
    'path'    : [0.937, 0.702, 0.220],  # 琥珀金：路径
    'start'   : [0.255, 0.490, 0.710],  # 钢青：起点
    'end'     : [0.227, 0.624, 0.506],  # 鼠尾草绿：终点
}

def _build_rgb(grid, visited_set, path_set, start, end):
    rows, cols = grid.shape
    img = np.full((rows, cols, 3), C['free'])
    for r in range(rows):
        for c in range(cols):
            p = (r, c)
            if grid[r][c] == 1:     img[r, c] = C['obstacle']
            elif p in path_set:     img[r, c] = C['path']
            elif p in visited_set:  img[r, c] = C['visited']
    img[start[0], start[1]] = C['start']
    img[end[0],   end[1]]   = C['end']
    return img

def _polish_ax(ax, rows, cols):
    for x in range(cols + 1):
        ax.axvline(x - 0.5, color='white', lw=1.8, zorder=2)
    for y in range(rows + 1):
        ax.axhline(y - 0.5, color='white', lw=1.8, zorder=2)
    ax.set_xticks([])
    ax.set_yticks([])
    for sp in ax.spines.values():
        sp.set_visible(False)

def _label_se(ax, start, end, fs=14):
    kw = dict(ha='center', va='center', fontweight='bold', color='white', zorder=5)
    ax.text(start[1], start[0], 'S', fontsize=fs, **kw)
    ax.text(end[1],   end[0],   'E', fontsize=fs, **kw)

def _legend_handles():
    s = dict(edgecolor='none')
    return [
        mpatches.Patch(facecolor=C['obstacle'], label='障碍区域',   **s),
        mpatches.Patch(facecolor=C['visited'],  label='已探索区域', **s),
        mpatches.Patch(facecolor=C['path'],     label='最短路径',   **s),
        mpatches.Patch(facecolor=C['start'],    label='起点 (S)',   **s),
        mpatches.Patch(facecolor=C['end'],      label='终点 (E)',   **s),
    ]

def plot_static(grid, path, visited_order, start, end,
                title='路径搜索结果', save_path=None):
    fig, ax = plt.subplots(figsize=(7, 5.5))
    fig.patch.set_facecolor(C['bg'])
    ax.set_facecolor(C['bg'])
    img = _build_rgb(grid, set(visited_order), set(path) if path else set(), start, end)
    ax.imshow(img, interpolation='nearest', aspect='equal')
    _polish_ax(ax, *grid.shape)
    _label_se(ax, start, end)
    plen = len(path) - 1 if path else '无法到达'
    ax.set_title(title, fontsize=15, fontweight='bold', pad=12, color='#1a1a2e')
    ax.set_xlabel(f'探索节点数：{len(visited_order)}   ·   路径长度：{plen} 步',
                  fontsize=11, labelpad=8, color='#555555')
    ax.legend(handles=_legend_handles(), loc='center left',
              bbox_to_anchor=(1.03, 0.5), fontsize=10, frameon=False)
    fig.tight_layout()
    if save_path:
        fig.savefig(save_path, dpi=180, bbox_inches='tight', facecolor=C['bg'])
    plt.show()

def animate_search(grid, path, visited_order, start, end,
                   title='搜索过程', interval=110, save_gif=None):
    rows, cols = grid.shape
    path_set = set(path) if path else set()
    n_vis = len(visited_order)
    n_total = n_vis + 25

    fig, ax = plt.subplots(figsize=(7, 5.5))
    fig.patch.set_facecolor(C['bg'])

    def update(f):
        ax.clear()
        ax.set_facecolor(C['bg'])
        if f < n_vis:
            vis  = set(visited_order[:f + 1])
            pset = set()
            sub  = f'搜索中  ·  已扩展节点：{f + 1}'
        else:
            vis  = set(visited_order)
            pset = path_set
            sub  = f'完成  ·  探索 {n_vis} 节点  ·  路径 {len(path)-1 if path else "N/A"} 步'
        img = _build_rgb(grid, vis, pset, start, end)
        ax.imshow(img, interpolation='nearest', aspect='equal')
        _polish_ax(ax, rows, cols)
        _label_se(ax, start, end)
        ax.set_title(title, fontsize=14, fontweight='bold', pad=10, color='#1a1a2e')
        ax.set_xlabel(sub, fontsize=11, labelpad=8, color='#555555')
        ax.legend(handles=_legend_handles(), loc='center left',
                  bbox_to_anchor=(1.03, 0.5), fontsize=10, frameon=False)

    ani = animation.FuncAnimation(fig, update, frames=n_total,
                                  interval=interval, repeat=False)
    if save_gif:
        ani.save(save_gif, writer='pillow', fps=9)
    fig.tight_layout()
    plt.show()
    return ani

def compare_plot(grid, results, start, end, save_path='compare_result.png'):
    n = len(results)
    fig, axes = plt.subplots(1, n, figsize=(5.5 * n, 5.2))
    if n == 1:
        axes = [axes]
    fig.patch.set_facecolor(C['bg'])
    for ax, (name, (path, visited)) in zip(axes, results.items()):
        ax.set_facecolor(C['bg'])
        img = _build_rgb(grid, set(visited), set(path) if path else set(), start, end)
        ax.imshow(img, interpolation='nearest', aspect='equal')
        _polish_ax(ax, *grid.shape)
        _label_se(ax, start, end, fs=13)
        plen = len(path) - 1 if path else '—'
        ax.set_title(name, fontsize=14, fontweight='bold', pad=8, color='#1a1a2e')
        ax.set_xlabel(f'探索 {len(visited)} 节点  ·  路径 {plen} 步',
                      fontsize=10, labelpad=6, color='#555555')
    fig.legend(handles=_legend_handles(), loc='lower center', ncol=5,
               bbox_to_anchor=(0.5, -0.06), fontsize=11, frameon=False)
    fig.suptitle('算法搜索效率对比', fontsize=17, fontweight='bold',
                 y=1.03, color='#1a1a2e')
    fig.tight_layout()
    fig.savefig(save_path, dpi=180, bbox_inches='tight', facecolor=C['bg'])
    plt.show()