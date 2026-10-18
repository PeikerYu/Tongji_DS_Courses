#include<iostream>
using namespace std;
struct LNode{
    int data;
    LNode* next;
};
using LinkList = LNode*;

/* 
带头节点的单链表：
头节点存储链表中第一个位置数据元素的信息，因此不需要再对第一个节点做特殊处理
对空表与非空表的处理也统一了
*/

//取元素（按序号查找，直到找到第i个节点）
//1表示找到 0表示未找到
bool GetElem(LinkList L,int i,int &e)
{
    int j=1;
    LNode *p=L->next;
    while(p!=NULL&&j<i)
    {
        p=p->next;
        j++;
    }
    if(p==NULL||j>i)
        return 0;
    e=p->data;
    return 1;
}

//插入元素，在第i个位置处插入
bool ListInsert(LinkList &L,int i,int e)
{
    LNode *p=L;
    int j=0;
    while(p!=NULL&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(p==NULL||j>i-1)
        return 0;
    LNode* s=(LNode*)malloc(sizeof(LNode));
    s->data=e;
    //找到第i-1个节点，然后在之后插入
    s->next=p->next;
    p->next=s;
    return 1;
}

//删除元素
bool ListDelete(LinkList &L,int i,int e)
{
    LNode *p=L;
    int j=0;
    while(p->next!=NULL&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(p->next==NULL||j>i-1)
        return 0;
    LNode *q=p->next;
    p->next=q->next;
    e=q->data;
    free(q);
    return 1;
}

//头插法建立链表，节点次序与输入次序相反
void CreateList(LinkList &L,int n)
{
    LNode* p;
    L=(LNode*)malloc(sizeof(LNode));
    L->next=NULL;
    for(int i=n;i>0;i--)
    {
        p=(LNode*)malloc(sizeof(LNode));
        cin>>p->data;
        p->next=L->next;
        L->next=p;
    }
}

//尾插法建立链表
void CreateList_Tail(LinkList &L,int n)
{
    LNode* p,* r;  //r为尾指针
    r=(LNode*)malloc(sizeof(LNode));
    L=(LNode*)malloc(sizeof(LNode));
    L->next=NULL;
    r=L;
    for(int i=0;i<n;i++)
    {
        p=(LNode*)malloc(sizeof(LNode));
        cin>>p->data;
        p->next=NULL; //新创建的节点一定是尾节点
        r->next=p; 
        r=p; //尾指针后移
    }
}

void MergeList(LinkList &La,LinkList &Lb,LinkList &Lc)
{
    LNode* pa,*pb,*pc;
    pa=La->next; // 第一个数据结点
    pb=Lb->next;
    Lc=pc=La;
    while(pa&&pb)
    {
        if(pa->data<=pb->data)
        {
            pc->next=pa; //尾插法
            pc=pa;
            pa=pa->next;
        }
        else
        {
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    }
    while(pa)
    {
        pc->next=pa; //尾插法
        pc=pa;
        pa=pa->next;
    }
    while(pb)
    {
        pc->next=pb;
        pc=pb;
        pb=pb->next;
    }
}

void OrderInsert(LinkList &L,int e) //按递增顺序插入
{
    LNode* p=L->next; // 第一个数据结点
    LNode* q=L; // 前驱，从头结点开始
    while(p!=NULL&&p->data<e)
    {
        q=p;
        p=p->next;
    }
    LNode* t=(LNode*)malloc(sizeof(LNode));
    t->data=e;
    t->next=p;
    q->next=t;
}

void Destroy(LinkList &L) //销毁
{
    LNode* p=L; //头节点一并删除
    while(L)
    {
        p=p->next;
        free(L);
        L=p;
    }
}

void ClearList(LinkList L) //清空
{
    LNode* p=L->next;  //从第一个数据元素开始删除
    LNode* q;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL;
}

bool PriorList(LinkList L,int cur_e,int &pre_e) //找前驱
{
    LNode* p=L->next;
    LNode* q;
    if(p==NULL)
        return 0;
    while(p->next!=NULL) //p所指节点有后继
    {
        q=p->next;
        if(q->data==cur_e)
        {
            pre_e=p->data;
            return 1;
        }
        p=q;
    }
}

bool NextList(LinkList L,int cur_e,int &next_e) //找后继
{
    LNode* p=L->next;
    LNode* q;
    if(p==NULL)
        return 0;
    while(p->next!=NULL) //p所指节点有后继
    {
        q=p->next;
        if(p->data==cur_e)
        {
            next_e=q->data;
            return 1;
        }
        p=q;
    }
}

/*
接下来是循环链表的操作：将最后一个节点的next指针不指向0而是指向表头节点
循环条件：p->next!=H
带头结点
*/

void Merge(LinkList &La,LinkList &Lb) //循环链表的合并 时间复杂度：O(m+n)
{
    LNode*p=La;
    while(p->next!=La)
        p=p->next;
    p->next=Lb->next;
    while(p->next!=Lb)
        p=p->next;
    p->next=La;
    free(Lb);
}

void CreateList2(LinkList &L,int n)
{
    LNode* p;
    L=(LNode*)malloc(sizeof(LNode));
    L->next=L; //这是循环链表与单链表的一个不同之处！
    for(int i=n;i>0;i--)
    {
        p=(LNode*)malloc(sizeof(LNode));
        cin>>p->data;
        p->next=L->next;
        L->next=p;
    }
}

/*
下面是对双向循环链表的操作
其最大优势在于头尾不需特判
带头节点
*/
struct DuLNode{
    int data;
    DuLNode *prior;
    DuLNode *next;
};
using DuLinkList=  DuLNode* ;

void CreateDuList(DuLinkList &L,int n) //创建双向循环链表
{
    DuLinkList p;
    L=p=(DuLNode*)malloc(sizeof(DuLNode));
    L->next=L;
    L->prior=L; //初始化为空的双向循环链表
    for(int i=n;i>0;i--)
    {
        p->next=(DuLNode*)malloc(sizeof(DuLNode));
        cin>>p->data;
        p->next->prior=p;
        p=p->next;
        //把尾结点和头结点重新连起来，形成“循环”
        p->next=L;
        L->prior=p;
    }
}

//插入元素，在第i个位置处插入
bool DuListInsert(DuLinkList &L,int i,int e)
{
    DuLNode *p=L;
    int j=0;
    while(p->next!=L&&j<i-1) //与单链表不同的地方
    {
        p=p->next;
        j++;
    }
    if(p->next==L||j!=i-1)
        return 0;
    DuLNode* s=(DuLNode*)malloc(sizeof(DuLNode));
    s->data=e;
    //找到第i-1个节点，然后在之后插入
    s->prior=p;
    s->next=p->next;
    //下面这两句不能交换位置！！！
    p->next->prior=s;
    p->next=s;
    return 1;
}

//删除元素,删除第 i 个位置的元素
bool DuListDelete(DuLinkList &L,int i,int &e)
{
    DuLNode *p=L;
    int j=0;
    while(p->next!=L&&j<i-1)
    {
        p=p->next;
        j++;
    }
    if(p->next==L||j!=i-1)
        return 0;
    DuLNode *q=p->next;
    e=q->data;
    q->prior->next=q->next;
    q->next->prior=q->prior;
    free(q);
    return 1;
}

/*
链表实现之多项式：
*/
struct PolyNode
{
    int coef;   // 系数
    int expn;   // 指数
    PolyNode *next;
};
using Polynomial = PolyNode*;

void InitPoly(Polynomial &P) //初始化多项式
{
    P = (PolyNode*)malloc(sizeof(PolyNode));
    P->next = NULL;
}

void OrderInsertPoly(Polynomial &P, int coef, int expn) //按顺序插入
{
    PolyNode *p = P;
    PolyNode *q = P->next;

    // 找到第一个 expn >= 当前项 的位置
    while (q && q->expn < expn)
    {
        p = q;
        q = q->next;
    }

    // 情况1：指数相同，则系数相加
    if (q && q->expn == expn)
    {
        q->coef += coef;
        if (q->coef == 0)   // 系数为0，删除该项
        {
            p->next = q->next;
            free(q);
        }
    }
    else
    {
        // 情况2：指数大于当前项，则新建结点插入
        PolyNode *s = (PolyNode*)malloc(sizeof(PolyNode));
        s->coef = coef;
        s->expn = expn;

        s->next = q;
        p->next = s;
    }
}

void CreatePoly(Polynomial &P, int m) //创建多项式
{
    InitPoly(P);

    int c, e;
    for (int i = 0; i < m; i++)
    {
        cin >> c >> e;   // 输入 系数 指数
        OrderInsertPoly(P, c, e);
    }
}

void PrintPoly(Polynomial P) //打印多项式
{
    PolyNode *p = P->next;
    if (!p)
    {
        cout << "0";
        return;
    }

    while (p)
    {
        cout << p->coef << "x^" << p->expn;
        if (p->next) cout << " + ";
        p = p->next;
    }
    cout << endl;
}

void AddPoly(Polynomial &A, Polynomial B)
{
    PolyNode *pa = A->next;
    PolyNode *pb = B->next;
    PolyNode *pc = A;   // pc 始终指向 A 中的前驱

    while (pa && pb)
    {
        if (pa->expn < pb->expn)
        {
            pc = pa;
            pa = pa->next;
        }
        else if (pa->expn > pb->expn)
        {
            // 把 pb 插到 pc 后面
            PolyNode *t = pb->next;
            pb->next = pc->next;
            pc->next = pb;

            pc = pb;
            pb = t;
        }
        else
        {
            // 指数相等
            pa->coef += pb->coef;
            PolyNode *t = pb;
            pb = pb->next;
            free(t);

            if (pa->coef == 0)
            {
                pc->next = pa->next;
                free(pa); //详细解释见md
                pa = pc->next;
            }
            else
            {
                pc = pa;
                pa = pa->next;
            }
        }
    }

    // B 还有剩余，直接接到 A 后面
    if (pb)
        pc->next = pb;
}

//两个单增单链表合并成一个单减单链表：
LinkList Merge(LinkList La,LinkList Lb)
{
    LinkList Lc = (LinkList)malloc(sizeof(LNode));
    Lc->next=NULL;
    LNode* pa=La->next;
    LNode* pb=Lb->next;
    while(pa&&pb)
    {
        if(pa->data<pb->data)
        {
            LNode* ta=pa->next;
            pa->next=Lc->next;
            Lc->next=pa;
            pa=ta;
        }
        else if(pa->data>pb->data)
        {
            LNode* tb=pb->next;
            pb->next=Lc->next;
            Lc->next=pb;
            pb=tb;
        }
        else{
            //任选一个插入
            LNode* ta=pa->next;
            pa->next=Lc->next;
            Lc->next=pa;
            pa=ta;
            pb=pb->next;
        }
    }
    while(pa)
    {
        LNode* ta=pa->next;
        pa->next=Lc->next;
        Lc->next=pa;
        pa=ta;
    }
    while(pb)
    {
        LNode* tb=pb->next;
        pb->next=Lc->next;
        Lc->next=pb;
        pb=tb;
    }
    return Lc;
}

void EvenAndOdd(LinkList L)
{
    LinkList odd, even;
    odd = (LinkList)malloc(sizeof(LNode));
    even = (LinkList)malloc(sizeof(LNode));
    odd->next = NULL;
    even->next = NULL;
    LNode* p=L->next;
    while(p)
    {
        LNode*next=p->next;
        if(p->data%2!=0)
        {
            //有序插入奇数链表
            LNode* op=odd->next;
            LNode* op_pre=odd;
            while(op&&op->data<p->data)
            {
                op_pre=op;
                op=op->next;
            }
            p->next=op;
            op_pre->next=p;
        }
        else
        {
            LNode* ep=even->next;
            LNode* ep_pre=even;
            while(ep&&ep->data<p->data)
            {
                ep_pre=ep;
                ep=ep->next;
            }
            p->next=ep;
            ep_pre->next=p;
        }
        p=next;
    }
}

