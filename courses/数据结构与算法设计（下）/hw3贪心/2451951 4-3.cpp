/*
 * 为了用最少的箭引爆最多的气球，每一次射击应当尽可能向右推迟，以覆盖更多的后续气球。将所有气球按照右边界（结束坐标）从小到大排序。对于当前最早结束的气球，必须在它的右边界处射出一箭（局部最优策略），这样既保证能引爆它，又能最大概率穿透后续左边界较小的气球。一旦遇到左边界大于当前箭矢位置的新气球，说明产生了区间断层，必须额外增加一箭，并将射击位置更新为新气球的右边界。
 */
#include <vector>
#include <algorithm> 
using namespace std;
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;

        // 1. 按照气球的右边界（xend）从小到大进行排序
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int arrows = 1; // 只要有气球，至少需要射出一箭
        int current_pos = points[0][1]; // 第一支箭贪心地射在第一个气球的右边界处

        // 2. 遍历后续气球
        for (int i = 1; i < points.size(); i++) {
            // 如果下一个气球的左边界严格大于当前箭的射击位置，说明这支箭射不到它了
            if (points[i][0] > current_pos) {
                arrows++; // 必须增加一支新箭
                current_pos = points[i][1]; // 新箭同样贪心地射在这个新气球的右边界
            }
        }

        return arrows;
    }
};