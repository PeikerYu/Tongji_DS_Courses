#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <climits> // 包含 INT_MIN

// 使用 C/C++ 的 bool 类型
#ifdef __cplusplus
#include <stdbool.h>
#else
#include <stdbool.h> // C99
#endif

/*
 * 【设计思路概述】
 * * 这是一个使用单调队列（Monotonic Queue）解决的最大值查询问题。
 * 目标：实现 O(1) 均摊时间复杂度的 Enqueue, Dequeue, GetMax 三个操作。
 * * 1. ValueQueue (vq): 循环顺序队列。用于存储所有实际元素，维护 FIFO 顺序。
 * 2. MaxDeque (md): 循环顺序双端队列。用于存储“可能成为最大值的候选元素”，
 * 并严格保持单调递减（队头最大）。
 * 3. MaxQueue: 封装 vq 和 md，提供高层操作。
 * * 约定：循环队列的 front 指向队头元素的前一个位置，rear 指向队尾元素。
 * 底层数组长度 cap = capacity + 1 (留一空位判断满)。
 */

// ValueQueue: 循环顺序队列（存数据） 
struct ValueQueue {
    int *data;      // 动态分配数组：存储实际元素
    int front;      // 队头指针，指向队首元素的前一个位置
    int rear;       // 队尾指针，指向队尾元素位置（最后一个有效元素）
    int cap;        // 底层数组长度 = capacity + 1
};

// 初始化队列：capacity 为用户指定的最大可存放元素个数 n
void VQ_Init(ValueQueue &q, int capacity) {
    q.cap = capacity + 1;            // 循环队列保留一个空位
    q.data = new int[q.cap];         // 动态分配内存
    q.front = q.rear = 0;
}

// 判断空：front == rear
bool VQ_IsEmpty(const ValueQueue &q) {
    return q.front == q.rear;
}

// 判断满： (rear + 1) % cap == front
bool VQ_IsFull(const ValueQueue &q) {
    return ( (q.rear + 1) % q.cap ) == q.front;
}

// 入队：在队尾插入元素 val
void VQ_Push(ValueQueue &q, int val) {
    // 调用前应确保队列不满
    q.rear = (q.rear + 1) % q.cap; // 队尾指针后移
    q.data[q.rear] = val;          // 存入新元素
}

// 出队并返回值；调用前应先检查是否空
int VQ_Pop(ValueQueue &q) {
    // 调用前应确保队列不空
    q.front = (q.front + 1) % q.cap; // 队头指针后移（跳过被移除的元素）
    // 返回被移除的元素值
    return q.data[q.front]; 
}

// 访问队首元素（不弹出），调用前请确保非空
int VQ_Front(const ValueQueue &q) {
    // 队首元素在 front + 1 的位置
    int idx = (q.front + 1) % q.cap;
    return q.data[idx];
}

// 将队列元素按顺序输出到 vector（用于 quit 命令）
std::vector<int> VQ_GetAll(const ValueQueue &q) {
    std::vector<int> res;
    // 从队头元素位置开始遍历
    int i = (q.front + 1) % q.cap;
    // 循环到队尾元素的后一个位置为止
    while (i != (q.rear + 1) % q.cap) {
        res.push_back(q.data[i]);
        i = (i + 1) % q.cap;
    }
    return res;
}

// MaxDeque: 单调双端队列（维护最大值候选）
/*
 * 这是一个双端队列，用于保证单调递减序列。
 * 队头元素 (MD_Front) 始终是当前队列的最大值。
 */
struct MaxDeque {
    int *data;
    int front;
    int rear;
    int cap;
};

void MD_Init(MaxDeque &d, int capacity) {
    d.cap = capacity + 1;
    d.data = new int[d.cap];
    d.front = d.rear = 0;
}

bool MD_IsEmpty(const MaxDeque &d) {
    return d.front == d.rear;
}

// push_back：在尾部插入
void MD_PushBack(MaxDeque &d, int val) {
    // 假定不满
    d.rear = (d.rear + 1) % d.cap;
    d.data[d.rear] = val;
}

// pop_back：移除尾部元素
void MD_PopBack(MaxDeque &d) {
    // 假定不空
    d.rear = (d.rear - 1 + d.cap) % d.cap; // 队尾指针向前移动
}

// pop_front：移除头部元素
void MD_PopFront(MaxDeque &d) {
    // 假定不空
    d.front = (d.front + 1) % d.cap; // 队头指针向后移动
}

// front value：获取队头元素（最大值）
int MD_Front(const MaxDeque &d) {
    if (MD_IsEmpty(d)) return INT_MIN; // 保护性返回
    int idx = (d.front + 1) % d.cap;
    return d.data[idx];
}

