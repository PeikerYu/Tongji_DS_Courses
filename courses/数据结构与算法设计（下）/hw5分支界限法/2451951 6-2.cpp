// 核心思路：采用优先队列的分支限界法（等同于 Dijkstra 算法）维护一个二维 dist 数组记录起点到各点的最小体力消耗，每次从优先队列中取出当前最大高度差最小的点进行上下左右分支扩展 若新路径消耗更小则更新并入队，提前剪枝掉劣质路径
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>

using namespace std;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();
        
        // 优先队列：{当前最大体力消耗, x坐标, y坐标} 使用小根堆
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        
        // dist 数组用于限界剪枝
        vector<vector<int>> dist(rows, vector<int>(cols, 1e9));
        
        pq.push({0, 0, 0});
        dist[0][0] = 0;
        
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!pq.empty()) {
            auto [effort, x, y] = pq.top();
            pq.pop();
            
            // 如果到达终点，因为是优先队列，当前的一定是全局最小
            if (x == rows - 1 && y == cols - 1) {
                return effort;
            }
            
            // 限界：如果出队时发现有更优路径已经到达过该点，则废弃当前分支
            if (effort > dist[x][y]) continue;
            
            // 分支扩展
            for (auto& dir : dirs) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                    int next_effort = max(effort, abs(heights[x][y] - heights[nx][ny]));
                    // 限界剪枝条件：只有找到更小的体力消耗才入队
                    if (next_effort < dist[nx][ny]) {
                        dist[nx][ny] = next_effort;
                        pq.push({next_effort, nx, ny});
                    }
                }
            }
        }
        return 0;
    }
};