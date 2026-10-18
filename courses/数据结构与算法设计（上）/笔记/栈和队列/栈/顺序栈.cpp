#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#include<iostream>
#include<stdlib.h>
using namespace std;

struct Stack
{
    int *base;
    int *top;
    int stacksize;  //当前已分配的存储空间，单位是sizeof(元素)
};

int InitStack(Stack &S)  //栈初始化
{
    S.base=(int*)malloc(STACK_INIT_SIZE*sizeof(int));
    if(S.base==NULL) exit(1);
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return 1;
}

int GetTop(Stack S,int &e) //取栈顶元素
{
    if(S.base==NULL)
    {
        cout<<"栈不存在！"<<endl;
        return 0;
    }
    else if(S.base==S.top)
    {
        cout<<"栈为空！"<<endl;
        return 0;
    }
    else
    {
        e=*(S.top-1); 
        return 1;
    }
}

int Push(Stack &S,int num) //插入元素e为新的栈顶元素
{
    if((S.top-S.base)>=S.stacksize) //栈已满
    {
        S.base=(int*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(int));
        if(S.base==NULL) exit(1);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top=num;
    S.top++;
    return 1;
}

int Pop(Stack &S,int &e) //删除栈顶元素并返回其值
{
    if(S.base==NULL)
    {
        cout<<"栈不存在！"<<endl;
        return 0;
    }
    else if(S.base==S.top)
    {
        cout<<"栈为空！"<<endl;
        return 0;
    }
    else{
        e=*(S.top-1);
        S.top--;
        return 1;
    }
}

int StackLength(Stack S) //求长度
{
    return (S.top-S.base);
}

int StackDestroy(Stack &S) //销毁栈
{
    if (S.base != NULL) {
        free(S.base);
        S.base = NULL;
        S.top = NULL;
        S.stacksize = 0;
        }
    return 1;
}

int StackClear(Stack &S) //清空栈
{
    if (S.base == NULL) return 0;
    S.top = S.base;
    return 1;
}

// 遍历时调用的访问函数
int PrintElem(int e) {
    cout << e << " ";
    return 1;
}

int StackTraverse(Stack S,int(*visit)(int)) //遍历栈中每个元素并调用函数visit()
{
    if (S.base == NULL) {
        cout << "栈不存在！" << endl;
        return 0;
    }
    int *p = S.base;
    while (p < S.top) {
        visit(*p);
        p++;
    }
    return 1;
}

int main()
{
    Stack S;
    InitStack(S);
    cout << "初始化完成，当前栈长: " << StackLength(S) << endl;

    // 入栈
    Push(S, 10);
    Push(S, 20);
    Push(S, 30);
    cout << "入栈 10, 20, 30 后栈长: " << StackLength(S) << endl;

    // 遍历
    cout << "当前栈内容（从底到顶）: ";
    StackTraverse(S, PrintElem);
    cout << endl;

    // 查看栈顶
    int e;
    if (GetTop(S, e))
        cout << "当前栈顶元素: " << e << endl;

    // 出栈
    Pop(S, e);
    cout << "弹出元素: " << e << "，当前栈长: " << StackLength(S) << endl;

    // 清空栈
    StackClear(S);
    cout << "清空后栈长: " << StackLength(S) << endl;

    // 再次入栈验证是否可复用
    Push(S, 99);
    Push(S, 100);
    cout << "再次入栈后内容: ";
    StackTraverse(S, PrintElem);
    cout << endl;

    // 销毁栈
    StackDestroy(S);
    cout << "栈已销毁。" << endl;

    return 0;
}
