// 核心思路：使用广度优先搜索（BFS）遍历状态空间。将两个水壶当前的水量 (x, y) 看作一个状态，每次有 6 种操作分支（装满X、装满Y、清空X、清空Y、X倒Y、Y倒X） 利用哈希表记录已访问状态进行限界剪枝，避免死循环
#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        if (jug1Capacity + jug2Capacity < targetCapacity) return false;
        if (targetCapacity == 0 || targetCapacity == jug1Capacity || targetCapacity == jug2Capacity) return true;

        // 状态定义：将 (x, y) 映射为一个 long long 整数以使用哈希表
        auto hashState = [](int x, int y) -> long long {
            return (long long)x * 100000000ll + y;
        };

        unordered_set<long long> visited;
        queue<pair<int, int>> q; // FIFO 分支限界法的队列
        
        q.push({0, 0});
        visited.insert(hashState(0, 0));

        while (!q.empty()) {
            auto [currX, currY] = q.front();
            q.pop();

            if (currX == targetCapacity || currY == targetCapacity || currX + currY == targetCapacity) {
                return true;
            }

            // 6 种分支扩展
            pair<int, int> nextStates[] = {
                {jug1Capacity, currY}, // 填满 X
                {currX, jug2Capacity}, // 填满 Y
                {0, currY},            // 清空 X
                {currX, 0},            // 清空 Y
                // X 倒入 Y
                {currX - min(currX, jug2Capacity - currY), currY + min(currX, jug2Capacity - currY)},
                // Y 倒入 X
                {currX + min(currY, jug1Capacity - currX), currY - min(currY, jug1Capacity - currX)}
            };

            for (auto& state : nextStates) {
                long long stateHash = hashState(state.first, state.second);
                // 限界剪枝：只将未访问过的合法状态加入队列
                if (visited.find(stateHash) == visited.end()) {
                    visited.insert(stateHash);
                    q.push(state);
                }
            }
        }
        return false;
    }
};