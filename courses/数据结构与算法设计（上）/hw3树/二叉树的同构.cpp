#include<iostream>
#include<string>
#include<cstdlib> // for malloc, realloc, exit
using namespace std;

struct BiTNode //构造二叉树结点
{
    char data; //数据域
    int l_id;
    int r_id; //左右孩子的下标索引
    BiTNode *lchild=nullptr;
    BiTNode *rchild=nullptr;
};

void BuildTree(BiTNode* &nodes,int n,BiTNode* &root) //根据输入建立节点之间的联系，找到根节点
{
    bool isChild[n]={0}; //用于标记节点是否为其他节点的孩子，用来找到根节点
    string l_id_s,r_id_s; //根据题目输入需要
    for(int i=0;i<n;i++)
    {
        cin>>nodes[i].data>>l_id_s>>r_id_s;
        if(l_id_s=="-")
            nodes[i].l_id=-1;
        else
            {nodes[i].l_id=stoi(l_id_s);isChild[nodes[i].l_id]=1;}
        if(r_id_s=="-")
            nodes[i].r_id=-1;
        else
            {nodes[i].r_id=stoi(r_id_s);isChild[nodes[i].r_id]=1;}
    }

    for(int i=0;i<n;i++) //根据下标索引建立节点之间的关系
    {
        if(nodes[i].l_id!=-1)
            nodes[i].lchild=&nodes[nodes[i].l_id];
        if(nodes[i].r_id!=-1)
            nodes[i].rchild=&nodes[nodes[i].r_id];
    }

    for(int i=0;i<n;i++) //找到根节点
    {
        if(isChild[i]==0) //若根节点不为空
        {
            root=&nodes[i];
            break;
        }
    }
}

bool isIsomorphic(BiTNode* root1, BiTNode* root2)
{
    if(root1 == nullptr && root2 == nullptr)
        return true;
    if(root1 == nullptr || root2 == nullptr)
        return false;
    if(root1->data != root2->data)
        return false;

    // 情况1：不交换左右孩子
    bool same = isIsomorphic(root1->lchild, root2->lchild)
             && isIsomorphic(root1->rchild, root2->rchild);

    // 情况2：交换左右孩子
    bool swapped = isIsomorphic(root1->lchild, root2->rchild)
                && isIsomorphic(root1->rchild, root2->lchild);

    return same || swapped;
}


int depth(BiTNode* root) //计算二叉树深度
{
    if(root==nullptr)
        return 0;
    else
    {
        int ldepth=depth(root->lchild);
        int rdepth=depth(root->rchild);
        return (ldepth>rdepth)?(ldepth+1):(rdepth+1);
    }
}

int main()
{
    int n1,n2;
    cin>>n1;
    BiTNode* nodes_1=new BiTNode[n1+1]; //创建节点数组1
    BiTNode* root1=nullptr; //定义根节点
    BuildTree(nodes_1,n1,root1); //建立树1
    cin>>n2;
    BiTNode* nodes_2=new BiTNode[n2+1]; //创建节点数组2
    BiTNode* root2=nullptr; 
    BuildTree(nodes_2,n2,root2); //建立树2
    if(isIsomorphic(root1,root2))
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;
    cout<<depth(root1)<<endl;
    cout<<depth(root2)<<endl;
    return 0;
}
