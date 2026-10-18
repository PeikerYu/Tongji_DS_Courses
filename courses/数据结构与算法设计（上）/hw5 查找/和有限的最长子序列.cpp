#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1010;   // n <= 1000
const int MAXM = 1010;   // m <= 1000

struct SeqList
{
    int len;                  // nums当前长度
    int a[MAXN];              // 排序后的nums
    long long prefix[MAXN];   // prefix[i] = a[1] + ... + a[i] 前i个数的和
};

SeqList nums;                 // 存 nums（排序后也放这里）
long long queries[MAXM];      // 存 queries（1-based）
int answer[MAXM];             // 存答案（1-based）

/**
 * @brief 初始化顺序表（清空数据）
 * @param L  顺序表
 * @param n  长度
 */
void InitSeqList(SeqList &L, int n)
{
    L.len = n;
    for (int i = 1; i <= L.len; ++i)
    {
        L.a[i] = 0;
        L.prefix[i] = 0;
    }
}

/**
 * @brief 读入 nums 数据到顺序表中
 * @param L  顺序表
 */
void ReadNums(SeqList &L)
{
    for (int i = 1; i <= L.len; ++i)
        cin >> L.a[i];
}

/**
 * @brief 对 nums 排序，并计算前缀和
 * @param L  顺序表（里面的 a 会被排序，prefix 会被填好）
 */
void BuildPrefix(SeqList &L)
{
    // 因为是 1-based，所以 sort 的范围是 [a+1, a+len+1)
    sort(L.a + 1, L.a + L.len + 1);

    long long sum = 0;
    for (int i = 1; i <= L.len; ++i)
    {
        sum += L.a[i];
        L.prefix[i] = sum;
    }
}

/**
 * @brief 二分查找：返回最大 k，使得 prefix[k] <= q
 * @param L  已经排序并有 prefix 的顺序表
 * @param q  查询值（上限）
 * @return 最大可选元素个数 k
 */
int BinarySearchMaxLen(SeqList &L, long long q)
{
    int left = 1, right = L.len;
    int ans = 0; // ans=0 表示一个数都选不了

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (L.prefix[mid] <= q)
        {
            ans = mid;        // mid 可行，记录下来
            left = mid + 1;   // 尝试找更大的 mid
        }
        else
        {
            right = mid - 1;  // mid 不可行，缩小范围
        }
    }
    return ans;
}

int main()
{
    int n, m;
    cin >> n >> m;

    // 1) 初始化并读入 nums
    InitSeqList(nums, n);
    ReadNums(nums);

    // 2) 排序 nums 并建立 prefix
    BuildPrefix(nums);

    // 3) 读入 queries，逐个二分求答案
    for (int i = 1; i <= m; ++i)
        cin >> queries[i];

    for (int i = 1; i <= m; ++i)
        answer[i] = BinarySearchMaxLen(nums, queries[i]);

    // 4) 输出答案：一行 m 个整数
    for (int i = 1; i <= m; ++i)
    {
        if (i > 1) cout << " ";
        cout << answer[i];
    }
    cout << "\n";

    return 0;
}
