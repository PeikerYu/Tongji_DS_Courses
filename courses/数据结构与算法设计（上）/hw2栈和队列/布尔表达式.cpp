// #define STACK_INIT_SIZE 100
// #define STACKINCREMENT 10
// #include<iostream>
// #include<stdlib.h>
// using namespace std;
// using namespace std;
// const char oper[5]={'|','&','!','(',')'};
// struct Stack
// {
//     char *base;  //栈底
//     char *top;  //栈顶
//     int stacksize;  //当前已分配的存储空间，单位是sizeof(元素)
// };
// int InitStack(Stack &S)  //栈初始化
// {
//     S.base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
//     if(S.base==NULL) exit(1);
//     S.top=S.base;
//     S.stacksize=STACK_INIT_SIZE;
//     return 1;
// }
// int GetTop(Stack S,char &e) //取栈顶元素
// {
//     if(S.base==NULL)
//         return 0;
//     else if(S.base==S.top)
//         return 0;
//     else
//     {
//         e=*(S.top-1);
//         return 1;
//     }
// }
// int Push(Stack &S,char ch) //插入元素ch为新的栈顶元素
// {
//     if((S.top-S.base)>=S.stacksize) //栈已满
//     {
//         S.base=(char*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(char));
//         if(S.base==NULL) exit(1);
//         S.top=S.base+S.stacksize;
//         S.stacksize+=STACKINCREMENT;
//     }
//     *S.top=ch;
//     S.top++;
//     return 1;
// }
// int Pop(Stack &S,char &e) //删除栈顶元素并返回其值
// {
//     if(S.base==NULL)
//         return 0;
//     else if(S.base==S.top)
//         return 0;
//     else{
//         e=*(S.top-1);
//         S.top--;
//         return 1;
//     }
// }
// bool In(char ch) //判断字符是否应该进入运算符栈
// {
//     for(int i=0;i<5;i++)
//     {
//         if(ch==oper[i]) return true;
//     }
//     return false;
// }
// char Precede(char theta1,char theta2) //判断运算符优先级
// {
//     if((theta1=='('&&theta2==')')||(theta1=='#'&&theta2=='#')) 
//         return '=';
//     else if(theta1=='#'||theta1=='('||theta2=='(')
//         return '<';
//     else if(theta2==')')
//         return '>';
//     else if(theta1=='!'&&theta2=='!')
//         return '<';
//     else{
//         int p1,p2;
//         if(theta1=='!') p1=3;
//         else if(theta1=='&') p1=2;
//         else if(theta1=='|') p1=1;
//         else p1=0;

//         if (theta2 == '!') p2 = 3;
//         else if (theta2 == '&') p2 = 2;
//         else if (theta2 == '|') p2 = 1;
//         else p2 = 0;

//         if (p1 < p2) return '<';
//         else return '>';
//     }
// }
// char Operate(char first,char theta,char second) //计算运算结果
// {
//     switch(theta)
//     {
//         case '|':
//         {
//             if(first=='F'&&second=='F') return 'F';
//             else return 'V';
//         }
//         case '&':
//         {
//             if(first=='V'&&second=='V') return 'V';
//             else return 'F';
//         }
//         case '!':
//             return (second=='V')?'F':'V'; //注意是作用在第二个操作数上的
//         default:
//             return 'F';
//     }
// }
// char EvaluateExpression(const string& expression) //表达式求值函数
// {
//     Stack S1,S2;  //S1为运算符栈，S2为运算数栈
//     char ch,e,num1,num2;
//     InitStack(S1);
//     InitStack(S2);
//     Push(S1,'#');  //将表达式起始符‘#’压入运算符栈
//     string filtered_expression;
//     for(char c:expression)
//     {
//         if(c!=' ')
//             filtered_expression+=c;
//     }
//     filtered_expression+='#';
//     int i=0;
//     ch=filtered_expression[i++];
//     while(!(ch == '#' && *(S1.top - 1) == '#'))
//     {
//         if(ch=='V'||ch=='F')
//         {
//             Push(S2,ch);
//             ch=filtered_expression[i++]; 
//         }
//         else if(In(ch))
//         {
//             GetTop(S1,e);
//             switch(Precede(e,ch))
//             {
//                 case '=':
//                 {
//                     Pop(S1,e);
//                     ch=filtered_expression[i++]; 
//                     break;
//                 }
//                 case '<':
//                 {
//                     Push(S1,ch);
//                     ch=filtered_expression[i++]; 
//                     break;
//                 }
//                 case '>':
//                 {
//                     Pop(S1,e);
//                     if(!Pop(S2,num2)) num2='F';
//                     char num3;
//                     if(e=='!') //处理单目运算符！情况
//                     {
//                         num1=' ';
//                         num3=Operate(num1,e,num2);
//                     }
//                     else{
//                         if(!Pop(S2,num1)) num1='F'; //弹出左操作数
//                         num3=Operate(num1,e,num2);
//                     }
//                     Push(S2,num3);
//                     break;
//                 }
//             }
//         }
//     }
//     char res;
//     if(GetTop(S2,res))
//         return res;
//     return 'F';
// }
// int main()
// {
//     Stack S1,S2;
//     string line;
//     int count=1;
//     while(getline(cin,line))
//     {
//         char result=EvaluateExpression(line);
//         cout<<"Expression "<<(count++)<<": "<<result<<endl;
//     }
//     return 0;
// }


