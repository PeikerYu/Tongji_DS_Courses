#include<iostream>
#include<climits>
#include <cstdlib>
using namespace std;
#define MAX_VERTEX_NUM 100 //最大顶点个数
#define INFINITY INT_MAX //带权图中无边的顶点之间权值用无穷表示
typedef char VertexType; //顶点的数据类型
typedef int EdgeType; //带权图中边上权值的数据类型
//邻接矩阵法：
struct VNode
{
    VertexType data; //存储顶点信息
    //其他信息
};

struct UDMGraph //无权图
{
    VNode Vex[MAX_VERTEX_NUM]; //顶点表
    bool Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //边表：邻接矩阵
    int vexnum,arcnum; //图当前的顶点数与边数
};

struct WDMGraph //带权图（网）
{
    VNode Vex[MAX_VERTEX_NUM]; //顶点表
    EdgeType Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //边表：邻接矩阵
    int vexnum,arcnum; //网当前的顶点数与边数
};

int LocateVex(UDMGraph G,VertexType u) //根据节点数据定位下标
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(u==G.Vex[i].data)
            return i;
    }
    if(i==G.vexnum)
    {
        cout<<"Error u!\n";
        exit(1);
    }
    return 0;
}

int LocateVex(WDMGraph G,VertexType u) //根据节点数据定位下标
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        // if(u==G.Vex[i].data)
            return i;
    }
    if(i==G.vexnum)
    {
        cout<<"Error u!\n";
        exit(1);
    }
    return 0;
}

void CreateUDMGraph(UDMGraph &G) //初始化无权图
{
    cout<<"请输入顶点数与边数：\n";
    cin>>G.vexnum>>G.arcnum;
    cout<<"请输入顶点具体信息：\n";
    for(int i=0;i<G.vexnum;i++)
        cin>>G.Vex[i].data;
    for(int i=0;i<G.vexnum;i++)
        for(int j=0;j<G.vexnum;j++)
            G.Edge[i][j]=0; //初始化
    VertexType v1,v2;
    int i,j; //输入的顶点的下标
    for(int k=0;k<G.arcnum;k++)
    {
        cout<<"请输入顶点1 顶点2，在之间建立边\n";
        cin>>v1>>v2;
        i=LocateVex(G,v1);
        j=LocateVex(G,v2);
        G.Edge[i][j] = 1;  
        G.Edge[j][i] = 1;  
    }
    return;
}

void CreateWDMGraph(WDMGraph &G) //初始化带权图
{
    cout<<"请输入顶点数与边数：\n";
    cin>>G.vexnum>>G.arcnum;
    cout<<"请输入顶点具体信息：\n";
    for(int i=0;i<G.vexnum;i++)
        // cin>>G.Vex[i].data;
    for(int i=0;i<G.vexnum;i++)
        for(int j=0;j<G.vexnum;j++)
            // G.Edge[i][j]=INFINITY; //初始化
    VertexType v1,v2;
    EdgeType w;
    int i,j; //输入的顶点的下标
    for(int k=0;k<G.arcnum;k++)
    {
        cout<<"请输入顶点1 顶点2之间的边：\n";
        // cin>>v1>>v2>>w;
        // i=LocateVex(G,v1);
        // j=LocateVex(G,v2);
        // G.Edge[i][j]=w;
        // G.Edge[j][i]=w; //注意有向图和无向图此句不一样
    }
    return;
}

//邻接表法：
struct ArcNode //边节点
{
    int adjvex; //与边关联的另一顶点的顶点下标
    ArcNode* next; //指向下一条弧的指针
    EdgeType info; //边权值
};

struct VNode2
{
    VertexType data; //存储顶点信息
    ArcNode *first; //指向第一条边的指针
    int indegree; //在拓扑排序中的入度
};

struct ALGraph //图
{
    VNode2 AdjList[MAX_VERTEX_NUM]; //邻接表
    int vexnum,arcnum; //图当前的顶点数与边数
};

int LocateVex(ALGraph G,VertexType u) //根据节点数据定位下标
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(u==G.AdjList[i].data)
            return i;
    }
    if(i==G.vexnum)
    {
        cout<<"Error u!\n";
        exit(1);
    }
    return 0;
}

void CreateALGraph(ALGraph &G) //邻接表的初始化
{
    ArcNode* p;
    cout<<"请输入顶点数与边数：\n";
    cin>>G.vexnum>>G.arcnum;
    cout<<"请输入各顶点具体信息：\n";
    for(int i=0;i<G.vexnum;i++)
    {
        cin>>G.AdjList[i].data;
        G.AdjList[i].first=NULL; //初始化置空
    }
    VertexType v1,v2;
    EdgeType w;
    int i,j; //输入的顶点的下标
    cout<<"请输入顶点1 顶点2，在之间建立边\n";
    for(int k=0;k<G.arcnum;k++)
    {
        cin>>v1>>v2>>w;
        i=LocateVex(G,v1);
        j=LocateVex(G,v2);
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=j;
        p->info=w; //以上存储好了信息，现在开始建立链表
        p->next=G.AdjList[i].first;
        G.AdjList[i].first=p;
        //若为无向图，则需要再次建立j与i之前的关联
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=i;
        p->info=w; //以上存储好了信息，现在开始建立链表
        p->next=G.AdjList[j].first; //头插法
        G.AdjList[j].first=p;
    }
}

