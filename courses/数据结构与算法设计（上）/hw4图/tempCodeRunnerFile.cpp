#include<iostream>
#include<vector>
using namespace std;
int map[5][5]={
    {0,1,1,0,1},
    {1,0,1,0,1},
    {1,1,0,1,1},
    {0,0,1,0,1},
    {1,1,1,1,0}
}; //邻接矩阵
int visited_edge[5][5]={0}; //记录边被访问的次数
vector<int>path; //存储当前找到的欧拉路径（顶点序列）

/**
 * @brief 深度优先搜索函数，用于寻找欧拉路径
 * @param u 当前节点
 * @param visited_count 已经遍历过的边数
 */
void DFS(int u,int visited_count)
{
    //1.记录当前顶点
    path.push_back(u);
    //终止条件：已访问的边数>=总边数
    if(visited_count>=8)
    {
        //欧拉路径的存在条件是图中只有0个或2个奇数度顶点
        //如果有 0 个奇数度顶点，则存在欧拉回路（起点 = 终点）
        //如果有 2 个奇数度顶点，则存在欧拉路径，且这条路径必须从一个奇数度顶点开始，并在另一个奇数度顶点结束
        if(path[0]==0&&path.back()==1)
        {
            for(size_t i=0;i<path.size();i++)
                cout<<path[i]+1; //输出找到的欧拉路径
            cout<<endl;
        }
        path.pop_back(); 
        //回溯：当DFS函数执行完后，必须撤销它对 path 的修改，以便上一个顶点（调用它的函数）可以继续尝试其他路径
        return;
    }
    //遍历当前节点u所有可能的邻居
    for(int v=0;v<5;v++)
    {
        if(map[u][v]==1&&visited_edge[u][v]==0)
        {
            //标记该边访问
            visited_edge[u][v]++;
            visited_edge[v][u]++; //注意无向图两者都要+1！
            DFS(v,visited_count+1);
        }
    }
    path.pop_back(); //回溯，返回u
}
int main()
{
    DFS(0,0);
    return 0;
}