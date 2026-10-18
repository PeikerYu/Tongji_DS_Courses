#include <vector>
#include <map>

using namespace std;

/* * 算法基本思想：奇偶分治构造法
 * 1. 数学原理：利用“偶数不等于奇数”的性质。若 nums[i] 为奇数，nums[j] 为偶数，则其和必为奇数，
 * 而 2 * nums[k] 必为偶数，从而天然满足 2 * nums[k] != nums[i] + nums[j]
 * 2. 分治策略：将数组分为左侧全部奇数、右侧全部偶数，通过递归构造子问题的漂亮数组
 * 3. 线性变换：若 [x1, x2, ...] 是漂亮的，则 [2*x1-1, 2*x2-1, ...] (奇数映射) 
 * 和 [2*x1, 2*x2, ...] (偶数映射) 也是漂亮的
 * 4. 记忆化搜索：使用 map 存储已计算过的结果，避免重复构造，提高效率
 */
class Solution {
    // 记忆化，存储已经构造好的不同长度的漂亮数组
    map<int, vector<int>> memo;

public:
    vector<int> beautifulArray(int n) {
        // 基准情况：长度为 1 的数组显然是漂亮的
        if (n == 1) 
            return {1};
        
        // 如果已经算过了，直接返回
        if (memo.count(n)) 
            return memo[n];

        vector<int> res;
        
        // 递归处理左半部分（奇数）
        // 长度为 (n+1)/2 的漂亮数组映射到 1, 3, 5...
        vector<int> leftPart = beautifulArray((n + 1) / 2);
        for (int i = 0; i < leftPart.size(); i++) {
            int x = leftPart[i];      
            res.push_back(2 * x - 1);       
        }
        
        // 递归处理右半部分（偶数）
        // 长度为 n/2 的漂亮数组映射到 2, 4, 6...
        vector<int> rightPart = beautifulArray((n + 1) / 2);
        for (int i = 0; i < rightPart.size(); i++) {
            int x = rightPart[i];      
            res.push_back(2 * x);       
        }

        // 合并后的结果天然满足漂亮数组定义
        return memo[n] = res;
    }
};