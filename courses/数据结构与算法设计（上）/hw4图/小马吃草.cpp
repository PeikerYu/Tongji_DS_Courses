#include <iostream>
#include <climits>
#include <queue>
using namespace std;
const int MAXN = 1005;
const int INF = INT_MAX;

struct ArcNode  //边节点
{
    int adjvex;  
    int weight;
    ArcNode* next_arc;
};
struct VNode  //顶点节点(牧场)
{
    ArcNode* first_arc;  
};
struct Graph //图
{
    VNode vertices[MAXN]; 
    int vexnum, arcnum;
};

int dis[MAXN][MAXN]; //存储第 i 个草点到所有其他牧场 j 的最短距离
int grass[MAXN]; //存放有牧草的点的下标

void InitGraph(Graph &G, int n, int m)  //图的初始化
{
    G.vexnum = n;
    G.arcnum = m;
    for (int i = 1; i <= n; ++i)
        G.vertices[i].first_arc = NULL;
}

void AddArc(Graph &G, int u, int v, int w)  //在一个vnode后面的边链中插入一个边节点（一条边）
{
    ArcNode* p = new ArcNode;
    p->adjvex = v;
    p->weight = w;
    p->next_arc = G.vertices[u].first_arc;
    G.vertices[u].first_arc = p;  
}

void Dijkstra(Graph& G,int start,int dist[])
{
    bool in_queue[MAXN]={0};
    for(int i=1;i<=G.vexnum;i++)
    {
        dist[i]=INF;
    }
    dist[start]=0;
    queue<int>q;
    q.push(start);
    in_queue[start]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        in_queue[u]=0;
        ArcNode*p=G.vertices[u].first_arc;
        while(p!=nullptr)
        {
            int v=p->adjvex;
            int w=p->weight;
            if(dist[v]>dist[u]+w)
            {
                dist[v]=dist[u]+w;
                if(!in_queue[v])
                {
                    q.push(v);
                    in_queue[v]=1;
                }
            }
            p=p->next_arc;
        }
    }
}

int main() 
{
    int n, m;
    cin >> n >> m;
    Graph G;
    InitGraph(G, n, m);

    for (int i = 0; i < m; ++i) 
    {
        int u, v, w;
        cin >> u >> v >> w;
        AddArc(G, u, v, w);
        AddArc(G, v, u, w); // 无向图
    }

    int H, R;
    cin >> H >> R;
    for (int i = 0; i < H; ++i)
        cin >> grass[i];

    // 每个草点跑一次 Dijkstra
    for (int i = 0; i < H; ++i) 
    {
        Dijkstra(G, grass[i], dis[i]);
    }

    // 每匹小马查询
    for (int i = 0; i < R; ++i) 
    {
        int s, t;
        cin >> s >> t;
        int ans = INF;
        for (int j = 0; j < H; ++j) 
        {
            if (dis[j][s] < INF && dis[j][t] < INF)
                ans = min(ans, dis[j][s] + dis[j][t]);
        } 
        cout << ans << "\n";
    }

    return 0;
}
