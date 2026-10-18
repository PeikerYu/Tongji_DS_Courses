#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

/* * 算法基本思想：快速选择 (Quick Select)
 * 1. 分治策略：基于快速排序的 Partition 过程。通过一个基准值 (pivot) 将数组分为两部分
 * 2. 减治优化：与快排不同，快速选择只关心目标 k 所在的区间。每次划分后，只需递归其中一边
 * 3. 稳定性处理：采用 Hoare Partition 并在遇到相等元素时停止指针，确保在大量重复元素下依然能对半划分
 * 4. 随机化：通过随机选取 pivot 避免在有序或特定构造的数组中退化至 O(n^2)，保证平均时间复杂度为 O(n)
 */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 初始化随机种子，防止被极端测试用例针对
        srand(time(0));
        int n = nums.size();
        // 题目找第 k 大，等价于找升序排序后下标为 n - k 的元素
        return quickselect(nums, 0, n - 1, n - k);
    }

private:
    int quickselect(vector<int>& nums, int l, int r, int k) {
        // 基准情况：区间只有一个元素
        if (l == r) return nums[l];

        // 随机化优化：随机选一个位置作为基准，并换到左端
        int randomIndex = rand() % (r - l + 1) + l;
        swap(nums[l], nums[randomIndex]);

        int pivot = nums[l];
        int i = l - 1, j = r + 1;

        // Hoare Partition：双指针碰撞法
        while (i < j) {
            // 不使用 <= 或 >= 是为了在遇到重复元素时强制交换，保持树的平衡
            do i++; while (nums[i] < pivot);
            do j--; while (nums[j] > pivot);
            if (i < j) swap(nums[i], nums[j]);
        }

        // 分治定位：
        // 此时数组被划分为 [l, j] 和 [j + 1, r] 两部分
        // j 是左半部分的边界
        if (k <= j) {
            return quickselect(nums, l, j, k);
        } else {
            return quickselect(nums, j + 1, r, k);
        }
    }
};