#include <iostream>
using namespace std;

const int MAXK = 1005;

struct ArcNode //边节点
{
    int adjvex;        
    ArcNode* next;    
};

struct VNode //顶点节点
{
    ArcNode* first;    
    int indegree;      //每个节点的入度
    int stack_link;    // 模拟栈的链指针。在拓扑排序中，用于连接所有入度为 0 的顶点。
};

struct ALGraph //图
{
    VNode AdjList[MAXK];
    int vexnum, arcnum;
};

void cleanup_graph(ALGraph& G) //清理边
{
    for (int i = 1; i <= G.vexnum; ++i) 
    {
        ArcNode* p = G.AdjList[i].first;
        while (p) 
        {
            ArcNode* temp = p;
            p = p->next;
            delete temp;
        }
        G.AdjList[i].first = nullptr;
    }
}

//构建图
/**
 * @brief  根据给定的约束条件构建有向图（邻接表），并统计各结点入度
 * @param  G        图的邻接表结构
 * @param  vexnum   顶点个数（1~k）
 * @param  arcnum   有向边条数
 * @param  cond     约束数组，每一行为一条有向边 u -> v
 */
void build_graph(ALGraph& G, int vexnum, int arcnum, int cond[][2]) 
{
    G.vexnum = vexnum;
    G.arcnum = arcnum;
    for (int i = 1; i <= vexnum; ++i) 
    {
        G.AdjList[i].first = nullptr;
        G.AdjList[i].indegree = 0;
        G.AdjList[i].stack_link = -2;
    }

    for (int i = 0; i < arcnum; ++i) 
    {
        int u = cond[i][0];
        int v = cond[i][1];
        // 插入边 u->v
        ArcNode* p = new ArcNode;
        p->adjvex = v;
        p->next = G.AdjList[u].first;
        G.AdjList[u].first = p;
        G.AdjList[v].indegree++;
    }
}

// 拓扑排序
/**
 * @brief  使用 Kahn 算法对有向图进行拓扑排序
 * @param  G        有向图（邻接表）
 * @param  sorted   拓扑排序结果数组
 * @return 是否存在合法拓扑序（是否无环）
 */
bool topological_sort(ALGraph& G, int sorted[]) 
{
    int top = -1;   // 模拟栈顶指针，-1 表示当前栈为空
    // 第一步：将所有入度为 0 的结点入栈
    for (int i = 1; i <= G.vexnum; ++i) 
    {
        if (G.AdjList[i].indegree == 0) 
        {
            G.AdjList[i].stack_link = top; // 当前结点指向原来的栈顶
            top = i;                       // 更新栈顶
        }
    }
    int count = 0;   // 已输出到拓扑序列中的结点个数
    // 第二步：不断弹出入度为 0 的结点
    while (top != -1) 
    {
        int i = top;                    // 取出当前栈顶结点
        top = G.AdjList[i].stack_link;  // 栈顶下移（模拟 pop）
        sorted[count++] = i;            // 将该结点加入拓扑序列
        // 第三步：删除该结点的所有出边
        ArcNode* p = G.AdjList[i].first;
        while (p) 
        {
            int k = p->adjvex;          // k 为 i 指向的后继结点
            G.AdjList[k].indegree--;    // 删除边 i -> k，相当于入度减 1
            if (G.AdjList[k].indegree == 0) 
            {
                G.AdjList[k].stack_link = top;
                top = k;                // 新产生的入度为 0 的结点入栈
            }
            p = p->next;
        }
    }
    // 若所有结点都被输出，则说明无环
    return count == G.vexnum; // true: 拓扑排序成功
}

int main() 
{
    int k, n, m;
    cin >> k >> n >> m;

    int row_cond[n][2];
    int col_cond[m][2];
    for (int i = 0; i < n; ++i) 
        cin >> row_cond[i][0] >> row_cond[i][1];
    for (int i = 0; i < m; ++i) 
        cin >> col_cond[i][0] >> col_cond[i][1];

    ALGraph G_row, G_col;
    build_graph(G_row, k, n, row_cond);
    build_graph(G_col, k, m, col_cond);

    int row_order[k+1], col_order[k+1];
    if (!topological_sort(G_row, row_order)) 
    {
        cout << -1 << endl;
        cleanup_graph(G_row);
        cleanup_graph(G_col);
        return 0;
    }
    if (!topological_sort(G_col, col_order)) 
    {
        cout << -1 << endl;
        cleanup_graph(G_row);
        cleanup_graph(G_col);
        return 0;
    }

    // 数字 到 行/列映射
    int row_pos[k+1], col_pos[k+1]; 
    // 为了方便直接使用题目中 1～k 的编号作为数组下标，避免频繁进行 ±1 转换，
    // 行列映射数组统一开为 k+1 大小，其中下标 1～k 分别对应数字 1～k
    for (int i = 0; i < k; ++i)
        row_pos[row_order[i]] = i;
    for (int i = 0; i < k; ++i) 
        col_pos[col_order[i]] = i;

    // 构建矩阵
    int matrix[k][k] = {0};
    for (int num = 1; num <= k; ++num) 
    {
        int r = row_pos[num];
        int c = col_pos[num];
        matrix[r][c] = num;
    }

    // 输出
    for (int i = 0; i < k; ++i) 
    {
        for (int j = 0; j < k; ++j) 
        {
            cout << matrix[i][j] << (j == k-1 ? "\n" : " ");
        }
    }

    cleanup_graph(G_row);
    cleanup_graph(G_col);
    return 0;
}
