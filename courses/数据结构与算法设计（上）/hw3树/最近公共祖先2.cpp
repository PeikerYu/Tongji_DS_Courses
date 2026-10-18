#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int parent; // 双亲索引
};

struct Tree {
    int n;
    TreeNode *nodes;
};

// 初始化树
Tree createTree(int n) {
    Tree t;
    t.n = n;
    t.nodes = new TreeNode[n];
    for (int i = 0; i < n; i++)
        t.nodes[i].parent = -1; // 根节点初始为-1
    return t;
}

// 计算每个节点深度，根节点深度为0
void computeDepth(Tree &tree, vector<int> &depth) {
    depth.resize(tree.n);
    for (int i = 0; i < tree.n; i++) {
        int d = 0;
        int cur = i;
        while (tree.nodes[cur].parent != -1) {
            cur = tree.nodes[cur].parent;
            d++;
        }
        depth[i] = d;
    }
}

// 递归版求最近公共祖先
int findLCA(Tree &tree, vector<int> &depth, int x, int y) {
    // 如果深度不同，让深的节点上移
    if (depth[x] > depth[y]) return findLCA(tree, depth, tree.nodes[x].parent, y);
    if (depth[y] > depth[x]) return findLCA(tree, depth, x, tree.nodes[y].parent);

    // 深度相同，如果相等则返回当前节点
    if (x == y) return x;

    // 同时向上递归
    return findLCA(tree, depth, tree.nodes[x].parent, tree.nodes[y].parent);
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, m;
        cin >> n >> m;
        Tree tree = createTree(n);

        // 读取边信息，构建父子关系
        for (int j = 0; j < n - 1; j++) {
            int parent, child;
            cin >> parent >> child;
            tree.nodes[child - 1].parent = parent - 1; // 转为0-based索引
        }

        // 计算每个节点深度
        vector<int> depth;
        computeDepth(tree, depth);

        // 处理查询
        for (int k = 0; k < m; k++) {
            int x, y;
            cin >> x >> y;
            int ans = findLCA(tree, depth, x - 1, y - 1);
            cout << ans + 1 << endl;
        }

        delete[] tree.nodes;
    }
    return 0;
}
