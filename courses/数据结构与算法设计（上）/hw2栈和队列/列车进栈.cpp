#define STACK_INIT_SIZE 100 // 栈初始分配空间大小
#define STACKINCREMENT 10  // 栈满时增加的存储空间
#include<iostream>
using namespace std;
using namespace std;
struct Stack
{
    char *base; //栈尾指针
    char *top;  //栈顶指针
    int stacksize;  //当前已分配的存储空间，单位是sizeof(元素)
};
/**
 * @brief 初始化顺序栈S
 * @param S 待初始化的栈引用
 * @return int 1表示成功，exit(1)表示失败
 */
int InitStack(Stack &S)  //栈初始化
{
    S.base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
    if(S.base==NULL) exit(1);
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return 1;
}
/**
 * @brief 取栈顶元素
 * @param S 栈结构体
 * @param e 用于接收栈顶元素的引用
 * @return int 1表示成功，0表示栈为空或不存在
 */
int GetTop(Stack S,char &e) //取栈顶元素
{
    if(S.base==NULL)
        return 0;
    else if(S.base==S.top)
        return 0;
    else
    {
        e=*(S.top-1);
        return 1;
    }
}
/**
 * @brief 插入元素e为新的栈顶元素（模拟列车进车站）
 * @param S 栈引用
 * @param e 待插入的字符（列车编号）
 * @return int 1表示成功
 */
int Push(Stack &S,char e) //插入元素e为新的栈顶元素
{
    if((S.top-S.base)>=S.stacksize) //栈已满
    {
        S.base=(char*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(char));
        if(S.base==NULL) exit(1);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top=e;
    S.top++;
    return 1;
}
/**
 * @brief 删除栈顶元素并返回其值（模拟列车从车站出站）
 * @param S 栈引用
 * @param e 用于接收被删除的栈顶元素
 * @return int 1表示成功，0表示栈为空或不存在
 */
int Pop(Stack &S,char &e) //删除栈顶元素并返回其值
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
/**
 * @brief 判断某字符是否在栈里
 * @param S 栈结构体
 * @param e 待查找的字符
 * @return int 1表示在栈里，0表示不在
 */
int In(Stack S,char e) //判断某字符是否在栈里
{
    char *p=S.base;
    while(*p!=e&&p<S.top)
    {
        p++;
    }
    if(p!=S.top)
        return 1;
    else
        return 0;
}
/**
 * @brief 清空栈并释放内存
 * @param S 栈引用
 */
void ClearStack(Stack &S) //清空栈
{
    if (S.base) {
        free(S.base); // 使用 free 释放 malloc/realloc 的内存
    }
    // 重新初始化所有成员
    S.base = nullptr; 
    S.top = nullptr;
    S.stacksize = 0;
}

/**
 * @brief 判断栈是否为空
 * @param S 栈常量引用
 * @return bool true如果栈为空，false否则
 */
bool StackEmpty(const Stack &S) //判断栈是否为空
{
    return S.base==S.top;
}

bool check_sequence(const string& str_in, const string& str_out, Stack &S)
{
    // ... 清空栈和初始化代码保持不变 ...
    ClearStack(S); 
    if(InitStack(S) != 1) exit(1);
    
    int i = 0; // 入口序列指针
    int j = 0; // 期望出站序列指针
    char e;    // 栈顶元素

    if (str_in.length() != str_out.length()) {
        return false;
    }

    // 外层循环：驱动整个过程，直到所有期望出站车 (str_out[j]) 都被满足
    while (j < str_out.length()) { 
        
        // --- 阶段 1: 尝试从入口引入新车 (操作 A 或 B) ---
        
        // 只有当栈顶无法满足期望时，我们才需要从入口引入新车。
        // 如果栈为空 或者 栈顶不等于 str_out[j]，就进入这个循环。
        while (i < str_in.length() && 
               (StackEmpty(S) || (GetTop(S, e) && e != str_out[j]))) 
        {
            // 决策：是直接出 (A) 还是进栈 (B)?
            if (str_in[i] == str_out[j]) {
                // *** 操作 A: 入口 -> 出口 (直接出站) ***
                i++; // 入口车被消耗
                j++; // 期望车被满足
                goto next_out_char; // 成功匹配，直接跳到下一轮外层循环
            }
            else {
                // *** 操作 B: 入口 -> 车站 (进栈等待) ***
                Push(S, str_in[i]);
                i++; // 入口车被消耗
            }
        }
        
        // --- 阶段 2: 检查车站 (栈) 是否满足期望 (操作 C) ---
        
        // 此时，内层 while 循环已经结束。结束的原因只有两个：
        // 1. 栈顶现在匹配了期望 str_out[j]。
        // 2. 入口所有车都用完了 (i == str_in.length())。
        
        if (!StackEmpty(S) && GetTop(S, e) && e == str_out[j]) {
            // *** 操作 C: 车站 -> 出口 (出栈) ***
            Pop(S, e); 
            j++;       // 期望车被满足
            continue;  // 成功出栈，进入下一轮外层循环
        }

        // --- 阶段 3: 失败判定 ---
        
        // 如果执行到这里，说明：
        // 1. 栈顶不匹配 (阶段 2 失败) AND
        // 2. 内层循环已经结束 (i == str_in.length() 是唯一可能的原因)。
        // 结论：期望的车永远被挡在栈内，无法出栈。
        return false;
        
    next_out_char:; // 用于操作 A 成功时，跳过阶段 2 和 3，直接检查下一个 j
    }
    
    // 如果 while 循环正常结束，说明 j 走完了 str_out
    return true;
}
int main()
{
    Stack S;
    if(InitStack(S)!=1) exit(1);
    string str_in;
    cin>>str_in;
    int i=0;int j=0;
    string str_out;
    while(cin>>str_out)
    {   
        if(check_sequence(str_in,str_out,S))
        {
            cout<<"yes"<<endl;
        }
        else
        {
            cout<<"no"<<endl;
        } 
    }
    ClearStack(S);
    return 0;
}