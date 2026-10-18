// 供水管网最小生成树
// 用Kruskal算法，按边权排序后用并查集维护连通性
// 时间复杂度：O(m log m)，m为可铺设管道数量

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

int par[1001], rnk[1001];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        par[i] = i;
        rnk[i] = 0;
    }
}

int find(int x) {
    if (par[x] != x) par[x] = find(par[x]);
    return par[x];
}

// 合并两个集合，返回是否成功（false代表已连通，加这条边会形成环）
bool unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return false;
    if (rnk[x] < rnk[y]) swap(x, y);
    par[y] = x;
    if (rnk[x] == rnk[y]) rnk[x]++;
    return true;
}

int main() {
    int n, m;
    cout << "请输入楼栋数n和可铺设管道数m：";
    cin >> n >> m;
    cout << "请依次输入每条管道的两端楼栋编号及铺设长度（u v w）：\n";

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    // 按管道长度从小到大排序
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    init(n);

    int total = 0, cnt = 0;
    vector<Edge> mst;

    for (auto& e : edges) {
        if (unite(e.u, e.v)) {
            mst.push_back(e);
            total += e.w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }

    if (cnt < n - 1) {
        cout << "无法使所有楼栋连通（图不连通）\n";
        return 0;
    }

    cout << "\n最优供水管网方案（最小生成树）：\n";
    cout << "铺设管道：\n";
    for (auto& e : mst)
        cout << "  楼栋" << e.u << " <---> 楼栋" << e.v << "  长度：" << e.w << "\n";
    cout << "总铺设管道长度（最低造价）：" << total << "\n";

    return 0;
}
