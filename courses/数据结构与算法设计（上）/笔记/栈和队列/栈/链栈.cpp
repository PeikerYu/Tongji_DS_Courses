//注意！这个代码是基于不带头结点的单链表的！
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#include<iostream>
#include<cstdlib> // 使用 malloc 和 free
using namespace std;

struct SNode
{
    int data;
    SNode*next;
};

struct LinkStack
{
    SNode *top;  // 栈顶指针 (指向链表的第一个有效结点)
    int count;   // 栈中元素的数量（用于 StackLength）
};

// 链栈基本操作函数

// 栈初始化：将栈顶指针置空
int InitStack(LinkStack &S) 
{
    S.top = NULL; // 初始时栈顶为空，表示栈为空
    S.count = 0;
    return 1;
}

// 判断栈是否为空
int StackEmpty(LinkStack S)
{
    return (S.top == NULL);
}

// 取栈顶元素
int GetTop(LinkStack S, int &e) 
{
    if (StackEmpty(S))
    {
        cout << "栈为空！" << endl;
        return 0;
    }
    
    e = S.top->data; // 栈顶就是第一个结点的数据
    return 1;
}

// 插入元素 e 为新的栈顶元素 (入栈操作)
int Push(LinkStack &S, int num) 
{
    // 1. 创建新结点并分配内存
    // 在 C++ 中，最好使用 new，但为了贴合您的 C/malloc 风格，我们继续使用 malloc
    SNode *p = (SNode*)malloc(sizeof(SNode));
    if (p == NULL) 
    {
        cout << "内存分配失败！" << endl;
        return 0; // 内存不足
    }
    
    // 2. 填充数据
    p->data = num;
    
    // 3. 将新结点 p 插入到当前栈顶的前面（头插法）
    p->next = S.top; // 新结点的 next 指向原来的栈顶
    S.top = p;       // 栈顶指针更新为新结点 p
    
    S.count++;
    return 1;
}

// 删除栈顶元素并返回其值 (出栈操作)
int Pop(LinkStack &S, int &e) 
{
    if (StackEmpty(S))
    {
        cout << "栈为空！" << endl;
        return 0;
    }
    
    // 1. 暂存将要被删除的结点
    SNode *p = S.top;
    
    // 2. 取出数据
    e = p->data;
    
    // 3. 栈顶指针下移到下一个结点
    S.top = p->next;
    
    // 4. 释放被删除结点的内存
    free(p);
    
    S.count--;
    return 1;
}

// 求长度
int StackLength(LinkStack S) 
{
    return S.count;
}

// 销毁栈 (释放所有结点内存)
int StackDestroy(LinkStack &S) 
{
    SNode *p = S.top;
    SNode *q;

    while (p != NULL) {
        q = p->next; // 暂存下一个结点
        free(p);     // 释放当前结点
        p = q;       // 移动到下一个结点
    }
    S.top = NULL;
    S.count = 0;
    return 1;
}

// 清空栈 (与销毁栈功能相似，释放所有元素结点，仅保留一个空栈)
int StackClear(LinkStack &S) 
{
    return StackDestroy(S); // 链栈中清空和销毁是相同的操作
}

// 遍历时调用的访问函数
int PrintElem(int e) {
    cout << e << " ";
    return 1;
}

// 遍历栈中每个元素并调用函数 visit() (从顶到底遍历)
int StackTraverse(LinkStack S, int(*visit)(int)) 
{
    if (StackEmpty(S)) {
        cout << "栈不存在或为空！" << endl;
        return 0;
    }
    
    SNode *p = S.top; // 从栈顶开始
    while (p != NULL) {
        visit(p->data);
        p = p->next;
    }
    return 1;
}

int main()
{
    LinkStack S;
    
    InitStack(S);
    cout << "初始化完成，当前栈长: " << StackLength(S) << endl;

    // 入栈
    Push(S, 10);
    Push(S, 20);
    Push(S, 30); // 栈顶是 30
    cout << "入栈 10, 20, 30 后栈长: " << StackLength(S) << endl;

    // 遍历 (从顶到底: 30, 20, 10)
    cout << "当前栈内容（从顶到尾）: ";
    StackTraverse(S, PrintElem);
    cout << endl;

    // 查看栈顶
    int e;
    if (GetTop(S, e))
        cout << "当前栈顶元素: " << e << endl;

    // 出栈
    Pop(S, e);
    cout << "弹出元素: " << e << "，当前栈长: " << StackLength(S) << endl; // 弹出 30

    // 清空栈
    StackClear(S);
    cout << "清空后栈长: " << StackLength(S) << endl;

    // 再次入栈验证是否可复用
    Push(S, 99);
    Push(S, 100);
    cout << "再次入栈后内容: ";
    StackTraverse(S, PrintElem);
    cout << endl; // 100, 99

    // 销毁栈
    StackDestroy(S);
    cout << "栈已销毁。" << endl;

    return 0;
}