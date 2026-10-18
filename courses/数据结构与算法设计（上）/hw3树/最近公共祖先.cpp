#include<iostream>
using namespace std;
struct TreeNode //树的节点
{
    int parent; //父节点索引
};

struct Tree //构造树
{
    int n; //有n个节点
    TreeNode *nodes; //节点数组
};

Tree createTree(int n) //初始化树
{
    Tree t;
    t.n=n;
    t.nodes=new TreeNode[n];
    for(int i=0;i<n;i++)
        t.nodes[i].parent=-1; //先全部初始化为-1，根节点
    return t;
}

int findLCA(Tree &tree,int x,int y) //寻找公共祖先函数
{
    bool visited[1005]={false};
    while(x!=-1) //标记x的所有祖先
    {
        visited[x]=true;
        x=tree.nodes[x].parent;
    }
    while(y!=-1)
    {
        if(visited[y]==true)
            return y; //若在y的祖先寻找过程中找到了标记过的x的祖先，则一定是两者公共祖先
        y=tree.nodes[y].parent;
    }
    return -1; //若循环结束没有找到，则是根节点
}

int main()
{
    int t; //t个测试样本
    cin>>t;
    for(int i=0;i<t;i++)
    {
        int n,m; //n个节点，m个问题
        cin>>n>>m;
        Tree tree=createTree(n); //初始化创建第i棵树
        for(int j=0;j<n-1;j++)
        {
            int idx1,idx2;
            cin>>idx1>>idx2;
            tree.nodes[idx2-1].parent=idx1-1; //让第一个节点成为第二个节点的子节点，注意节点编号从1开始
        }
        for(int k=0;k<m;k++)
        {
            int x,y;
            cin>>x>>y;
            int ans=findLCA(tree,x-1,y-1);
            cout<<ans+1<<endl;
        }
        delete[]tree.nodes; //释放内存
    }
    return 0;
}