//图的DFS算法
bool visited[MAX_VERTEX_NUM]={0}; //标记是否被访问过
void DFS(ALGraph G,int v) //从第v个顶点出发DFS，若是连通图则整个图都被遍历
{
    ArcNode* p;
    cout<<"从点"<<G.AdjList[v].data<<"开始遍历（DFS）\n";
    visited[v]=1;
    p=G.AdjList[v].first;
    while(p)
    {
        if(visited[p->adjvex]==0)
            DFS(G,p->adjvex);
        p=p->next;
    }
}

void DFSTraverse(ALGraph G) //整个图的DFS遍历（如果不是连通图）
{
    for(int v=0;v<G.vexnum;v++)
        if(visited[v]==0)
            DFS(G,v);
}

// void BFS(ALGraph G,int v)
// {
//     ArcNode* p;
//     cout<<"从点"<<G.AdjList[v].data<<"开始遍历（BFS）\n";
//     visited[v]=1;
//     SqQueue Q;
//     InitQueue(Q);
//     Q.base[Q.rear]=v;
//     Q.rear=(Q,rear+1)%MAXQSIZE;
//     while(Q.front!=Q.rear)
//     {
//         v=Q.base[Q.front];
//         Q.front=(Q.front+1)%MAXQSIZE;
//         p=G.AdjList[v].first;
//         while(p)
//         {
//             if(visited[p->adjvex]==0)
//             {
//                 cout<<G.AdjList[v].data;
//                 visited[p->adjvex]=1;
//                 Q.base[Q.rear]=p->adjvex;
//                 Q.rear=(Q.rear+1)%MAXQSIZE;
//             }
//             p=p->next;
//         }
//     }
// }

// void BFSTraverse(ALGraph G) //整个图的BFS遍历（如果不是连通图）
// {
//     for(int v=0;v<G.vexnum;v++)
//         if(visited[v]==0)
//             BFS(G,v);
// }

struct closedge
{
    EdgeType lowcost; //最小权值：对于未加入 MST 的顶点 j，closedge[j].lowcost 存储的是它到当前 MST 集合中所有顶点的边中，权值最小的那条边的权值。
    //一旦顶点 j 被加入 MST，它的 lowcost 会被设置为 0（这是算法中标记“已加入”的方式）。
    VertexType adjvex; //对于未加入 MST 的顶点 j，closedge[j].adjvex 存储的是与它形成 lowcost 那条边的已加入 MST 集合中的顶点。
};
void Prim(WDMGraph G,VertexType u)
{
    int k,j,i,minCost;
    closedge arr_closedge[MAX_VERTEX_NUM];
    k=LocateVex(G,u); //确定起始顶点u的下标k
    //初始化closedge数组，将其余顶点都暂时与k关联
    for(int j=0;j<G.vexnum;j++)
    {
        if(j!=k)
        {
            arr_closedge[j].adjvex=u;
            // arr_closedge[j].lowcost=G.Edge[k][j];
        }
    }
    arr_closedge[k].lowcost=0; //将k加入MST
    //最外层循环：一共有n-1条边循环n-1次
    for(int i=1;i<G.vexnum;i++) 
    {
        minCost=INFINITY;
        for(j=0;j<G.vexnum;j++) // 遍历所有顶点 j，寻找最小 lowcost
        {
            // 查找尚未加入 MST 集合 (lowcost != 0) 且 lowcost 最小的顶点 k
            if(arr_closedge[j].lowcost!=0&&arr_closedge[j].lowcost<minCost)
            {
                minCost=arr_closedge[j].lowcost;
                k=j; // 记录该顶点的下标 k
            }
        }
        if(minCost == INFINITY)
        {
            cout << "Graph is not connected!" << endl;
            return;
        }
        // cout << "(" << arr_closedge[k].adjvex << "," << G.Vex[k].data << ")" << endl;
        arr_closedge[k].lowcost=0;
        //更新arr_closedge数组
        for(int j=0;j<G.vexnum;j++)
        {
            // if(G.Edge[k][j]<arr_closedge[j].lowcost&&arr_closedge[j].lowcost != 0 ) // 如果通过新顶点 k 连接更短，小心边权值为0的情况
            {
                // arr_closedge[j].adjvex=G.Vex[k].data; // j 现在应该连接到 k
                // arr_closedge[j].lowcost=G.Edge[k][j]; // 更新为更小的权值
            }
        }
        
    }
}

