#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 110;

struct ArcNode  //边节点
{
    int adjvex;        // 在该 VNode 下指向的后继顶点（课程）编号v，用于表示 u to v 的关系
    ArcNode* next;     // 指向链表中下一个边节点
};
struct VNode  //顶点（课程）
{
    ArcNode* first;    //链表的头指针
    int indegree;      // 入度（前置课程数）
};
struct ALGraph 
{
    VNode AdjList[MAXN];  //存储所有课程顶点
    int vexnum, arcnum;
};

int ttime[MAXN];       // 存储每门课程完成所需的学时t[i], 1..n
// int EF[MAXN];          //存储课程 i 最早可能完成的时间
// int LF[MAXN];          //存储课程 i 允许的最晚完成时间，不影响总工期
// int topo[MAXN];        //存储图的拓扑排序结果
ALGraph G;

/**
 * @brief  在有向图中添加一条边 u -> v，添加前置课程关系
 * @param  G  有向图
 * @param  u  前置课程
 * @param  v  当前课程
 */
void AddEdge(ALGraph &G, int u, int v) 
{
    ArcNode* p = new ArcNode;
    p->adjvex = v;
    p->next = G.AdjList[u].first;
    G.AdjList[u].first = p;
    G.AdjList[v].indegree++;
    G.arcnum++;
}

int main() 
{
    int n;
    cin>>n;
    G.vexnum = n; 
    G.arcnum = 0;
    // 初始化：注意编号是1-based
    for (int i = 1; i <= n; ++i)  
    {
        G.AdjList[i].first = nullptr;
        G.AdjList[i].indegree = 0;
    }

    // 读入，并构造图：对于当前课程 i，读 t[i], ci, 然后 ci 个前置 p，构造边：p -> i
    for (int i = 1; i <= n; ++i) 
    {
        int ti, ci;
        cin >> ti >> ci;
        ttime[i] = ti;
        for (int k = 0; k < ci; ++k) 
        {
            int p; 
            cin >> p;
            AddEdge(G, p, i); // p -> i
        }
    }

    // 拓扑排序得到顺序 topo[]
    int indeg[MAXN];
    for (int i = 1; i <= n; ++i) 
        indeg[i] = G.AdjList[i].indegree;

    queue<int> q;
    int topo[MAXN], topoCnt = 0; //topoCnt记录已经放进topo[]的元素数量
    for (int i = 1; i <= n; ++i) 
        if (indeg[i] == 0) 
            q.push(i);

    while (!q.empty()) 
    {
        int u = q.front(); 
        q.pop();
        topo[topoCnt++] = u;
        for (ArcNode* p = G.AdjList[u].first; p; p = p->next) 
        {
            int v = p->adjvex;
            indeg[v]--;
            if (indeg[v] == 0) 
                q.push(v);
        }
    }

    // 题目保证可毕业（即无环），但仍可检查
    if (topoCnt != n) 
    {
        cout << "-1\n";
        return 0;
    }

    // 计算最早完成时间 EF (也叫 E)
    // EF[u] 表示课程 u 的最早完成时间（学时单位）
    int EF[MAXN];
    for (int i = 1; i <= n; ++i) 
        EF[i] = 0;

    // 按拓扑顺序处理
    for (int idx = 0; idx < topoCnt; ++idx) 
    {
        int u = topo[idx];
        // 如果 u 尚未被任何前驱更新且入度为0，则它的最早完成时间至少是自身时长
        if (EF[u] == 0) 
            EF[u] = ttime[u];
        // 用 u 去松弛后继 v： EF[v] = max(EF[v], EF[u] + t[v])
        for (ArcNode* p = G.AdjList[u].first; p; p = p->next) 
        {
            int v = p->adjvex;
            if (EF[v] < EF[u] + ttime[v]) 
                EF[v] = EF[u] + ttime[v];
        }
    }

    // 总毕业时间 T = max EF[i]
    int T = 0;
    for (int i = 1; i <= n; ++i) 
        if (EF[i] > T) 
            T = EF[i];

    // 计算最迟完成时间 LF (也叫 L)
    // 初始化 LF 为 +inf，终点节点（outdeg==0）设置为 T
    int LF[MAXN];
    for (int i = 1; i <= n; ++i) 
        LF[i] = T;

    // 反向按拓扑顺序处理（从后向前）
    for (int idx = topoCnt - 1; idx >= 0; --idx) 
    {
        int u = topo[idx];
        for (ArcNode* p = G.AdjList[u].first; p; p = p->next) 
        {
            int v = p->adjvex;
            // LF[u] = min(LF[u], LF[v] - t[v])
            if (LF[v] - ttime[v] < LF[u]) 
                LF[u] = LF[v] - ttime[v];
        }
    }
    
    // 输出每门课程的 EF 与 是否关键(1/0)
    // 若 EF[i] == LF[i] 则在关键路径上（增加该课程时间会增加总体时间）
    for (int i = 1; i <= n; ++i) 
    {
        int isCritical = (EF[i] == LF[i]) ? 1 : 0;
        cout << EF[i] << " " << isCritical << "\n";
    }

    return 0;
}
