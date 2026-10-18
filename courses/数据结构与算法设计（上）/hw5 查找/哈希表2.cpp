#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/**
 * @brief  判断一个数是否为素数
 * @param  n 待判断的数
 * @return true 表示是素数；false 表示不是素数
 */
bool IsPrime(int n)
{
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0) return false;
    }
    return true;
}

/**
 * @brief  找到大于等于 n 的最小素数
 * @param  n 起始值
 * @return 大于等于 n 的最小素数
 */
int GetNextPrime(int n)
{
    while (!IsPrime(n))
    {
        n++;
    }
    return n;
}

/**
 * @brief  计算字符串的哈希值
 * @param  key 字符串
 * @return 哈希值（unsigned long long）
 */
unsigned long long ComputeHash(const string &key)
{
    unsigned long long h = 0;
    int len = key.length();
    
    for (int i = 0; i < len; i++)
    {
        h = h * 37 + (unsigned long long)key[i];
    }
    
    return h;
}

/**
 * @brief  使用平方探测法在哈希表中查找插入位置
 * @param  hashTable 哈希表（0表示空位，1表示已占用）
 * @param  M 表长（素数）
 * @param  hashValue 哈希值
 * @return 插入位置索引，若找不到返回 -1
 */
int QuadraticProbe(int* hashTable, int M, unsigned long long hashValue)
{
    int pos = hashValue % M;
    
    // 首先检查原始位置
    if (hashTable[pos] == 0)
    {
        return pos;
    }
    
    // 平方探测：探测 pos+1^2, pos-1^2, pos+2^2, pos-2^2, ...
    for (int i = 1; i <= M; i++)
    {
        // 正向探测：(pos + i^2) % M
        int probe1 = (pos + i * i) % M;
        if (hashTable[probe1] == 0)
        {
            return probe1;
        }
        
        // 负向探测：(pos - i^2) % M
        int probe2 = (pos - i * i) % M;
        if (probe2 < 0) probe2 += M;  // 处理负数
        if (hashTable[probe2] == 0)
        {
            return probe2;
        }
    }
    
    // 探测次数超过表长，找不到位置
    return -1;
}

int main()
{
    
    int N, P;
    cin >> N >> P;
    
    // 若 P 不是素数，取大于 P 的最小素数
    int M = IsPrime(P) ? P : GetNextPrime(P);
    
    // 初始化哈希表（0 表示空位，1 表示已占用）
    int* hashTable = new int[M];
    memset(hashTable, 0, sizeof(int) * M);
    
    // 处理 N 个字符串
    for (int i = 0; i < N; i++)
    {
        string name;
        cin >> name;
        
        // 计算哈希值
        unsigned long long hashValue = ComputeHash(name);
        
        // 使用平方探测法查找插入位置
        int pos = QuadraticProbe(hashTable, M, hashValue);
        
        if (pos != -1)
        {
            hashTable[pos] = 1;  // 标记为已占用
            cout << pos;
        }
        else
        {
            cout << "-";
        }
        
        // 输出格式：最后一个不输出空格
        if (i < N - 1) cout << " ";
    }
    cout << "\n";
    
    delete[] hashTable;
    return 0;
}


