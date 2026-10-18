//24 点游戏
// 核心思路：每次从当前数字里任选两个做 + - * /，得到一个新数，剩下 n-1 个数继续递归；只剩一个数时判断是否等于 24。这样自然覆盖了所有括号组合方式。
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    bool judgePoint24(vector<int>& cards) {
        vector<double> nums(cards.begin(), cards.end());
        return solve(nums);
    }

    bool solve(vector<double>& nums) {
        if (nums.size() == 1)
            return fabs(nums[0] - 24) < 1e-6;

        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;

                vector<double> next;
                for (int k = 0; k < n; k++)
                    if (k != i && k != j) next.push_back(nums[k]);

                // 尝试四种运算
                double a = nums[i], b = nums[j];
                double ops[4] = {a + b, a - b, a * b};
                for (int t = 0; t < 3; t++) {
                    next.push_back(ops[t]);
                    if (solve(next)) return true;
                    next.pop_back();
                }
                if (b != 0) {
                    next.push_back(a / b);
                    if (solve(next)) return true;
                    next.pop_back();
                }
            }
        }
        return false;
    }
};
