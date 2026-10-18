#include <vector>
#include <algorithm> // 因为你用到了 swap
using namespace std;
/*f(n) = f(n-1) + f(n-2)。为了避免重复计算，采用动态规划的递归*/
class Solution {
public:
    int trainWays(int num) {
        if (num <= 1) return 1;
    
    // 使用数组记录中间结果，避免递归过程中的重复计算（动态规划思想）
    vector<int> dp(num + 1);
    dp[0] = 1; 
    dp[1] = 1;
    
    for (int i = 2; i <= num; i++) {
        // 状态转移方程：到达当前台阶的方法数 = 前两级方法数之和
        // 按照题目要求对大数取模，防止溢出
        dp[i] = (dp[i - 1] + dp[i - 2]) % 1000000007;
    }
    
    return dp[num];
    }
};