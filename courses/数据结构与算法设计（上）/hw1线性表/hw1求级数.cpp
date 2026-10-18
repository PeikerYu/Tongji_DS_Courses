// #include<iostream>
// #include<vector>
// #include<algorithm>
// using namespace std;
// vector<int>intToVector(int n) //将int转化为vector，低位在前
// {
//     if(n==0)
//         return {0};
//     vector<int>v;
//     while(n>0)
//     {
//         v.push_back(n%10);
//         n/=10;
//     }
//     return v;
// }
// vector<int>Add(const vector<int>&a,const vector<int>&b)  //大数+大数
// { 
//     vector<int>res;
//     int carry=0; //引入进位变量
//     int i=0,j=0;
//     while(i<a.size()||j<b.size()||carry!=0) //当 a 或 b 仍有位，或仍有进位时，继续计算
//     {
//         int x=(i<a.size()?a[i]:0); // 取当前位数字，若超出 vector 长度则取 0
//         int y=(j<b.size()?b[j]:0);
//         int curr=x+y+carry;
//         carry=curr/10;  //更新进位数
//         res.push_back(curr%10); //当前位是余数
//         i++;j++;
//     }
//     return res;
// }
// vector<int>Multiply(const vector<int>&a,int b) //大数×小数
// {
//     vector<int>res;
//     int curr;
//     int carry=0;
//     int i=0;
//     while(i<a.size()||carry!=0) //当 a 仍有位，或仍有进位时，继续计算
//     {
//         int x=(i<a.size()?a[i]:0);
//         curr=b*x+carry;
//         carry=curr/10; // 更新进位数
//         curr%=10; //当前位是余数
//         res.push_back(curr);
//         i++;
//     }
//     return res;
// }

// void Print(const vector<int>&a) //打印输出函数
// {
//     for(int i=a.size()-1;i>=0;i--)
//         cout<<a[i];
//     cout<<endl;
// }
// int main()
// {
//     int n,a;
//     while(cin>>n>>a)
//     {
//         vector<int>sum={0};
//         vector<int>power={1};
//         for(int i=1;i<=n;i++)
//         {
//             power=Multiply(power,a); // 计算 A^i
//             vector<int>curr_term=Multiply(power,i); // 计算 i * A^i
//             sum=Add(sum,curr_term);  // 累加到结果
//         }
//         Print(sum);
//     }
//     return 0;
// }

#include<iostream>
using namespace std;
struct BigData //从低位到高位存储
{
    int *data; //动态内存地址
    int size;  //当前整数最大位数
    int capacity;  //当前可用的最大容量（自动扩容）
};
void initBigData(BigData* v) //初始化动态数组
{
    v->size=0;
    v->capacity=100; //将初始容量设为100
    v->data=(int*)malloc(sizeof(int)*v->capacity);
}
void ensureCapacity(BigData* v,int newSize) 
//确保位数容量足够，若不够则扩容为原来两倍
{
    if(newSize<=v->capacity) return;
    while(v->capacity<newSize) v->capacity*=2;
    v->data=(int*)realloc(v->data,sizeof(int)*v->capacity);
}
void pushBack(BigData* v,int val) //在尾部追加一位数字
{
    ensureCapacity(v,v->size+1); //先确保容量足够
    v->data[v->size++]=val; //添加新元素并将size++
}
void freeBigData(BigData* v)
{
    free(v->data);  //释放堆内存
    v->data=NULL;
    v->size=0;
    v->capacity=0;
}
void initBigInt(BigData* v,int x) //将一个大整数转为BigData存放
{
    initBigData(v);
    if(x==0)
    {
        pushBack(v,0);
        return;
    }
    while(x>0) //依次取出x的每一位，低位在前
    {
        pushBack(v,x%10);
        x/=10;
    }
}
void multiplyInt(BigData* a,int x) //BigData*int
{
    int carry=0; //carry表示进位的值
    for(int i=0;i<a->size;i++)
    {
        long long temp=1LL*a->data[i]*x+carry; //当前位*x+上一位进位
        a->data[i]=temp%10; //当前位的值
        carry=temp/10; //更新进位值
    }
    while(carry>0) //处理剩余的进位
    {
        pushBack(a,carry%10);
        carry/=10;
    }
}
void addBigInt(BigData* c,BigData* a,BigData* b) //BigData的运算：a=b+c
{
    int n=(a->size>b->size?a->size:b->size);
    ensureCapacity(c,n+5); //加入5余量防止进位溢出
    int carry=0;
    for(int i=0;i<n;i++)
    {
        int x = (i < a->size ? a->data[i] : 0);  // 如果 a 不够长，补 0
        int y = (i < b->size ? b->data[i] : 0);  // 如果 b 不够长，补 0
        int sum = x + y + carry;  // 当前位相加 + 进位
        c->data[i] = sum % 10;    // 存入当前位结果
        carry = sum / 10;         // 更新进位
    }
    c->size = n;                 // 设置当前结果长度
    if (carry)                   // 若最后仍有进位
    {
        c->data[c->size++] = carry;
    } 
}
void printBigInt(struct BigData* v)
{
    for (int i = v->size - 1; i >= 0; i--)
    {  // 从最高位到最低位打印
        cout<<v->data[i];
    }
}                     
int main()
{
    int N,A;
    while(cin>>N>>A)
    {
        BigData ans,term,tmp;  //定义大整数：结果 ans，当前项 term，临时变量 tmp
        initBigInt(&ans,0);
        initBigInt(&term,A);  //初始化 ans = 0, term = A
        for(int k=1;k<=N;k++)
        {
            initBigInt(&tmp,0); //将term保存到tmp，因为×k不想破坏原term
            tmp.size=term.size;
            ensureCapacity(&tmp,term.size+10);
            for(int i=0;i<term.size;i++)
            {
                tmp.data[i]=term.data[i];
            }
            multiplyInt(&tmp,k); //tmp*=k
            addBigInt(&ans,&ans,&tmp); // ans+=tmp
            multiplyInt(&term,A); //term*=A
            freeBigData(&tmp);
        }
        printBigInt(&ans);
        cout<<endl;
        freeBigData(&ans);
        freeBigData(&term);
    }
    return 0;
}
