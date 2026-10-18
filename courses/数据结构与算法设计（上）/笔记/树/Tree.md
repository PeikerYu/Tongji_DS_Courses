### 完全二叉树：可以用顺序数组的方法存放各节点，连续存储
![alt text](image-14.png)
![alt text](image-15.png)

```cpp
#include<iostream>
#define MaxSize 100
using namespace std;
typedef int ElemType; //假设定义 ElemType 为 int

二叉树的顺序存储
struct TreeNode
{
    ElemType value; //节点中的数据元素
    bool isEmpty; //节点是否为空
};
TreeNode t[MaxSize]; //按照从上至下从左至右的顺序依次存储完全二叉树中的各个节点 
for (int i=0;i<MaxSize;i++) //初始将所有节点设为空值
{
    t[i].isEmpty=true;
}
```
![alt text](image.png)

如果不是完全二叉树呢？
以上规则不再适用，将非完全补充w为完全，用isEmpty判断是否存在左右孩子等
![alt text](image-1.png)
非常浪费空间！因此不怎么用顺式存储

### 二叉树的链式存储
```cpp
struct BiTNode
{
    ElemType data; //数据域
    BiTNode *lchild,*rchild,*parent;(这个父指针看情况写不写，加上就是三叉链表否则就是二叉链表)
};
BiTNode *root = NULL;

//插入根节点
root=(BiNode*)malloc(sizeof(BiTNode)); 
root->data=1;
root->lchild=NULL;
root->rchild=NULL;

//插入新节点
BiTNode * p=(BiTNode*)malloc(sizeof(BiTNode));
p->data=2;
p->lchild=NULL;
p->rchiled=NULL;
root->lchild=p;
```

### 二叉树的三种遍历（空间复杂度为O（n））
先序遍历：每个节点都会被路过三次，第一次路过时访问该节点
```cpp
void PreOrder(BiTNode *root)
{
    if(root==NULL)
        return;
    else
    {
        visit(root); //访问根节点
        PreOrder(root->lchild);//递归遍历左子树
        PreOrder(root->rchild);//递归遍历右子树
    }
}
```
![alt text](image-16.png)

中序遍历：每个节点都会被路过三次，第二次路过时访问该节点
（如果要找前驱和后继，要引入一个pre前驱指针，麻烦，详见中序线索二叉树）
```cpp
void InOrder(BiTNode *root)
{
    if(root==NULL)
        return;
    else
    {
        InOrder(root->lchild);//递归遍历左子树
        visit(root);
        InOrder(root->rchild);//递归遍历右子树
    }
}
```
后序遍历：每个节点都会被路过三次，第三次路过时访问该节点
![alt text](image-17.png)
```cpp
void PostOrder(BiTNode *root)
{
    if(root==NULL)
        return;
    else
    {
        PostOrder(root->lchild);//递归遍历左子树
        PostOrder(root->rchild);//递归遍历右子树
        visit(root);
    }
}
```
由遍历序列构造二叉树：
![alt text](image-3.png)
前序/后序/层序+中序才能确定

