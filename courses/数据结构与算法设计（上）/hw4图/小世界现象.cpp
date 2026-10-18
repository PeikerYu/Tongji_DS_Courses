#include<iostream>
#include<queue>
#include<iomanip>
using namespace std;
#define MAX_VERTEX_NUM 2100
//邻接表法：
// 边节点：代表一条边，记录它连接的另一个顶点编号
struct ArcNode 
{
    int adjvex;     // 与边关联的另一顶点的顶点下标 (1到N)
    ArcNode* next;  // 指向下一条弧的指针
};

// 顶点入口节点：作为邻接链表的头
struct VNode 
{
    ArcNode *first; // 指向第一条边的指针
};

// 图的整体结构
struct ALGraph 
{
    VNode AdjList[MAX_VERTEX_NUM]; // 邻接表数组
    int vexnum, arcnum;            // 图当前的顶点数与边数
};

void BFS(ALGraph G,int start_node)
{
    queue<int>q;
    bool visited[MAX_VERTEX_NUM]={0};
    int distance[MAX_VERTEX_NUM]={0}; //存储起点到每个节点的最短距离
    int count=1; //记录距离<=6的节点数
    q.push(start_node);
    visited[start_node]=1;
    while(!q.empty())
    {
        int u=q.front(); //取出队首节点
        q.pop();
        int dist=distance[u]; //获取队首节点的最短距离
        if(dist>=6)
            continue; //若最短路径已到达6，那么邻居节点距离必然超过6，不再扩展，跳到下一个出队节点
        //通过邻接表遍历节点u的所有邻居v
        ArcNode *p=G.AdjList[u].first;
        while(p!=NULL)
        {
            int v=p->adjvex;
            if(!visited[v])
            {
                distance[v]=dist+1;
                visited[v]=1;
                count++;
                q.push(v);
            }
            p=p->next;
        }
    }
    double percentage=count*1.0/G.vexnum*100.0;
    cout<<start_node<<": "<<fixed<<setprecision(2)<<percentage<<"%"<<endl;
}

int main()
{
    int n,m;
    cin>>n>>m;
    ArcNode x1,x2;
    ALGraph G;
    G.vexnum=n;
    G.arcnum=m;
    for(int i=1;i<=n;i++) //初始化，让所有顶点的邻接表的头指针指向NULL
    {
        G.AdjList[i].first=NULL;
    }
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        //插入边（u,v）:在 u 的邻接链表头部插入 v
        ArcNode *p_uv=new ArcNode;
        p_uv->adjvex=v;
        p_uv->next=G.AdjList[u].first;
        G.AdjList[u].first=p_uv;
        //插入边（v,u）:在 v 的邻接链表头部插入 u
        ArcNode *p_vu=new ArcNode;
        p_vu->adjvex=u;
        p_vu->next=G.AdjList[v].first;
        G.AdjList[v].first=p_vu;
    }
    for(int i=1;i<=n;i++)
    {
        BFS(G,i);
    }
    return 0;
}
