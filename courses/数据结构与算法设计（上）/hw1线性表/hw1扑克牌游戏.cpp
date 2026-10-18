#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
struct CardNode
{  
    string name; //花色
    string id;  //编号
    CardNode *next; //指针域
};
CardNode* Create(string name,string id)
{
    CardNode* p=new CardNode;
    p->id=id;
    p->name=name;
    p->next=nullptr;
    return p;
}

CardNode* Append(string name,string id,CardNode *head) //添加一张牌到底部
{
    CardNode* p=Create(name,id);
    if(head==nullptr)
    {
        head=p;
        return head;
    }
    else
    {
        CardNode* q=head;
        while(q->next!=nullptr)
        {
            q=q->next;
        }
        q->next=p;
    }
    return head;
}
int rankID(string id) {
    string order[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};  // 用T代表10
    for (int i = 0; i < 13; i++) {
        if (order[i] == id) return i; // 返回这个字符在顺序表中的位置
    }
    return -1; // 找不到（理论不会发生）
}

// CardNode* Extract(string name, CardNode* head)
// {
//     if (head == nullptr) return nullptr;

//     // 建立一个虚拟头，方便删除节点时不特殊处理头节点
//     CardNode* dummy = new CardNode();
//     dummy->next = head;

//     CardNode* prev = dummy;
//     CardNode* curr = head;

//     // 遍历整个链表
//     while (curr != nullptr)
//     {
//         if (curr->name == name) // 找到要抽取的花色
//         {
//             CardNode* toMove = curr;  // 当前要移动的节点
//             prev->next = curr->next;  // 从原链表中断开
//             curr = curr->next;        // 移动 curr 到下一个节点
//             toMove->next = nullptr;   // 断开 next 指针，避免混乱

//             // 如果头部还没出现目标花色 或者第一个目标花色id比它大
//             if (head->name != name || rankID(head->id) > rankID(toMove->id))
//             {
//                 toMove->next = head;
//                 head = toMove;
//             }
//             else
//             {
//                 CardNode* t = head;
//                 // 找到目标花色段中插入位置（保持id从小到大）
//                 while (t->next != nullptr &&
//                        t->next->name == name &&
//                        rankID(t->next->id) < rankID(toMove->id))
//                 {
//                     t = t->next;
//                 }
//                 toMove->next = t->next;
//                 t->next = toMove;
//             }
//         }
//         else
//         {
//             // 非目标花色节点，正常前进
//             prev = curr;
//             curr = curr->next;
//         }
//     }

//     delete dummy;
//     return head;
// }
// 抽取指定花色的牌，并按id升序放到牌堆顶部
CardNode* Extract(string name, CardNode* head)
{
    if (head == nullptr) return nullptr;
    // 建立虚拟头，方便删除节点时不特殊处理头节点
    CardNode* dummy = new CardNode();
    dummy->next = head;
    CardNode* prev = dummy;
    CardNode* curr = head;
    // 遍历并摘除目标花色节点
    vector<CardNode*> extracted; // 保存目标花色节点
    while (curr != nullptr)
    {
        if (curr->name == name) // 找到要抽取的花色
        {
            CardNode* toMove = curr;
            prev->next = curr->next; // 从原链表中断开
            curr = curr->next;
            toMove->next = nullptr;  // 断开 next 指针
            extracted.push_back(toMove); // 保存到数组
        }
        else // 非目标节点，正常前移prev和curr
        {
            prev = curr;
            curr = curr->next;
        }
    }
    head = dummy->next;
    delete dummy;
    if (extracted.empty())
        return head; // 没有抽到任何牌
    // 排序
    sort(extracted.begin(), extracted.end(),
        [](CardNode* a, CardNode* b){
            return rankID(a->id) < rankID(b->id);
        });
    // 从大到小插入头部（保证A最小在上，K最大在下）
    for (int i = extracted.size() - 1; i >= 0; i--)
    {
        extracted[i]->next = head;
        head = extracted[i];
    }
    return head;
}
CardNode *Revert(CardNode* head) //反转链表
{
    CardNode* prev=nullptr; //存储前一个节点
    CardNode* curr=head; //存储当前节点
    while(curr!=nullptr)
    {
        CardNode* nextNode=curr->next; //存储下一个节点
        curr->next=prev; //将当前节点指针指向前一个节点
        prev=curr;
        curr=nextNode; //处理下一个节点
    }
    return prev; //此时curr为nullptr，prev指向原链表最后一个节点，即新链表头部
}
void Pop(CardNode *&head) //弹出栈顶第一张牌
{
    if(head==nullptr)
    {
        cout<<"NULL"<<endl;
        return;
    } 
    else
    {
        cout<<head->name<<" "<<head->id<<endl;
        CardNode* temp=head; //暂存要删除的节点
        head=head->next; //栈顶指针移动到下一张牌
        delete temp; //释放原栈顶节点的内存
        return;
    }
}
void Print(CardNode* head)
{
    if(head==nullptr)
    {
        cout<<"NULL"<<endl;
        return;
    }
    CardNode* p=head;
    while(p!=nullptr)
    {
        cout<<p->name<<" "<<p->id<<endl;
        p=p->next;
    }
}
int main()
{
    int n;
    cin>>n;
    CardNode* head=nullptr;
    for(int i=0;i<n;i++)
    {
        string op;
        cin>>op;
        if(op=="Append")
        {
            string name;string id;
            cin>>name>>id;
            head=Append(name,id,head);
        }
        else if(op=="Extract")
        {
            string name;
            cin>>name;
            head=Extract(name,head);
        }
        else if(op=="Revert")
        {
            head=Revert(head);
        }
        else if(op=="Pop")
        {
            Pop(head);
        }
    }
    Print(head);
    return 0;
}