#include <iostream>
#include <string>
using namespace std;
#define MAXSIZE 200 // 根据题意，支持 100 长度表达式足够
struct Stack //静态栈
{
    char data[MAXSIZE];
    int top; // 指向当前栈顶的下一个位置
};
/**
 * @brief 初始化栈
 * @param S  栈引用
 */
void InitStack(Stack &S) {
    S.top = 0;
}
bool Push(Stack &S, char ch) {
    if (S.top >= MAXSIZE) return false; // 防溢出
    S.data[S.top++] = ch;
    return true;
}
bool Pop(Stack &S, char &e) {
    if (S.top == 0) return false; // 空栈
    e = S.data[--S.top];
    return true;
}
bool GetTop(Stack &S, char &e) {
    if (S.top == 0) return false;
    e = S.data[S.top - 1];
    return true;
}

bool In(char ch) {
    // 判断是否为运算符
    return (ch == '!' || ch == '&' || ch == '|' || ch == '(' || ch == ')' || ch == '#');
}

// 判断运算符优先级关系
// 返回：'<' 让进栈，'>' 弹出计算，'=' 匹配（括号或结束符）
char Precede(char theta1, char theta2) {
    // 括号与 # 特殊规则
    if ((theta1 == '(' && theta2 == ')') || (theta1 == '#' && theta2 == '#'))
        return '=';
    else if (theta1 == '(' || theta1 == '#' || theta2 == '(')
        return '<';
    else if (theta2 == ')')
        return '>';
    // 右结合的 !
    else if (theta1 == '!' && theta2 == '!')
        return '<';
    else {
        int p1, p2; // 优先级数值越大优先级越高
        if (theta1 == '!') p1 = 3;
        else if (theta1 == '&') p1 = 2;
        else if (theta1 == '|') p1 = 1;
        else p1 = 0;

        if (theta2 == '!') p2 = 3;
        else if (theta2 == '&') p2 = 2;
        else if (theta2 == '|') p2 = 1;
        else p2 = 0;

        if (p1 < p2) return '<';
        else return '>';
    }
}

// 执行布尔运算
char Operate(char first, char theta, char second) {
    switch (theta) {
        case '|':
            return (first == 'F' && second == 'F') ? 'F' : 'V';
        case '&':
            return (first == 'V' && second == 'V') ? 'V' : 'F';
        case '!':
            return (second == 'V') ? 'F' : 'V'; // 单目运算符，对右操作数取反
        default:
            return 'F';
    }
}

char EvaluateExpression(const string &expr) {
    Stack S1, S2; // S1: 运算符栈, S2: 操作数栈
    InitStack(S1);
    InitStack(S2);
    Push(S1, '#'); // 起始标志

    // 去除空格并添加结束符
    string s;
    for (char c : expr) if (c != ' ') s += c;
    s += '#';

    int i = 0;
    char ch = s[i++], e, num1, num2;

    // 算符优先主循环
    while (!(ch == '#' && S1.data[S1.top - 1] == '#')) {
        if (ch == 'V' || ch == 'F') {
            // 是操作数，直接入操作数栈
            Push(S2, ch);
            ch = s[i++];
        } else if (In(ch)) {
            GetTop(S1, e);
            switch (Precede(e, ch)) {
                case '<': // 新符号优先级高，入栈
                    Push(S1, ch);
                    ch = s[i++];
                    break;

                case '=': // 匹配括号或结束符，出栈丢弃
                    Pop(S1, e);
                    ch = s[i++];
                    break;

                case '>': { // 栈顶运算符优先级高，弹出计算
                    Pop(S1, e);
                    if (!Pop(S2, num2)) num2 = 'F'; // 防止空栈
                    char num3;
                    if (e == '!') {
                        num3 = Operate(' ', e, num2);
                    } else {
                        if (!Pop(S2, num1)) num1 = 'F';
                        num3 = Operate(num1, e, num2);
                    }
                    Push(S2, num3);
                    break;
                }
            }
        } else {
            // 非法字符（保险防护，不中断）
            ch = s[i++];
        }
    }

    char res;
    if (GetTop(S2, res)) return res;
    return 'F';
}

int main() {
    ios::sync_with_stdio(false); // 加速输入输出
    cin.tie(nullptr);

    string line;
    int count = 1;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        char result = EvaluateExpression(line);
        cout << "Expression " << count++ << ": " << result << "\n";
    }
    return 0;
}