// back value：获取队尾元素
int MD_Back(const MaxDeque &d) {
    if (MD_IsEmpty(d)) return INT_MIN; // 保护性返回
    return d.data[d.rear];
}

// MaxQueue：组合上述两个结构体，最高层
struct MaxQueue {
    ValueQueue vq;      // 存放值的队列
    MaxDeque md;        // 存放最大值候选的单调队列
    int capacity;
};

// 初始化 MaxQueue
void MQ_Init(MaxQueue &mq, int n) {
    mq.capacity = n;
    VQ_Init(mq.vq, n);
    MD_Init(mq.md, n);
}

// Enqueue 操作：O(1) 均摊
void MQ_Enqueue(MaxQueue &mq, int val) {
    // 1. 维护单调性：淘汰 MaxDeque 尾部所有小于 val 的元素
    // 这些被淘汰的元素因为 val 的存在，将永不可能成为最大值
    while (!MD_IsEmpty(mq.md) && MD_Back(mq.md) < val) {
        MD_PopBack(mq.md);
    }
    
    // 2. 将 val 加入 MaxDeque 尾部
    MD_PushBack(mq.md, val);
    
    // 3. 将 val 加入 ValueQueue (实际数据) 尾部
    VQ_Push(mq.vq, val);
}

// Dequeue 操作：O(1)
// ok 用于指示操作是否成功（队空则失败）
int MQ_Dequeue(MaxQueue &mq, bool &ok) {
    if (VQ_IsEmpty(mq.vq)) {
        ok = false;
        return INT_MIN;
    }
    
    // 1. 从 ValueQueue 移除队头元素
    int frontVal = VQ_Pop(mq.vq);
    
    // 2. 同步更新 MaxDeque：
    // 如果被弹出的元素正好是 MaxDeque 的队头，说明最大值离开了，需要同步移除 MaxDeque 的头部
    if (!MD_IsEmpty(mq.md) && MD_Front(mq.md) == frontVal) {
        MD_PopFront(mq.md);
    }
    
    ok = true;
    return frontVal;
}

// GetMax 操作：O(1)
int MQ_GetMax(MaxQueue &mq, bool &ok) {
    if (VQ_IsEmpty(mq.vq)) {
        ok = false;
        return INT_MIN;
    }
    
    // 最大值始终在 MaxDeque 的队头
    ok = true;
    return MD_Front(mq.md);
}

// 获取队列中所有元素（用于 quit 输出）
std::vector<int> MQ_GetAll(const MaxQueue &mq) {
    return VQ_GetAll(mq.vq);
}

// -------------------- 主程序：解析输入并调用上述操作 --------------------

int main() {
    // 使用 stdio 库的 I/O 流，避免使用复杂优化
    int n;
    // 读取容量 n
    if (!(std::cin >> n)) return 0;

    MaxQueue mq;
    MQ_Init(mq, n);

    char cmd[20]; // 用于存储命令字符串
    int val_int;  // 用于存储 enqueue 的值

    // 循环读取命令
    while (std::cin >> cmd) {
        if (strcmp(cmd, "enqueue") == 0) {
            // 读入 enqueue 的参数 m
            if (!(std::cin >> val_int)) break; 
            
            if (VQ_IsFull(mq.vq)) {
                std::cout << "Queue is Full\n";
            } else {
                MQ_Enqueue(mq, val_int); 
                // 成功时不输出
            }
        } else if (strcmp(cmd, "dequeue") == 0) {
            bool ok;
            int v = MQ_Dequeue(mq, ok);
            if (!ok) {
                std::cout << "Queue is Empty\n";
            } else {
                std::cout << v << "\n";
            }
        } else if (strcmp(cmd, "max") == 0) {
            bool ok;
            int m = MQ_GetMax(mq, ok);
            if (!ok) {
                std::cout << "Queue is Empty\n";
            } else {
                std::cout << m << "\n";
            }
        } else if (strcmp(cmd, "quit") == 0) {
            // 输出队列中所有元素（从队首到队尾）
            std::vector<int> all = MQ_GetAll(mq);
            if (!all.empty()) {
                for (size_t i = 0; i < all.size(); ++i) {
                    if (i) std::cout << ' ';
                    std::cout << all[i];
                }
            }
            std::cout << "\n";
            break;
        } else {
            // 忽略未知命令
            continue;
        }
    }

    // 释放动态分配的内存，避免内存泄漏
    delete[] mq.vq.data;
    delete[] mq.md.data;
    return 0;
}
