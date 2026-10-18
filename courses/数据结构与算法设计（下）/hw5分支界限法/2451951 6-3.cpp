// 核心思路：问题等价于从数组中挑出和为 sum/2 的子集。采用 DFS 构建状态空间树，利用记忆化数组（memo）进行查重限界
// 为了加速剪枝，先将数组降序排列，以便快速触发“当前和越界”的终止条件
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<vector<int>> memo;

    bool dfs(const vector<int>& nums, int index, int current_sum, int target) {
        if (current_sum == target) return true;
        
        // 限界剪枝 1：越界
        if (current_sum > target || index >= nums.size()) return false;
        
        // 限界剪枝 2：记忆化（查重），-1表示未计算，0表示false，1表示true
        if (memo[index][current_sum] != -1) {
            return memo[index][current_sum] == 1;
        }

        // 分支：选当前数字
        if (dfs(nums, index + 1, current_sum + nums[index], target)) {
            return true;
        }
        
        // 分支：不选当前数字
        if (dfs(nums, index + 1, current_sum, target)) {
            return true;
        }

        // 记录当前状态为失败
        memo[index][current_sum] = 0;
        return false;
    }

public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        
        int target = sum / 2;
        
        // 优化策略：降序排序，大的数字先入包，能极大加速“超载剪枝”的触发
        sort(nums.rbegin(), nums.rend());

        memo.assign(nums.size(), vector<int>(target + 1, -1));

        return dfs(nums, 0, 0, target);
    }
};