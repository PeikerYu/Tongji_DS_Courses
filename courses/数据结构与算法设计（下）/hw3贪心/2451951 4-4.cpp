int wiggleMaxLength(int* nums, int numsSize) {
    if(numsSize==1)
        return 1;

    int i=1;
    while(i<numsSize)
    {
        if(nums[i-1]==nums[i])
            i++;
        else
            break;
    }
    if(i==numsSize)
        return 1;

    int len=2;
    int lastdir=(nums[i]>nums[i-1]?1:-1);
    for(int j=i;j<numsSize-1;j++)
    {
        if(lastdir==1&&nums[j]>nums[j+1])
        {
            lastdir=-1;
            len++;
        }
        else if(lastdir==-1&&nums[j]<nums[j+1])
        {
            lastdir=1;
            len++;
        }
    }
    return len;
}
