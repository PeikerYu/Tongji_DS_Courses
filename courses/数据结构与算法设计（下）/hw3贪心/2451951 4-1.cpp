/*
 * 算法核心思想：为了找到小于等于 n 的最大单调递增整数，采用贪心策略从右向左扫描数组。当发现相邻两位前大后小时，将前一位减 1，并记录当前位置作为分界线。因为高位一旦减小，整体数值必然变小，此时为了让结果最大化，需将分界线及之后的所有低位全部置为 9
 */
#include <string>
#include <algorithm> 
using namespace std;
class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string s=to_string(n);
        int length=s.length();
        int flag=length; //flag是从哪一位开始要把s的后续位置全部转换为9的位置
        for(int i=length-1;i>0;i--)
        {
            if(s[i-1]>s[i])
            {
                flag=i;
                s[i-1]--;
            }
            for(int i=flag;i<length;i++)
                    s[i]='9';
        }
        return stoi(s);
    }
};