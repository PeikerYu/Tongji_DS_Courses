#include <map>
#include <vector>
using namespace std;

/**
 * 核心思想：
 * - freq[val]：记录 val 当前出现次数（频率）
 * - group[f] ：一个“栈”（用 vector 当栈）存放所有“当前频率变成 f 的元素”
 *   也就是说：每次 push(val) 后，val 的频率从 f-1 变成 f，就把 val 压入 group[f]
 *
 * pop():
 * - 总是从最大频率 maxFreq 对应的 group[maxFreq] 的栈顶弹出
 * - 弹出后，该 val 的频率 freq[val]--（因为少了一个）
 * - 如果 group[maxFreq] 变空，maxFreq--（最大频率下降）
 *
 * 这样可以保证：
 * - 频率最高优先：因为总取 maxFreq
 * - 同频率时取最靠近栈顶：因为 group[f] 是按时间顺序压入的“栈”，栈顶就是最新的
 */
class FreqStack
{
private:
    map<int, int> freq;                 // freq[val] = val 出现次数
    map<int, vector<int>> group;        // group[f] = 频率为 f 的“栈”
    int maxFreq;                        // 当前最大频率

public:
    /**
     * @brief  构造函数：初始化空的频率栈
     */
    FreqStack()
    {
        maxFreq = 0;
    }

    /**
     * @brief  将 val 压入栈顶
     * @param  val 要压入的整数
     *
     * 操作步骤：
     * 1) freq[val]++
     * 2) 令 f = freq[val]，把 val 压入 group[f]
     * 3) 更新 maxFreq = max(maxFreq, f)
     */
    void push(int val)
    {
        int f = ++freq[val];
        group[f].push_back(val);
        if (f > maxFreq) maxFreq = f;
    }

    /**
     * @brief  弹出并返回出现频率最高的元素
     * @return 被弹出的元素值
     *
     * 规则：
     * - 若最高频率元素不止一个，弹出最接近栈顶（最新 push）的那个
     *
     * 操作步骤：
     * 1) 从 group[maxFreq] 的“栈顶”取出 val
     * 2) group[maxFreq].pop_back()
     * 3) freq[val]--（因为 val 少了一个）
     * 4) 若 group[maxFreq] 为空，则 maxFreq--
     */
    int pop()
    {
        vector<int> &stk = group[maxFreq];
        int val = stk.back();
        stk.pop_back();

        freq[val]--;

        if (stk.empty())
        {
            group.erase(maxFreq);  
            maxFreq--;
        }

        return val;
    }
};
