#include<iostream>
#include<vector>
#define MAXSIZE 100
using namespace std;

struct TreeNode
{
    bool infected=0; //是否已被感染
    int lchild; //左孩子下标
    int rchild; //右孩子下标
    int parent; //父节点下标
};

struct Queue
{
    int data[MAXSIZE];
    int front;
    int rear;
};

//队列基本操作函数
void InitQueue(Queue &q) 
{
    q.front = q.rear = 0;
}

bool IsEmpty(Queue &q) 
{
    return q.front == q.rear;
}

void EnQueue(Queue &q, int x) 
{
    q.data[q.rear] = x;
    q.rear= (q.rear + 1) % MAXSIZE;
}

int DeQueue(Queue &q) 
{
    int val = q.data[q.front];
    q.front = (q.front + 1) % MAXSIZE;
    return val;
}

TreeNode* BuildTree(int n) //构建树节点的关系
{
    TreeNode* tree=new TreeNode[n];
    for (int i = 0; i < n; i++) 
    {
        tree[i].parent = -1; // 初始化所有节点的父节点为 -1
        tree[i].infected = false; // <<< 确保重置 infected 状态
    }
    for(int i=0;i<n;i++)
    {   
        cin>>tree[i].lchild>>tree[i].rchild;
        if(tree[i].lchild!=-1)
            tree[tree[i].lchild].parent=i;
        if(tree[i].rchild!=-1)
            tree[tree[i].rchild].parent=i;
    }
    return tree;
}

int time(TreeNode* tree,int start) //计算感染所需总时间
{
    Queue q;
    InitQueue(q);
    EnQueue(q,start);
    tree[start].infected=1;
    int time=-1; //从-1开始更为方便
    while(!IsEmpty(q))
    {
        int size = (q.rear - q.front + MAXSIZE) % MAXSIZE;
        for(int i=0;i<size;i++)
        {
            int curr=DeQueue(q);
            if(tree[curr].parent!=-1 && tree[tree[curr].parent].infected==0)
            {
                tree[tree[curr].parent].infected=1;
                EnQueue(q,tree[curr].parent);
            }
            if(tree[curr].lchild!=-1 && tree[tree[curr].lchild].infected==0)
            {
                tree[tree[curr].lchild].infected=1;
                EnQueue(q,tree[curr].lchild);
            }
            if(tree[curr].rchild!=-1 && tree[tree[curr].rchild].infected==0)
            {
                tree[tree[curr].rchild].infected=1;
                EnQueue(q,tree[curr].rchild);
            }
        }
        time++;
    }
    return time;
}
int main()
{
    int n,start;
    cin>>n>>start;
    TreeNode* tree=BuildTree(n);
    int total_time=time(tree,start);     
    cout<<total_time; //感染总时间比递归次数少1
    return 0;
}

