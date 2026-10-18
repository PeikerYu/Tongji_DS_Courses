#include<iostream>
using namespace std;
#define MAX_VERTEX_NUM 110 //最大顶点个数
#include<algorithm>
struct Edge
{
    int u,v; //连接边的两个顶点
    int w; //边的权值
};
struct WDMGraph //带权图（网）
{
    Edge Edge_stored[MAX_VERTEX_NUM*MAX_VERTEX_NUM]; //边表：存储各村庄之间的距离情况
    int vexnum,arcnum; //网当前的顶点数与边数
};

int parent[MAX_VERTEX_NUM]; //parent[i]表示i的父节点

/**
 * @brief  查找结点所在集合的根结点（路径压缩）
 * @param  x   当前结点
 * @return     x 所在集合的根
 */
//查找根节点
int Find(int x) 
{
    if(parent[x]!=x) //如果x的父节点不是自己，继续查找
        parent[x]=Find(parent[x]);
    return parent[x];
}

/**
 * @brief  合并两个结点所在的集合
 * @param  x   结点 x
 * @param  y   结点 y
 * @return     若成功合并返回 true，否则返回 false
 */
//合并两个集合
bool Union(int x, int y) 
{
    int rootX = Find(x);  // 找到x的根
    int rootY = Find(y);  // 找到y的根
    
    if (rootX == rootY)
        return false;  // 已经在同一组，不需要合并，否则会形成环
    
    parent[rootX] = rootY;  // 把x的根连到y的根上
    return true;  // 合并成功
}

/**
 * @brief  初始化带权图（WDMGraph），并把每个节点的父节点初始化为自己（为并查集做准备）
 * @param  G   待初始化的带权图结构
 * @param  n   图的顶点数量
 */
void CreateWDMGraph(WDMGraph &G,int n) //初始化带权图
{
    G.vexnum=n;
    int w;
    int edgenum=0;
    for(int i=0;i<G.vexnum;i++)
        for(int j=0;j<G.vexnum;j++)
        {
            cin>>w;
            // if(i<j) //无向图：只初始化上半边
            // {
                G.Edge_stored[edgenum].u=i;
                G.Edge_stored[edgenum].v=j;
                G.Edge_stored[edgenum].w=w;
                ++edgenum;
            // }
        }
    //初始化：每个元素的父节点是自己
    for(int i=0;i<n;i++) 
    {
        parent[i]=i;
    }     
    G.arcnum=edgenum;
    return;
}

bool cmp(Edge i,Edge j)
{
    return i.w<j.w;
}

int Kruskal(WDMGraph &G,int m) //利用Kruskal算法求出最小路径长度
{
    int a,b;
    for(int i=0;i<m;i++)
    {
        cin>>a>>b;
        Union(a-1,b-1);
    } 
    int total=0;
    int edgeAdded=0; //已加入MST的边数
    sort(G.Edge_stored,G.Edge_stored+G.arcnum,cmp);
    //最外层循环
    for(int i=0;i<G.arcnum;i++) 
    {
        int u=G.Edge_stored[i].u;
        int v=G.Edge_stored[i].v;
        int w=G.Edge_stored[i].w;
        if(Union(u,v))
        {
            total+=w;
            edgeAdded++;
            if(edgeAdded==G.vexnum-1)
                break;
        }
    }
    return total;
}

int main()
{
    int n;
    cin>>n;
    WDMGraph G;
    CreateWDMGraph(G,n);
    int m;
    cin>>m;
    int res=Kruskal(G,m);
    cout<<res;
    return 0;
}

