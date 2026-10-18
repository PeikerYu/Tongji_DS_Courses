/*
 *核心突破口在于“高个子看不见矮个子”，即后续插入较矮的人完全不会影响已经排好位置的高个子的 k 值。因此，确立了“先高后矮”的处理顺序。首先将数组按照身高 h 降序排列，如果 h 相同则按 k 升序排列。排好序后，依次遍历每个人，并直接将其插入到结果队列的第 k 个位置。由于此时队列中已存在的都是比他高或等高的人，插入到索引 k 恰好满足“前面有 k 个大于等于自己的人”；而未来插入的矮个子即使插到他前面，也不会破坏他的 k 值条件。
 */
#include <vector>
#include <algorithm> 
using namespace std;
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // 1. 自定义排序规则：身高 h 降序，k 值升序
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] < b[1];
            }
            return a[0] > b[0];
        });

        vector<vector<int>> queue;
        
        // 2. 遍历排序后的数组，按照 k 值作为索引进行插入
        for (int i = 0; i < people.size(); i++) {
            // 在 queue 的第 people[i][1] (即 k) 个位置插入当前元素
            queue.insert(queue.begin() + people[i][1], people[i]);
        }
        
        return queue;
    }
};