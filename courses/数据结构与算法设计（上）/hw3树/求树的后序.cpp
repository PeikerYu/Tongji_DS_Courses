#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
  功能：计算有序树与其左孩子-右兄弟表示的二叉树的最大深度（均按边计）
  算法思想：
    - 输入是深度优先遍历方向字符串 'd' (down) / 'u' (up)
    - 原树深度 h1 通过计数器统计当前深度即可；
    - 转换后二叉树深度 h2 用递归模拟构造过程，
      每次进入一个新子节点时，深度 = 父深度 + 已有子节点数 + 1，
      递归过程中更新全局最大深度。
  数据结构设计：
    使用 TreeNode 结构体保存“当前节点的状态信息”，包括：
      int depth;        // 当前节点在原树中的深度（用于理解，可选）
      int fatherDepth;  // 父节点在二叉树表示中的深度
      int childCount;   // 当前节点的孩子计数
    注意：该结构体并不保存指针关系，递归栈天然维护了父子结构。
*/

struct TreeNode {
    int depth;        // 当前节点的深度（辅助理解）
    int fatherDepth;  // 父节点在二叉树中的深度
    int childCount;   // 当前节点的已处理孩子数量
};

// 全局变量
string s;    // 输入序列
int bdp = 0; // 转换后二叉树的最大深度（按边计）

// 深度优先递归函数
void dfs(int &i, int fatherDepth) {
    // 显式创建一个结构体变量（非构造函数）
    TreeNode node;
    node.depth = 0;          // 该字段可理解为逻辑深度，不参与计算
    node.fatherDepth = fatherDepth;
    node.childCount = 0;

    // 更新二叉树深度
    bdp = max(bdp, node.fatherDepth);

    // 遍历字符串直到遇到 'u' 返回
    while (i < (int)s.size()) {
        if (s[i] == 'd') {
            // 第 childCount+1 个孩子的深度（右兄弟转换公式）
            int childDepth = node.fatherDepth + node.childCount + 1;
            node.childCount++;

            ++i;             // 向下进入新节点
            dfs(i, childDepth); // 递归解析子树
        }
        else if (s[i] == 'u') {
            ++i;             // 返回上一层
            return;
        }
        else {
            ++i;             // 非法字符安全跳过
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNo = 0;

    while (cin >> s) {
        if (!s.empty() && s[0] == '#') break;

        // ---------- 计算原树的深度 h1 ----------
        int curDepth = 0, h1 = 0;
        for (char c : s) {
            if (c == 'd') {
                curDepth++;
                h1 = max(h1, curDepth);
            } else if (c == 'u') {
                curDepth--;
            }
        }

        // ---------- 计算转换后二叉树的深度 h2 ----------
        bdp = 0;
        int idx = 0;
        dfs(idx, 0); // 根节点的父深度记为 0

        ++caseNo;
        cout << "Tree " << caseNo << ": " << h1 << " => " << bdp << "\n";
    }

    return 0;
}
