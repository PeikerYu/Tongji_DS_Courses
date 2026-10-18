//最大子数组和
// 核心思路：如果前面累加的子数组和已经小于0了，那它对后面的元素只会起到“拖后腿”的作用，不如直接丢弃，从下一个元素重新开始算。
int maxSubArray(int* nums, int numsSize) {
    int curr_sum = 0;
    int sum = nums[0]; // 记录全局最大和
    
    for(int i = 0; i < numsSize; i++) {
        curr_sum += nums[i]; 
        
        if(curr_sum > sum) {
            sum = curr_sum;  // 创新高就更新记录
        }
        
        if(curr_sum < 0) {
            curr_sum = 0;    // 跌破0就及时止损，前面的彻底不要了
        }
    }

    return sum;
}