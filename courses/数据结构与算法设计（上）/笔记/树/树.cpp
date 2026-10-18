#include<iostream>
using namespace std;
#define N 5
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

//哈夫曼树
struct HTNode
{
    int weight;
    int parent,lchild,rchild;
};

