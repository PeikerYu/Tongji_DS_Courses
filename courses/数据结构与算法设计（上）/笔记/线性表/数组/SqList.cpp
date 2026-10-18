//这个文件用于存放所有函数的实现
#include"SqList.h" //包含头文件
#include<iostream>
#include<stdlib.h> //包含realloc exit
using namespace std;
int InitSqList(SqList &L) //构造一个空的线性表
{
    L.arr=(int*)malloc(LIST_INT_SIZE*sizeof(int));
    if(!L.arr) exit(1);  //存储分配失败
    L.length=0;  //初始长度设为0
    L.listsize=LIST_INT_SIZE;  //初始存储容量
    return 1;
}
int ListInsert(SqList &L,int num,int pos) //在L中第pos个位置之前插入新元素num
{
    // if(L.length==0) {L.arr[0]=num;return 1;}
    if(pos<1||pos>L.length+1) //排除不合法的位置
        return 0;
    if(L.length>=L.listsize) //当存储空间已满时，增添内存分配
    {
        int* new_arr;
        new_arr=(int*)realloc(L.arr,(L.listsize+LIST_INCREMENT)*sizeof(int));
        if(new_arr==NULL) exit(1); //内存分配失败退出
        L.listsize+=LIST_INCREMENT;
        L.arr=new_arr;
    }
    for(int i=L.length-1;i>=pos-1;i--)
    {
        L.arr[i+1]=L.arr[i];
    }
    L.arr[pos-1]=num;
    L.length++;
    return 1;
}
int ListDelete(SqList&L,int pos,int&e) //删除函数
{
    if(pos<1||pos>L.length) return 0;
    e=L.arr[pos-1];
    for(int i=pos;i<L.length;i++)
    {
        L.arr[i-1]=L.arr[i];
    }
    L.length--;
    return 1;
}
int ListLocate(SqList&L,int num) //查找
{
    for(int i=0;i<L.length;i++)
    {
        if(L.arr[i]==num)
            return i+1;
    }
    return 0;
}
void ListMerge(const SqList&L1,const SqList&L2,SqList &L3)  //将两个非递减顺序表按非递减方式排列
{
    InitSqList(L3);
    if(L3.listsize<L1.length+L2.length)
    {
        L3.arr=(int*)realloc(L3.arr,(L1.length+L2.length)*sizeof(int));
        L3.listsize=L1.length+L2.length;
    }
    int *p1=L1.arr;
    int *p2=L2.arr;
    int *p3=L3.arr;
    while(p1<L1.arr+L1.length&&p2<L2.arr+L2.length)
    {
        if(*p1<*p2)
        {
            *p3=*p1;
            p1++;p3++;
        }
        else if(*p1>*p2)
        {
            *p3=*p2;
            p2++;p3++;
        }
        else
        {
            *p3=*p1;
            p1++;p3++;
            *p3=*p2;
            p2++;p3++;
        }
    }
    while(p1<L1.arr+L1.length)
    {
        *p3=*p1;
        p3++;p1++;
    }
    while(p2<L2.arr+L2.length)
    {
        *p3=*p2;
        p3++;p2++;
    }
    L3.length = L1.length + L2.length;
}

void ListTraverse(SqList&L) //遍历写入
{
    int *p=L.arr;
    int n;
    // 【提示】在调用前确保 L 已经被初始化/清空
    cout << "请依次输入要插入的整数，按回车键确认。输入任一非数字字符（如字母、#、或其他符号）后按回车，将结束本次输入。\n";
    while(cin>>n)
    {
        ListInsert(L,n,L.length+1);
    }
    // 【核心修复】清除 cin 的 fail 状态标志，并清空缓冲区中的残留字符
    cin.clear();         
    cin.ignore(10000,'\n'); 
}

void ListPrint(SqList L1)  //遍历打印
{
    if (L1.length == 0) {
        cout << "[空列表]\n";
        return;
    }

    cout << "[";
    for(int i = 0; i < L1.length; ++i) {
        cout << L1.arr[i];
        if (i < L1.length - 1) {
            cout << ", ";
        }
    }
    cout << "]\n";
}

int ListOrderInsert(SqList &L,int num) //递增插入有序表
{
    if(L.length>=L.listsize) //当存储空间已满时，增添内存分配
    /* 补充：如果用C++的new方式反而会变得更麻烦（需要手动复制，还要删除以前分配的内存）
    int* new_arr = new int[L.listsize + LIST_INCREMENT];
    // 拷贝旧数据
    for(int i = 0; i < L.length; i++)
    {
        new_arr[i] = L.arr[i];
    }
    // 释放旧空间
    delete[] L.arr;
    L.arr = new_arr;
    L.listsize += LIST_INCREMENT;
    */
    {
        int* new_arr;
        new_arr=(int*)realloc(L.arr,(L.listsize+LIST_INCREMENT)*sizeof(int));
        if(new_arr==NULL) exit(1); //内存分配失败退出
        L.listsize+=LIST_INCREMENT;
        L.arr=new_arr;
    }
    int *p=L.arr;
    int i=0;
    while(p<L.arr+L.length&&*p<num) {p++;i++;} //注意while循环的条件！而且两个判断语句不要搞反
    for(int j=L.length-1;j>=i;--j)
    {
        L.arr[j+1]=L.arr[j];
    }
    L.arr[i]=num;
    L.length++;
    return 1; 
}

void ListDestroy(SqList &L) //销毁数组
{
    if(L.arr!=NULL)
    {
        free(L.arr);
        L.arr=NULL;
        L.length=0;
        L.listsize=0;
    }
}
