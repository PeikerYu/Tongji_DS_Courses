#include <vector>
#include <string>

class Solution
{
private:
    /**
     * @brief 最大座位数
     * 题目限制 n,m <= 200，因此最多有 n*m <= 40000 个座位
     */
    static const int MAXN = 40000;

    /**
     * @brief 哈希表桶数量（取较大的质数，减少冲突）
     */
    static const int HASH_SIZE = 100003;

    /**
     * @brief 哈希表结点（链地址法）
     * 用于存储 “学生姓名 -> 目标座位编号” 的映射
     */
    struct HashNode
    {
        char name[6];   // 学生姓名（仅小写字母，长度 <= 5）
        int pos;        // 该学生在正确座位表中的目标位置编号
        int next;       // 同一哈希桶中下一个结点的下标
    };

    /**
     * @brief 哈希表结构
     */
    struct HashTable
    {
        int head[HASH_SIZE];  // head[i]：第 i 个桶的链表头
        HashNode nodes[50000];  // 所有结点的顺序存储区
        int tot;    // 当前已使用结点数
    };

    /**
     * @brief 字符串哈希函数
     * 将学生姓名映射为哈希桶编号
     * @param s 学生姓名字符串
     * @return 哈希桶下标
     */
    int Hash(const char *s)
    {
        int h = 0;
        for (int i = 0; s[i]; ++i)
        {
            h = (h * 26 + (s[i] - 'a')) % HASH_SIZE;
        }
        return h;
    }

    /**
     * @brief 初始化哈希表
     * 清空所有桶，并重置结点计数器
     */
    void InitHash(HashTable &H)
    {
        H.tot = 0;
        for (int i = 0; i < HASH_SIZE; ++i)
        {
            H.head[i] = -1;
        }
    }

    /**
     * @brief 向哈希表中插入一个映射
     * 建立 “学生姓名 -> 目标座位编号” 的对应关系
     * @param H    哈希表
     * @param name 学生姓名
     * @param pos  目标座位编号
     */
    void Insert(HashTable &H, const char *name, int pos)
    {
        int bucket = Hash(name);   // 计算桶号
        int id = H.tot++;          // 申请一个新结点

        // 拷贝姓名字符串
        int i = 0;
        while (name[i])
        {
            H.nodes[id].name[i] = name[i];
            ++i;
        }
        H.nodes[id].name[i] = '\0';

        // 存储目标位置
        H.nodes[id].pos = pos;

        // 头插法加入桶链表
        H.nodes[id].next = H.head[bucket];
        H.head[bucket] = id;
    }

    /**
     * @brief 在哈希表中查找学生的目标位置
     * @param H    哈希表
     * @param name 学生姓名
     * @return 目标座位编号（题目保证一定存在）
     */
    int Find(HashTable &H, const char *name)
    {
        int bucket = Hash(name);

        // 遍历该桶中的链表
        for (int i = H.head[bucket]; i != -1; i = H.nodes[i].next)
        {
            int j = 0;
            while (name[j] && H.nodes[i].name[j] &&
                   name[j] == H.nodes[i].name[j])
            {
                ++j;
            }

            // 两个字符串同时结束，说明完全相等
            if (!name[j] && !H.nodes[i].name[j])
            {
                return H.nodes[i].pos;
            }
        }

        return -1; // 理论上不会发生
    }

public:
    /**
     * @brief 计算将 old_chart 变为 new_chart 所需的最少交换次数
     * @param old_chart 当前（错误）的座位表
     * @param new_chart 正确的座位表
     * @return 最少交换次数
     * 算法思想：
     * 1) 使用哈希表建立 “学生姓名 -> 目标位置编号” 的映射
     * 2) 构造置换数组 p：p[id] 表示当前位置 id 的学生最终要去的位置
     * 3) 对置换进行环分解：长度为 L 的环需要 L-1 次交换
     */
    int solve(std::vector<std::vector<std::string>> &old_chart,
              std::vector<std::vector<std::string>> &new_chart)
    {
        int n = old_chart.size();        // 行数
        int m = old_chart[0].size();     // 列数
        int N = n * m;                   // 总座位数

        // 1) 构建哈希表：name -> 目标位置 
        HashTable H;
        InitHash(H);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                // 将二维坐标 (i,j) 映射为一维编号 id
                int id = i * m + j;
                Insert(H, new_chart[i][j].c_str(), id);
            }
        }

        // 2) 构造置换数组 p 
        static int p[MAXN];   // p[id] = 当前在 id 的人最终要去的位置
        static int vis[MAXN]; // 访问标记数组

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                int id = i * m + j;
                p[id] = Find(H, old_chart[i][j].c_str());
                vis[id] = 0;
            }
        }

        // 3) 环分解，统计最少交换次数 
        int swaps = 0;

        for (int i = 0; i < N; ++i)
        {
            // 已经属于某个环的结点直接跳过
            if (vis[i]) continue;

            int cur = i;
            int len = 0;

            // 沿着置换不断跳转，直到回到已访问结点
            while (!vis[cur])
            {
                vis[cur] = 1;
                cur = p[cur];
                ++len;
            }

            // 长度为 len 的环需要 len-1 次交换
            if (len > 1)
            {
                swaps += (len - 1);
            }
        }

        return swaps;
    }
};
