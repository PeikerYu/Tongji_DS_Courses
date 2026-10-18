#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define MAX_VERTEX_NUM 1010 //最大顶点个数

//邻接矩阵法：
struct UDMGraph //无向无权图
{
    int Vex[MAX_VERTEX_NUM]; //顶点表
    bool Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM]={0}; //边表：邻接矩阵
    int vexnum,arcnum; //图当前的顶点数与边数
};

/**
 * @brief 初始化无向无权图（邻接矩阵表示）
 * @param G 图结构体（引用传入，用于修改）
 * @param n 顶点个数（编号为 0 ~ n-1）
 * @param m 边的条数
 */
void CreateUDMGraph(UDMGraph &G,int n,int m) //初始化无权图
{
    int x1,x2;
    G.arcnum=m;
    G.vexnum=n;
    for(int i=0;i<m;i++)
    {
        cin>>x1>>x2;
        G.Edge[x1][x2]=1;
        G.Edge[x2][x1]=true;  // 修正：反向边，无向图必须对称
    }
}

bool visited[MAX_VERTEX_NUM]={0}; //标记是否被访问过
vector<vector<int>>arr; //存储所有联通分量


/**
 * @brief 从顶点 v 出发，使用 DFS 搜索一个连通分量
 * @param G 无向图（只读）
 * @param v 当前访问的顶点编号
 * @param arr1 用于存放当前连通分量中顶点的数组
 */
void DFS(const UDMGraph& G,int v,vector<int>&arr1) //DFS
{
    visited[v]=1;
    arr1.push_back(v);
    for(int j=0;j<G.vexnum;j++)
    {
        if(G.Edge[v][j]==1&&visited[j]==0)
            DFS(G,j,arr1);
    }
}

/**
 * @brief 使用 DFS 遍历整个图，找出所有连通分量
 * @param G 无向图
 * @return 无（结果存放在全局变量 arr 中）
 */
void DFSTraverse(const UDMGraph& G)
{
    //重置访问标记为0，并且清空存储在数组中的结果
    for(int i=0;i<G.vexnum;i++)
        visited[i]=0;
    arr.clear();
    //遍历所有顶点
    for(int v=0;v<G.vexnum;v++)
    {
        if(visited[v]==0)
        {
            vector<int>arr_curr;
            DFS(G,v,arr_curr);
            if(arr_curr.empty()!=1)
                arr.push_back(arr_curr);
        }
    }
}
   
void BFS(const UDMGraph& G,int v,vector<int>&arr1) //BFS
{
    queue<int>Q;
    Q.push(v);
    visited[v]=1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        arr1.push_back(k);
        for(int j=0;j<G.vexnum;j++)
        {
            if(G.Edge[k][j]==1&&!visited[j])
            {
                visited[j]=1;
                Q.push(j);
            }
        }
    }
}

void BFSTraverse(const UDMGraph& G)
{
    //重置访问标记为0，并且清空存储在数组中的结果
    for(int i=0;i<G.vexnum;i++)
        visited[i]=0;
    arr.clear();
    //遍历所有顶点
    for(int v=0;v<G.vexnum;v++)
    {
        if(visited[v]==0)
        {
            vector<int>arr_curr;
            BFS(G,v,arr_curr);
            if(arr_curr.empty()!=1)
                arr.push_back(arr_curr);
        }
    }
}


void Print()
{
    // 使用下标遍历 all_components
    for (size_t k = 0; k < arr.size(); k++)
    {
        // k 是当前连通分量的索引
        const vector<int>& component = arr[k];
        cout << "{";
        // 内部使用下标遍历 component
        for (size_t i = 0; i < component.size(); i++)
        {
            cout << component[i];
            if (i < component.size() - 1)
            {
                cout << " ";
            }
        }
        cout << "}";
    }
    cout << endl;
}

int main()
{
    int n,m; //顶点数和边数
    cin>>n>>m;
    UDMGraph G;
    CreateUDMGraph(G,n,m);
    DFSTraverse(G);
    Print();
    BFSTraverse(G);
    Print();
    return 0;
}