bool toplogicalSort(ALGraph G) //拓扑排序
{
    ArcNode *p;
    int top=-1; //入度为0的顶点栈初始化
    int i;
   // FindIndegree(G.indegree);
    for(i=0;i<G.vexnum;i++)
    {
        if(G.AdjList[i].indegree==0)
        {
            G.AdjList[i].indegree=top;
            top=i; //入度为0的顶点进栈
        }
    }
    int count=0;
    while(top+1)
    {
        i=top;
        top=G.AdjList[top].indegree; //入度为0的顶点出栈
        cout<<i<<" "<<G.AdjList[i].data;
        ++count;
        for(p=G.AdjList[i].first;p;p=p->next) //扫描该顶点的出边表
        {
            int k=p->adjvex; //边的另一顶点
            G.AdjList[k].indegree--; //该顶点入度减一
            if(G.AdjList[k].indegree==0)
            {
                G.AdjList[k].indegree=top;
                top=k; //入度为0的顶点入栈
            }
        }
    }
    if(count<G.vexnum)
        return false; //有向环
    else
    return true;
} 

//最短路径问题
//Dijkstra算法：使用邻接矩阵实现
int Distance_DIJ[MAX_VERTEX_NUM]; //存储从源点到每个顶点的当前最短路径长度
int pre[MAX_VERTEX_NUM]; //存储在最短路径上顶点i的前驱顶点
bool final[MAX_VERTEX_NUM]; //标记顶点v的最终最短路径是否已经确定

struct VNode
{
    VertexType data; //存储顶点信息
    //其他信息
};

struct WDMGraph //带权图（网）
{
    VertexType Vex[MAX_VERTEX_NUM]; //顶点表
    int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //边表：邻接矩阵
    int vexnum,arcnum; //网当前的顶点数与边数
};

void ShortestPath_DIJ(WDMGraph G,int u0,int Distance_DIJ[],int pre[])
{
    int min_dist; //存储当前找到的最小距离
    for(int v=1;v<=G.vexnum;v++)
    {
        final[v]=0;
        Distance_DIJ[v]=G.AdjMatrix[u0][v]; //距离初始化为u0到v的边权
        pre[v]=(Distance_DIJ[v]<INFINITY)?u0:-1; //若可达，前驱是u0
    }
    Distance_DIJ[u0]=0;
    final[u0]=1;
    pre[u0]=-1;
    //遍历G.vexnum-1次，每次确定一个顶点的最短路径
    for(int i=1;i<G.vexnum;i++)
    {
        //1.找到当前Distance_DIJ[]中最小的未确定顶点
        min_dist=INFINITY;
        int u; //顶点下标
        for(int j=0;j<G.vexnum;j++)
        {
            if(final[j]==0&&Distance_DIJ[j]<min_dist)
            {
                u=j;
                min_dist=Distance_DIJ[j];
            }
        }
        final[u]=1;
        //2.以u为中介点，更新所有邻接点w的距离：是否通过u到达w的路径更短？
        for(int w=0;w<G.vexnum;w++)
        {
            // 确保 w 未被确定最终最短路径
            // 并且 u 到 w 是有边的 (G.AdjMatrix[u][w] < INFINITY)
            if(final[w]==0&&G.AdjMatrix[u][w]<INFINITY)
            {
                if(min_dist+G.AdjMatrix[u][w]<Distance_DIJ[w])
                {
                    Distance_DIJ[w]=min_dist+G.AdjMatrix[u][w];
                    pre[w]=u;
                }
            }
        }
    }
}

//Floyd算法


//利用关键路径法求AOE网络的关键活动
//邻接表法：
struct ArcNode //边节点
{
    int adjvex; //与边关联的另一顶点的顶点下标
    ArcNode* next; //指向下一条弧的指针
    EdgeType info; //边权值
};

struct VNode2
{
    VertexType data; //存储顶点信息
    ArcNode *first; //指向第一条边的指针
    int indegree; //在拓扑排序中的入度
};

struct ALGraph //图
{
    VNode2 AdjList[MAX_VERTEX_NUM]; //邻接表
    int vexnum,arcnum; //图当前的顶点数与边数
};
void CriticalPath(ALGraph G)
{
    VNode2* Ve=new VNode2[G.vexnum];
    VNode2* Vl=new VNode2[G.vexnum];

    for(int i=0;i<G.vexnum;i++)
        Ve[i].data=0;
    for(int i=0;i<G.vexnum;i++)
    {
        ArcNode *p=G.AdjList[i].first;
        while(p!=NULL)
        {
            int k=p->adjvex;
            if(Ve[i].data+p->info>Ve[k].data)
                Ve[k].data=Ve[i].data+p->info;
            p=p->next;
        }
    }
    //对每个顶点的Vl初始化为汇点发生的最早时间
    for(int i=0;i<G.vexnum;i++)
        Vl[i].data=Ve[G.vexnum-1].data;
    for(int i=G.vexnum-2;i>0;i--)
    {
        ArcNode *p=G.AdjList[i].first;
        while(p!=NULL)
        {
            int k=p->adjvex;
            if(Vl[i].data>Vl[k].data-p->info)
                Vl[i].data=Vl[k].data-p->info;
            p=p->next;
        }
    }
    for(int i=0;i<G.vexnum;i++)
    {
        ArcNode *p=G.AdjList[i].first;
        while(p!=NULL)
        {
            int k=p->adjvex;
            int e=Ve[i].data;
            int l=Vl[k].data-p->info;
            if(e==l)
            //cout<<...
            p=p->next;
        }
    }
}