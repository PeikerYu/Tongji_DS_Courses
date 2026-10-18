//图的最大路径价值
// 核心思路：从 0 出发 DFS 走图，路径必须回到 0 且总时间不超过 maxTime。每个节点价值只加一次，用 seen 数组记录是否已计入；每到一个节点若回到 0 就更新答案，然后回溯撤销访问标记。
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n = values.size();
        vector<vector<pair<int, int>>> g(n); // g[u] = {邻居, 耗时}
        for (auto& e : edges) {
            g[e[0]].push_back({e[1], e[2]});
            g[e[1]].push_back({e[0], e[2]});
        }

        int ans = 0;
        vector<int> seen(n, 0);
        seen[0] = 1;
        dfs(g, values, 0, values[0], maxTime, seen, ans);
        return ans;
    }

    void dfs(vector<vector<pair<int, int>>>& g, vector<int>& values,
             int u, int quality, int time, vector<int>& seen, int& ans) {
        if (u == 0) ans = max(ans, quality);

        for (auto& p : g[u]) {
            int v = p.first, cost = p.second;
            if (cost > time) continue;

            int add = (seen[v] == 0) ? values[v] : 0;
            seen[v]++;
            dfs(g, values, v, quality + add, time - cost, seen, ans);
            seen[v]--; // 回溯
        }
    }
};