先序+中序：
![alt text](image-18.png)
```cpp
/**
 * @brief 根据前序遍历序列和中序遍历序列构造二叉树。
 *
 * @param preOrder 前序遍历序列数组
 * @param inOrder  中序遍历序列数组
 * @param preStart 前序序列的起始索引
 * @param preEnd   前序序列的结束索引
 * @param inStart  中序序列的起始索引
 * @param inEnd    中序序列的结束索引
 * @return BiTNode* 构造出的子树的根结点
 */
BiTNode* BuildTree_PreIn(char preOrder[], char inOrder[], int preStart, int preEnd, int inStart, int inEnd)
{
    // 递归终止条件：序列为空，即子树为空
    if (preStart > preEnd || inStart > inEnd) 
    {
        return NULL;
    }

    // 1. 前序序列的第一个元素 preOrder[preStart] 是当前子树的根结点
    BiTNode *root = new BiTNode;
    root->data = preOrder[preStart];
    root->lchild = NULL;
    root->rchild = NULL;

    // 2. 在中序序列中找到根结点的位置（划分左右子树）
    int rootInIndex;
    for (rootInIndex = inStart; rootInIndex <= inEnd; rootInIndex++) 
    {
        if (inOrder[rootInIndex] == root->data) 
        {
            break;
        }
    }
    
    // 3. 计算左子树的结点数量
    int leftSubtreeSize = rootInIndex - inStart;

    // 4. 递归构造左子树
    root->lchild = BuildTree_PreIn(preOrder, inOrder,
                                   preStart + 1,          // 前序：根之后紧接着是左子树的根
                                   preStart + leftSubtreeSize,// 前序：左子树结束的位置
                                   inStart,                   // 中序：左子树起始
                                   rootInIndex - 1);          // 中序：左子树结束

    // 5. 递归构造右子树
    root->rchild = BuildTree_PreIn(preOrder, inOrder,
                            preStart + leftSubtreeSize + 1, // 前序：左子树之后是右子树的根
                            preEnd,                         // 前序：右子树结束
                            rootInIndex + 1,                // 中序：右子树起始
                            inEnd);                         // 中序：右子树结束

    return root;
}
```
后序+中序：
```cpp
BiTNode* BuildTree_PostIn(char postOrder[], char inOrder[], int postStart, int postEnd, int inStart, int inEnd)
{
    // 递归终止条件：序列为空，即子树为空
    if (postStart > postEnd || inStart > inEnd) 
    {
        return NULL;
    }

    BiTNode *root = new BiTNode;
    root->data = postOrder[postEnd];
    root->lchild = NULL;
    root->rchild = NULL;

    // 2. 在中序序列中找到根结点的位置（划分左右子树）
    int rootInIndex;
    for (rootInIndex = inStart; rootInIndex <= inEnd; rootInIndex++) 
    {
        if (inOrder[rootInIndex] == root->data) 
        {
            break;
        }
    }
    
    // 3. 计算左子树的结点数量
    int leftSubtreeSize = rootInIndex - inStart;

    // 4. 递归构造左子树
    root->lchild = BuildTree_PreIn(postOrder, inOrder,
                            postStart, // 后序：左子树起始
                            postStart + leftSubtreeSize-1,    // 后序：左子树结束的位置
                            inStart,                   // 中序：左子树起始
                            rootInIndex - 1);          // 中序：左子树结束

    // 5. 递归构造右子树
    root->rchild = BuildTree_PreIn(postOrder, inOrder,
                            postStart + leftSubtreeSize, // 后序：右子树起始
                            postEnd-1,                   // 后序：右子树结束
                            rootInIndex + 1,             // 中序：右子树起始
                            inEnd);                      // 中序：右子树结束

    return root;
}
```
非递归的先序遍历：
注意！栈里存放的是二叉链表的节点指针
![alt text](image-21.png)
```cpp
算法1：保存右子树
void preOrder(BiTree T)
{
    SqStack S;
    BiTree P=T;
    InitStack(S);
    Push(S,NULL); //压在栈底作“监视哨”
    while(P)
    {
        visit(P);
        if(P->rchild)
            Push(S,P->rchild);
        if(P->lchild)
            P=P->lchild;
        else
            Pop(S,P);
    }
}

算法2：保存根节点
void preOrder(BiTree T)
{
    SqStack S;
    BiTree P=T;
    InitStack(S);
    while(P||!S.IsEmpty())
    {
        if(P)
        {
            visit(P);
            Push(S,P);
            P=P->lchild;
        }
        else
        {
            Pop(S,P);
            P=P->rchild;
        }
    }
}
```
非递归的中序遍历：
![alt text](image-22.png)
```cpp
void inOrder(BiTree T)
{
    stack<BiTree>S;
    BiTree P=T;
    while(P||!S.empty())
    {
        if(P)
        {
            S.push(P);
            P=P->lchild;
        }
        else
        {
            S.pop();
            visit(P);
            P=P->rchild;
        }
    }
}
```
非递归的后序遍历：
太难了，学不会了，不码了

