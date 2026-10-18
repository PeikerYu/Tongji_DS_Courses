//零钱兑换
// 核心思路：要想凑出金额 i 用的硬币最少，只需看看凑出“i - 某枚硬币面值”最少需要几个，然后加 1。从小到大遍历每个金额，试遍手里的硬币，一边把无法凑出的设为“极大值”排雷，一边留住最少的硬币个数。
#include <vector>
#include <algorithm> 
using namespace std;
int min(int a,int b)
{
    return a<b?a:b;
}
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        //初始化dp数组，表示凑成金额为i时所需的最少的硬币个数 
        int dp[amount+1];
        for(int i=0;i<=amount;i++)
            dp[i]=amount+1; //此背景下不可能达到的值，不用INT_MAX因为后续加减会存在溢出问题
        dp[0]=0;
        for(int i=1;i<=amount;i++)
        {
            for(int j=0;j<coins.size();j++)
            {
                if(i>=coins[j])
                {
                    dp[i]=min(dp[i],dp[i-coins[j]]+1);
                }
            }
        }
        if(dp[amount]==amount+1)
            return -1;
        else
            return dp[amount];
    }
};