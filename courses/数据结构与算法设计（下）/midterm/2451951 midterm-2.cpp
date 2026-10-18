// 宝可梦卡牌分堆
// 将n张卡牌分成两堆，使两堆价值之差最小
// 方法1：暴力枚举所有2^n种分法 O(2^n)
// 方法2：动态规划（0-1背包变形）O(n * totalSum)

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>
#include <iomanip>
using namespace std;

// ===== 方法1：暴力枚举 =====
// 枚举每张牌"放入堆1"或"不放入堆1"的所有组合
void bruteForce(vector<int>& v) {
    int n = v.size();
    int total = 0;
    for (int x : v) total += x;

    int bestDiff = INT_MAX, bestMask = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int s = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) s += v[i];
        int diff = abs(total - 2 * s);
        if (diff < bestDiff) {
            bestDiff = diff;
            bestMask = mask;
        }
    }

    int s1 = 0;
    vector<int> p1, p2;
    for (int i = 0; i < n; i++) {
        if (bestMask >> i & 1) { s1 += v[i]; p1.push_back(i + 1); }
        else p2.push_back(i + 1);
    }
    int s2 = total - s1;
    if (s1 > s2) { swap(s1, s2); swap(p1, p2); }

    cout << s1 << "\n";
    for (int x : p1) cout << x << " ";
    cout << "\n" << s2 << "\n";
    for (int x : p2) cout << x << " ";
    cout << "\n";
}

// 暴力枚举只计算不打印（用于计时）
int bruteForceCalc(vector<int>& v) {
    int n = v.size();
    int total = 0;
    for (int x : v) total += x;

    int bestDiff = INT_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {
        int s = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) s += v[i];
        int diff = abs(total - 2 * s);
        if (diff < bestDiff) bestDiff = diff;
    }
    return bestDiff;
}

// ===== 方法2：动态规划 =====
// 递推式：dp[i][j] = 前i张牌能否凑出和j
//   dp[i][j] = dp[i-1][j]  （不选第i张）
//           || dp[i-1][j-v[i-1]]  （选第i张，若j>=v[i-1]）
// 目标：找最大的j <= total/2 使得dp[n][j]=true
// 时间复杂度：O(n * totalSum)，空间复杂度：O(n * totalSum)（回溯用）
void dpSolve(vector<int>& v) {
    int n = v.size();
    int total = 0;
    for (int x : v) total += x;
    int half = total / 2;

    // dp[i][j]: 用前i张牌能否恰好凑出和j
    vector<vector<bool>> dp(n + 1, vector<bool>(total + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= total; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= v[i - 1] && dp[i - 1][j - v[i - 1]])
                dp[i][j] = true;
        }
    }

    // 找最大可达和 <= half
    int best = 0;
    for (int j = half; j >= 0; j--) {
        if (dp[n][j]) { best = j; break; }
    }

    // 回溯找第一堆用了哪些牌
    vector<int> p1;
    int cur = best;
    for (int i = n; i >= 1; i--) {
        if (!dp[i - 1][cur]) {
            // 不选第i张无法达到cur，说明必须选了它
            p1.push_back(i);
            cur -= v[i - 1];
        }
    }
    sort(p1.begin(), p1.end());

    vector<bool> inP1(n + 1, false);
    for (int x : p1) inP1[x] = true;
    vector<int> p2;
    for (int i = 1; i <= n; i++)
        if (!inP1[i]) p2.push_back(i);

    int s1 = best, s2 = total - best;
    if (s1 > s2) { swap(s1, s2); swap(p1, p2); }

    cout << s1 << "\n";
    for (int x : p1) cout << x << " ";
    cout << "\n" << s2 << "\n";
    for (int x : p2) cout << x << " ";
    cout << "\n";
}

// DP只计算不打印（用于计时）
int dpCalc(vector<int>& v) {
    int n = v.size();
    int total = 0;
    for (int x : v) total += x;
    int half = total / 2;

    // 用滚动数组节省空间（计时版本）
    vector<bool> dp(total + 1, false);
    dp[0] = true;
    for (int i = 0; i < n; i++)
        for (int j = total; j >= v[i]; j--)
            if (dp[j - v[i]]) dp[j] = true;

    int best = 0;
    for (int j = half; j >= 0; j--)
        if (dp[j]) { best = j; break; }
    return total - 2 * best;
}

using hrc = chrono::high_resolution_clock;

int main() {
    srand(42);

    // ===== 示例测试 =====
    {
        cout << "===== 示例：n=8，卡牌价值 2 1 3 1 5 2 3 4 =====\n\n";
        vector<int> v = {2, 1, 3, 1, 5, 2, 3, 4};

        cout << "--- 暴力枚举结果 ---\n";
        bruteForce(v);

        cout << "\n--- 动态规划结果 ---\n";
        dpSolve(v);
    }

    // ===== 额外测试 =====
    {
        cout << "\n===== 测试2：n=5，卡牌价值 1 2 3 4 5 =====\n\n";
        vector<int> v = {1, 2, 3, 4, 5};
        cout << "--- 暴力枚举结果 ---\n";
        bruteForce(v);
        cout << "\n--- 动态规划结果 ---\n";
        dpSolve(v);
    }

    // ===== 暴力 vs DP 时间对比（小n） =====
    cout << "\n===== 暴力枚举 vs 动态规划 运行时间对比 =====\n";
    cout << setw(8) << "n"
         << setw(20) << "暴力枚举(微秒)"
         << setw(20) << "动态规划(微秒)" << "\n";
    cout << string(48, '-') << "\n";

    for (int n : {8, 12, 16, 20}) {
        vector<int> v(n);
        for (int i = 0; i < n; i++) v[i] = rand() % 10 + 1;

        volatile int sink = 0;
        auto t0 = hrc::now();
        sink ^= bruteForceCalc(v);
        auto t1 = hrc::now();
        sink ^= dpCalc(v);
        auto t2 = hrc::now();
        (void)sink;

        long long bf = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
        long long dp = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        cout << setw(8) << n << setw(20) << bf << setw(20) << dp << "\n";
    }

    // ===== DP处理大规模输入 =====
    cout << "\n===== 动态规划处理大规模输入 =====\n";
    cout << setw(8) << "n"
         << setw(20) << "动态规划(微秒)" << "\n";
    cout << string(28, '-') << "\n";

    for (int n : {50, 100, 200, 500}) {
        vector<int> v(n);
        for (int i = 0; i < n; i++) v[i] = rand() % 20 + 1;

        volatile int sink = 0;
        auto t0 = hrc::now();
        sink ^= dpCalc(v);
        auto t1 = hrc::now();
        (void)sink;

        cout << setw(8) << n
             << setw(20) << chrono::duration_cast<chrono::microseconds>(t1 - t0).count()
             << "\n";
    }

    return 0;
}
