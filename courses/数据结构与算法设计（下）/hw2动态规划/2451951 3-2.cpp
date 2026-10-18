//最长递增子序列 (LIS)
int max(int a,int b) {
    return a>b?a:b;
}

// 核心思路：dp[i] 表示“强制以 nums[i] 结尾”时的最长递增子序列长度。
// 想求 dp[i]，就去前面找比 nums[i] 小的数 nums[j]，然后试着接在它后面。
int lengthOfLIS(int* nums, int numsSize) {
    int dp[2501]; 
    for(int i=0;i<2501;i++)
        dp[i]=1; // 最差情况是自己单独成列，长度保底为1
        
    int res=1;
    for(int i=0;i<numsSize;i++) 
    {
        // 回头找前面所有能接上的位置
        // 注意：这里条件改成了 j < i，因为自己和自己比(j=i)没有意义
        for(int j=0;j<i;j++) 
        {
            if(nums[i]>nums[j]) // 满足严格递增
            {
                dp[i]=max(dp[j]+1, dp[i]); // 看看接在谁后面能凑得更长
                res=max(res, dp[i]);       // 顺手刷新一下全局最长记录
            }
        }
    }
    return res;
}