先序建立二叉树的递归算法：
```cpp
bool CreateBiTree(BiTree &T)
{
    char ch;
    cin>>ch;
    if(ch=='#') T=NULL; //该节点为空
    else
    {
        T=(BiTNode*)malloc(sizeod(TNode))
        T->data=ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return true;
}
```
### 三种遍历的第一个和最后一个节点
![alt text](image-19.png)
![alt text](image-23.png)
![alt text](image-24.png)
```cpp
BiTNode* First_Pre(BiTree T)
{
    return T;  // 根
}

BiTNode* Last_Pre(BiTree T)
{
    if (!T) return nullptr;

    BiTNode* p = T;
    while (p->lchild || p->rchild) {
        if (p->rchild) p = p->rchild;
        else           p = p->lchild;
    }
    return p;
}

BiTNode* First_In(BiTree T)
{
    if (!T) return nullptr;
    BiTNode* p = T;
    while (p->lchild) p = p->lchild;
    return p;
}

BiTNode* Last_In(BiTree T)
{
    if (!T) return nullptr;
    BiTNode* p = T;
    while (p->rchild) p = p->rchild;
    return p;
}

BiTNode* First_Post(BiTree T)
{
    if (!T) return nullptr;

    BiTNode* p = T;
    while (p->lchild || p->rchild) {
        if (p->lchild) p = p->lchild;
        else           p = p->rchild;
    }
    return p;
}

BiTNode* Last_Post(BiTree T)
{
    return T;  // 根
}

```
### 二叉树的应用
计算二叉树深度：
```cpp
int Depth(BiTree T)
{
    int depl,depr;
    if(T)
    {
        depl=Depth(T->lchild);
        depr=Depth(T->rchild);
        if(depl>depr)
            return depl+1;
        else
            return depr+1;
    }
    return 0;
}
```
求二叉树节点个数：
```cpp
int Size(BiTree T)
{
    if(T==NULL) 
        return 0;
    else
        return 1+Size(T->lchild)+Size(T->rchild);
}
```
复制二叉树：
```cpp
void CopyTree(BiTree T,BiTree &T1)
{
    if(T)
    {
        T1=(BiTree)malloc(sizeof(BiTNode));
        T1->data=T->data;
        T1->lchild=T1->rchild=NULL; //递归地调用 CopyTree 函数来填充这些 NULL 指针，从而确保新树和原树的每一个结点都是独立分配的。
        // T1->lchild=T->lchild;
        // T1->rchild=T->rchild; //新树和原树的子结点共享内存。修改T1子树的任何内容，都会影响到原树，这违反了“复制”的初衷。
        CopyTree(T->lchild,T1->lchild);
        CopyTree(T->rchild,T1->rchild);
    }
}
```
### 层次遍历：
![alt text](image-20.png)

二叉树的层次遍历
```cpp
//链式队列结点
struct LinkNode
{
    BiTNode *data; //队列结点存储的是二叉树结点指针而不是结点
    LinkNode *next;
}
struct LinkQueue
{
    LinkNode *front,*rear; //队头队尾
}
```
![alt text](image-2.png)
```cpp
void LevelOrder(BiTNode *root)
{
    LinkQueue Q;
    InitQueue(Q);
    BiTNode *p;
    EnQueue(Q,root); //根节点入队
    while(!IsEmpty(Q))
    {
        DeQueue(Q,p); //队头节点出队
        visit(p);
        if(p->lchild!=NULL) //左孩子入队
            EnQueue(Q,p->lchild);
        if(p->rchild!=NULL) //右孩子入队
            EnQueue(Q,p->rchild);
    }
}
```    

### 线索二叉树
线索二叉树做的事就是：把这些“原本为 NULL 的指针域”利用起来。

如果某结点没有左孩子，那它的 lchild 不再空着，而是用来指向它在某种遍历序列中的前驱（前一个结点）

如果某结点没有右孩子，那它的 rchild 用来指向它在遍历序列中的后继（后一个结点）

例如：中序线索二叉树
![alt text](image-4.png)
指向前驱、后继的指针称为线索
也可以实现从后向前遍历
线索树遍历操作优于非线索树，遍历不用设栈。

