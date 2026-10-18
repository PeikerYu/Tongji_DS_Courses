#include <vector>
#include <algorithm> 
using namespace std;
// 交换法思想：为了生成数组 a[k...n-1] 的全排列，将第 k 个元素与后面每一个元素依次交换，每次交换后递归地去生成剩余部分 a[k+1...n-1] 的全排列，最后再交换回来（回溯），以恢复数组状态进行下一次尝试
class Solution {
public:
    vector<vector<int>> results;
    void backtracking(vector<int>& nums,int index)
    {
        if(index==nums.size())
        {
            results.push_back(nums);
            return; // 当下标达到nums中的数字数量时，递归返回
        }
        for(int i=index;i<nums.size();i++)
        {
            swap(nums[index],nums[i]);
            backtracking(nums,index+1); // 递归处理后面的元素
            swap(nums[i],nums[index]); // 回溯
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        backtracking(nums,0);
        return results;
    }
};