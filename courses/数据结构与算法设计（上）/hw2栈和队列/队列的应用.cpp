#include <iostream>
#include <cstring> // memset
using namespace std;

struct Node //链式队列的节点
{
    int x, y;     // 存储坐标
    Node* next;   // 指向下一个节点
};
struct Queue //链式队列
{
    Node* front;  // 队头指针（不存数据）
    Node* rear;   // 队尾指针

    // 初始化队列（创建头节点）
    void init() 
    {
        front = rear = new Node;  // 创建一个空头节点
        front->next = NULL;
    }

    // 判断队列是否为空
    bool empty() 
    {
        return front == rear;
    }

    // 入队：在队尾插入元素
    void push(int x, int y) 
    {
        Node* p = new Node;
        p->x = x;
        p->y = y;
        p->next = NULL;
        rear->next = p;
        rear = p;
    }

    // 出队：删除队首元素，并返回其值
    bool pop(int &x, int &y) 
    {
        if (empty()) return false; // 空队列
        Node* p = front->next; //真正的第一个元素
        x = p->x;
        y = p->y;
        front->next = p->next;
        if (rear == p) rear = front; // 若删掉的是唯一的节点，更新rear指向头节点
        delete p;
        return true;
    }

    // 销毁队列（释放内存）
    void destroy() 
    {
        while (front) 
        {
            Node* tmp = front;
            front = front->next;
            delete tmp;
        }
    }
};

// ========================
// 全局变量定义
// ========================
const int MAXN = 1000; //题目保证n,m<=1000
bool Map[MAXN][MAXN];  // 存储输入的0/1地图
bool Vis[MAXN][MAXN];  // 访问标记，记录该坐标是否已被BFS访问过
int n, m;              // 行列数
//四个方向的偏移量，用于BFS搜索四领域
int dx[4] = {0, 0, -1, 1}; //行偏移：左右（0），上（-1），下（1）
int dy[4] = {-1, 1, 0, 0}; //列偏移：上下（0），左（-1），右（1）

// BFS函数：从 (x, y) 开始搜索整个连同区域
void BFS(int x, int y) {
    Queue Q;
    Q.init(); // 初始化队列
    Q.push(x, y);
    Vis[x][y] = true;

    while (!Q.empty()) {
        int cx, cy;
        Q.pop(cx, cy);
        // 向四个方向扩展
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            // 判断是否在范围内、是否为1、是否未访问
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                Map[nx][ny] && !Vis[nx][ny]) {
                Vis[nx][ny] = true;
                Q.push(nx, ny);
            }
        }
    }

    Q.destroy(); // 释放节点内存
}

// ========================
// 主函数
// ========================
int main() {
    memset(Vis, 0, sizeof(Vis));

    cin >> n >> m;

    // 输入地图（0或1），带空格输入
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> Map[i][j];

    int count = 0;

    // 遍历除边界外的格子
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            // 如果是未访问的1，则为一个新区域
            if (Map[i][j] && !Vis[i][j]) {
                count++;
                BFS(i, j);
            }
        }
    }

    cout << count << endl;
    return 0;
}