### 线索二叉树的存储：
```cpp
struct ThreadNode
{
    ElemType data;
    ThreadNode *lchild,*rchild;
    int ltag,rtag; //左右线索标志 tag==1表示指针是线索，tag为0表示指针指向孩子
};
```
### 二叉树线索化
![alt text](image-31.png)
![alt text](image-32.png)
![alt text](image-33.png)
```cpp
ThreadNode *pre=NULL; //全局变量，指向当前访问节点的前驱

void InThread(ThreadNode *root)
{
    if(root==NULL)
        return;
    else
    {
        //在先序遍历中还要在先序遍历左孩子时加上条件：if(root->ltag==0)
        InThread(root->lchild);//递归遍历左子树
        visit(root);
        InThread(root->rchild);//递归遍历右子树
    }
}
//一遍遍历一遍处理节点
void visit(ThreadNode *q)
{
    if(q->lchild==NULL)
    {
        q->lchild=pre;
        q->ltag=1;
    }
    if(pre!=NULL&&pre->rchild==NULL)
    {
        pre->rchild=q;
        pre->rtag=1;
    }
    pre=q;
}
//构造中序线索化二叉树
void CreateInThread(ThreadNode *root)
{
    pre=NULL;
    if(root!=NULL)
    {
        InThread(root); //非空二叉树才能线索化
        if(pre->rchild==NULL)
            pre->rtag=1; //处理遍历的最后一个节点
    }
}
```
![alt text](image-5.png)
![alt text](image-6.png)   

#### 线索二叉树找前驱与后继：
中序：
![alt text](image-10.png)
![alt text](image-11.png)

先序：
![alt text](image-26.png)

后序：
![alt text](image-28.png)

#### 线索二叉树的遍历（其实上面王道的已经给过了，下面给老师的ppt的）
遍历的思想就是：
1.先找到遍历的第一个节点 2.一直找当前节点的后继
在线索二叉树中，只有两个空指针域：第一个节点的左孩子&最后一个节点的右孩子

中序：
![alt text](image-25.png)

先序：
![alt text](image-27.png)

后序：
![alt text](image-29.png)
![alt text](image-30.png)

### 树
树的定长结构：
```cpp
//定长结构：每个节点分配的内存空间大小一致，不可改变
struct dNode
{
    int data;
    dNode* child[N];
};
//不定长：每个节点动态分配内存空间
struct dNode
{
    int data;
    int degree;
    dNode** child;
};
```
树的存储方式1--双亲表示法（顺序存储）
存储森林则多几个下标为-1的
![alt text](image-8.png)
```cpp
#define MAX_TREE_SIZE 100
struct PTNode
{
    int parent;    //双亲位置域
    Elemtype data; //数据元素
}
struct PTree
{
    PTNode nodes[MAX_TREE_SIZE]; 
    int n; //节点数
}
```
树的存储方式2--孩子表示法（顺序存储与链式存储相结合）
存储森林则多几个没孩子的
![alt text](image-7.png)
```cpp
struct CTNode //每个树的节点的孩子节点
{
    int child;  //孩子节点在一个树的节点的孩子数组中的位置
    struct CTNode *next;
}
struct CTBox //每个树的节点
{
    ElemType data;
    CTNode *firstChild; //第一个孩子
}
struct CTree //树
{
    int n,r; //树的节点总数和根的位置
    CTBox nodes[MAX_TREE_SIZE]
}
```
树的存储方式3--孩子兄弟表示法
![alt text](image-9.png)
森林中每棵树的根节点视为平级的兄弟关系

### 哈夫曼树
哈夫曼树是满二叉树，有n个叶子节点，n-1个其他节点









### 其他
后缀表达式求值：
![alt text](image-12.png)
中缀表达式转后缀：
![alt text](image-13.png)

| 特点   | BFS（广度优先）           | DFS（深度优先）             |
| ---- | ------------------- | --------------------- |
| 访问顺序 | 按**层次**（一圈圈扩散）      | 一条路走到黑（再回溯）           |
| 结构   | **队列（Queue）**       | **栈（Stack）** 或 递归调用栈  |
| 常见用途 | 求最短路径 / 最小步数 / 分层传播 | 遍历整棵树 / 搜索所有路径 / 组合枚举 |
| 感觉类比 | “水波扩散”              | “迷宫探路”                |

