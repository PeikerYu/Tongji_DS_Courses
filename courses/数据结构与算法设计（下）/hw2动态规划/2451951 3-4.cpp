//买卖股票的最佳时机
#include <vector>
#include <algorithm> 
using namespace std;
class Solution {
public:
    // 核心思路：要在某天卖出赚得最多，就必须在它之前“价格最低”的那天买入。
    // 遍历每一天，一边维护“历史最低价”，一边计算“如果今天卖出能赚多少”，留住最大利润。
    int maxProfit(vector<int>& prices) {
       int profit = 0;
       int min = prices[0]; // 记录到今天为止的历史最低价格
       
       for(int i = 1; i < prices.size(); i++) 
       {
           if(prices[i] < min) {
               min = prices[i]; // 发现更便宜的价格，更新买入成本
           }
           
           // 用今天的价格减去历史最低价，看看利润有没有打破之前的记录
           profit = max(profit, prices[i] - min);
       }
       return profit;
    }
};