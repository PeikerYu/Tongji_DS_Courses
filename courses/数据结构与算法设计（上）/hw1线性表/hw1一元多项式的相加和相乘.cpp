#include<iostream>
#include<map>
using namespace std;
struct Node //链表结点：存储（系数，指数）
{
    long long p; //系数
    long long e; //指数
    Node *next;  //指向下一结点
};
Node *createNode(long long coef,long long exp) //创建结点
{
    Node*node=new Node; //动态分配结点
    node->p=coef;
    node->e=exp;
    node->next=nullptr;
    return node;
}
Node* Add(Node*p1,Node* p2) //多项式加法,双指针法
{
    Node* head=nullptr; //结果链表头
    Node* tail=nullptr; //结果链表尾
    while(p1!=nullptr&&p2!=nullptr)
    {
        Node* node=nullptr; //临时指针，如果需要插入则创建结点并赋值，不需要则为空值
        if(p1->e<p2->e) //p1指数小，将p1当前项插入结果链表
        {
            node=createNode(p1->p,p1->e);
            p1=p1->next; 
        }
        else if(p1->e>p2->e) //p2指数小，将p2当前项插入结果链表
        {
            node=createNode(p2->p,p2->e);
            p2=p2->next;
        }
        else //指数相等，系数相加
        {
            long long sum=p1->p+p2->p;
            if(sum!=0) //排除sum为0的情况
            {
                node=createNode(sum,p1->e);
            }
            p1=p1->next; //指针前移
            p2=p2->next;
        }
        if(node!=nullptr)
        {
            if(head==nullptr) //结果链表初始为空
            {
                head=node;
                tail=node;
            }
            else //结果链表初始不为空，尾指针后移
            {
                tail->next=node;
                tail=node;
            }
        }
    }
    //将剩余的p1全部接到结果链表之后
    while(p1!=nullptr)
    {
        Node* node=createNode(p1->p,p1->e);
        if(head==nullptr)
        {
            head=node;
            tail=node;
        }
        else
        {
            tail->next=node;
            tail=node;
        }
        p1=p1->next;
    }
    //将剩余的p2全部接到结果链表之后
    while(p2!=nullptr)
    {
        Node* node=createNode(p2->p,p2->e);
        if(head==nullptr)
        {
            head=node;
            tail=node;
        }
        else
        {
            tail->next=node;
            tail=node;
        }
        p2=p2->next;
    }
    return head;
}
// void insertTerm(Node*&head,long long coef,long long exp)
// {
//     if(coef==0)
//         return;
//     Node *newnode =new Node;
//     newnode->p=coef;
//     newnode->e=exp;
//     newnode->next=nullptr;
//     if(head==nullptr) //链表为空
//     {
//         head=newnode;
//         return;
//     }
//     if(exp<head->e) //插在表头之前
//     {
//         newnode->next=head;
//         head=newnode;
//         return;
//     }
//     Node*pre=nullptr;
//     Node*curr=head;
//     while(curr!=nullptr&&curr->e<exp)
//     {
//         pre=curr;
//         curr=curr->next;
//     }
//     if(curr!=nullptr&&curr->e==exp) //找到相同指数，合并系数
//     {
//         curr->p+=coef;
//         delete newnode;
//         if(curr->p==0) //若合并后系数为0，需要删除此节点
//         {   if(pre==nullptr)
//                 head=curr->next; //删除的是头结点
//             else
//                 pre->next=curr->next;
//             delete curr;
//         }
//         else //插在pre curr之间
//         {
//             newnode->next=curr;
//             pre->next=newnode;
//         }    
//     }
   
       
// }
// Node* Multiply(Node* p1, Node* p2) //乘法：两层循环，生成每对项的乘积并插入到结果中（插入即合并）
// {
//     Node* result = nullptr;   // 乘积结果表，初始为空
//     // 遍历 p1 的每一项
//     for (Node* a = p1; a != nullptr; a = a->next)
//     {
//         // 对 p1 的当前项，遍历 p2 的每一项
//         for (Node* b = p2; b != nullptr; b = b->next)
//         {
//             long long coef = a->p * b->p;    // 系数相乘
//             long long exp  = a->e + b->e;    // 指数相加
//             insertTerm(result, coef, exp);   // 插入（或合并）到结果链表
//         }
//     }
//     return result; // 返回乘积链表头
// }
void Print(Node* head) //打印多项式
{
    if(head==nullptr)
        return;
    bool first=true;
    Node* temp=head;
    while(temp!=nullptr)
    {
        if(temp->p!=0) //系数为0的项跳过
        {
            if(first==false) //不是第一项前面需要空格
                cout<<" ";
            cout<<temp->p<<" "<<temp->e;
            first=false;
        }
        temp=temp->next;
    } 
    cout<<endl;  
}
Node* Multiply(Node* p1, Node* p2) {
    if (p1 == nullptr || p2 == nullptr) return nullptr; // 有一个为空

    map<long long, long long> acc;
    //为避免出现TLE，创建map字典（键值对），底层是红黑树，维护键（key）有序，而且可以用 key 来快速找到对应的值。
    //此处：key = 指数exp  value = 系数coef
    //这样，所有的“同类项”都会自动合并在同一个 key 下面。并且遍历 map 的时候，指数是自动从小到大排好序的。
    for (Node* a = p1; a != nullptr; a = a->next)    // 双循环：把乘积累加到 acc
    {
        for (Node* b = p2; b != nullptr; b = b->next)
        {
            acc[a->e + b->e] += a->p * b->p;
        }
    }
    // 从 map 转成链表
    Node* head = nullptr;
    Node* tail = nullptr;
    for (map<long long, long long>::iterator it = acc.begin(); it != acc.end(); ++it)
    {
        // it->first  表示 key（指数）
        // it->second 表示 value（系数）
        Node* node = createNode(it->second, it->first);  // 创建新节点
        if (head == nullptr)
        {
            // 如果链表还是空的，新节点作为第一个元素
            head = tail = node;
        }
        else
        {
            // 否则接到尾巴后面，并更新尾指针
            tail->next = node;
            tail = node;
        }
    }
    return head;
}
Node* Read(int count) //读取多项式（用来处理输入）
{
    Node* head=nullptr; //表头
    Node* tail=nullptr; //表尾
    for(int i=0;i<count;i++)
    {
        long long coef,exp;
        cin>>coef>>exp;
        Node* node= createNode(coef,exp);
        if(head==nullptr) //处理空链表
        {
            head=node; //让头指针和尾指针都指向第一个结点
            tail=node;
        }
        else
        {
            tail->next=node; //插到链表末尾
            tail=node; //更新表尾
        }
    }
    return head;
}
//删除结点释放内存
void Free(Node* head) {
    while (head != nullptr) {
        Node* nxt = head->next; // 保存下一个结点地址
        delete head;            // 释放当前结点
        head = nxt;             // 指针后移，继续处理
    }
}
int main()
{
    int m,n,operation;
    cin>>m;
    Node* p1=Read(m);
    cin>>n;
    Node* p2=Read(n);
    cin>>operation;
    if(operation==0||operation==2) //执行加法操作
    {
        Node *p_add=Add(p1,p2);
        Print(p_add);
        Free(p_add);
    }
    if(operation==1||operation==2) //执行乘法操作
    {
        Node* p_mul=Multiply(p1,p2);
        Print(p_mul);
        Free(p_mul);
    }
    Free(p1);
    Free(p2);
    return 0;
}

