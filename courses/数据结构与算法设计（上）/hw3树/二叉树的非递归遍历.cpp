#include<iostream>
#include<string>
#include<cstdlib> // for malloc, realloc, exit
#define MaxSize 100
#define STACKINCREMENT 10
using namespace std;

struct BiTNode //构造二叉树结点
{
    char data; //数据域
    struct BiTNode *lchild,*rchild;
};

//栈的相关操作
struct TStack //构造存放树节点的栈
{
    BiTNode **base;
    BiTNode **top;
    int stacksize;  //当前已分配的存储空间，单位是sizeof(元素)
};

int InitStack(TStack &S)  //栈初始化
{
    S.base=(BiTNode**)malloc(MaxSize*sizeof(BiTNode*));
    if(S.base==NULL) exit(1);
    S.top=S.base;
    S.stacksize=MaxSize;
    return 1;
}

int Push(TStack &S,BiTNode *e) //插入元素e为新的栈顶元素
{
    if((S.top-S.base)>=S.stacksize) //栈已满
    {
        S.base=(BiTNode**)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(BiTNode*));
        if(S.base==NULL) exit(1);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top=e;
    S.top++;
    return 1;
}

int Pop(TStack &S,BiTNode* &e) //删除栈顶元素并返回其值
{
    if(S.base==NULL)
    {
        return 0;
    }
    else if(S.base==S.top)
    {
        return 0;
    }
    else
    {
        S.top--;
        e=*S.top;
        return 1;
    }
}

int GetTop(TStack S,BiTNode* &e) //取栈顶元素
{
    if(S.base==NULL)
    {
        return 0;
    }
    else if(S.base==S.top)
    {
        return 0;
    }
    else
    {
        e=*(S.top-1);
        return 1;
    }
}

void PostOrder(BiTNode *root) //后序遍历函数（递归实现）
{
    if(root==NULL)
        return;
    else
    {
        PostOrder(root->lchild);//递归遍历左子树
        PostOrder(root->rchild);//递归遍历右子树
        cout<<root->data;
    }
}

int main()
{
    int n;
    cin>>n;
    if(n==0)
    {
        cout<<endl; //空树直接退出
        return 0;
    }
    TStack S; //创建栈用于存放节点指针
    InitStack(S);
    BiTNode *root=NULL; //创建整棵树的根节点
    BiTNode *pre=NULL; //创建跟踪当前节点的前驱指针
    for(int i=0;i<2*n;i++)
    {
        string oper;
        cin>>oper;
        if(oper=="push")
        {
            char val;
            cin>>val;
            BiTNode *newnode=new BiTNode();
            newnode->data=val;
            newnode->lchild=newnode->rchild=NULL;
            if(root==NULL) //如果是第一个节点，则将其设为根节点
                root=newnode;
            if(pre!=NULL)
            {
                if(pre->lchild==NULL) //如果前驱节点的左子树为空，则将新节点设为左子树，这对应于中序遍历中一路向左走的情况
                    pre->lchild=newnode;
                else //否则将新节点设为右子树，这对应于一个节点被pop后，开始处理其右子树的情况
                    pre->rchild=newnode;
            }
            pre=newnode; //更新前驱节点为当前新节点
            Push(S,newnode); //将新节点指针入栈
        }
        else //一个节点被pop，意味着它的左子树已经处理完了
            // 接下来如果再有push操作，一定是创建它的右孩子
            // 所以，我们将parent指向这个即将被pop的节点
        {
            GetTop(S,pre);
            BiTNode* temp;
            Pop(S,temp); 
        }
    }
    PostOrder(root); //调用后序遍历函数
    cout<<endl;
    free(S.base);
    return 0;
}





