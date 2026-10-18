#include<iostream>
using namespace std;
using namespace std;
#define STACK_INIT_SIZE 100 // 栈初始分配空间大小
#define STACKINCREMENT 10  // 栈满时增加的存储空间
struct Stack
{
    int *base; //栈尾指针
    int *top;  //栈顶指针
    int stacksize;  //当前已分配的存储空间，单位是sizeof(元素)
};
/**
 * @brief 初始化顺序栈S
 * @param S 待初始化的栈引用
 * @return int 1表示成功，exit(1)表示失败
 */
int InitStack(Stack &S)  //栈初始化
{
    S.base=(int*)malloc(STACK_INIT_SIZE*sizeof(int));
    if(S.base==NULL) exit(1);
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return 1;
}

/**
 * @brief 插入元素e为新的栈顶元素
 * @param S 栈引用
 * @param e 待插入的数字
 * @return int 1表示成功
 */
int Push(Stack &S,int e) //插入元素e为新的栈顶元素
{
    if((S.top-S.base)>=S.stacksize) //栈已满
    {
        S.base=(int*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(int));
        if(S.base==NULL) exit(1);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top=e;
    S.top++;
    return 1;
}
/**
 * @brief 取栈顶元素
 * @param S 栈结构体
 * @param e 用于接收栈顶元素的引用
 * @return int 1表示成功，0表示栈为空或不存在
 */
int GetTop(Stack S,int &e) //取栈顶元素
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
 * @brief 删除栈顶元素并返回其值
 * @param S 栈引用
 * @param e 用于接收被删除的栈顶元素
 * @return int 1表示成功，0表示栈为空或不存在
 */
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
/**
 * @brief 判断栈是否为空
 * @param S 栈常量引用
 * @return bool true如果栈为空，false否则
 */
bool StackEmpty(const Stack &S) //判断栈是否为空
{
    return S.base==S.top;
}
void Pair(const string&s,int &max_len,int &pos)
{
    if(s.empty())
    {
        max_len=0;
        return;
    }
    Stack S;
    InitStack(S);
    Push(S,-1); //将栈底的元素作为当前合法子串的起点前一个位置，初始化时将基准索引-1压入栈中
    int top_val;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='(') Push(S,i);
        else{
            Pop(S,top_val);
            if(StackEmpty(S)) //若为空，说明当前的‘)’没有匹配的‘(’，是违法的
            {
                Push(S,i); //将当前的索引i作为新的基准点压入栈中，相当于重置的合法子串的计算起点
            }
            else{
                GetTop(S,top_val);
                int curr_len=i-top_val;
                if(curr_len>max_len)
                {
                    max_len=curr_len;
                    pos=top_val+1;
                }
            }
        }
    }
}
int main()
{
    string s;
    cin>>s;
    int i=0;
    int max_len=0;
    int pos=0;
    Pair(s,max_len,pos);
    cout<<max_len<<" "<<pos<<endl;
    return 0;
}