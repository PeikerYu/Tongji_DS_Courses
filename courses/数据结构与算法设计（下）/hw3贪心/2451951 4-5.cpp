// 首先将所有课程按截止时间从小到大排序，优先考虑最先过期的课程。在遍历过程中，贪心地将每门课暂且加入计划，并累加总耗时；如果累加后的总时间超出了当前课程的截止时间，说明原计划不可行，此时触发“反悔”机制,利用大顶堆，从已选课程中剔除耗时最长的那一门。通过这种“牺牲一门长课，保全后续多门短课”的做法，在不改变已选课程数量下限的前提下，尽可能多地为后续课程腾出时间，从而实现课程数量的最大化。
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // 1. 按照课程的截止时间 lastDay 从小到大排序
        sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        // 2. 大顶堆，用于存储已经决定上的课程的 duration
        priority_queue<int> maxHeap;
        int total_time = 0; // 当前已经消耗的总时间

        // 3. 遍历所有课程
        for (const auto& course : courses) {
            int duration = course[0];
            int lastDay = course[1];

            // 贪心地把当前课程加进来
            total_time += duration;
            maxHeap.push(duration);

            // 如果加入后总时间超出了当前课程的截止时间，触发“反悔”机制
            if (total_time > lastDay) {
                // 把已选课程中耗时最长的一门踢掉（堆顶元素）
                total_time -= maxHeap.top();
                maxHeap.pop();
            }
        }

        // 4. 堆里面剩下的元素个数，就是最多可以修读的课程数目
        return maxHeap.size();
    }
};