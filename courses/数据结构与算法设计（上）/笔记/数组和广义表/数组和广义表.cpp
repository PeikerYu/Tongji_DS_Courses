#include<iostream>
using namespace std;
#define MAX_ARRAY_DIM 8 //定义最大维数
struct Array
{
    int *base;
    int dim;
    int *bound; //bounds 是一个长度为 dim 的整型数组，用来存每一维的长度
    int *constants; //地址计算用的乘数（把多维下标变成一维偏移）
};

//三元组：用来存放稀疏矩阵中的非零元
#define MAXSIZE 10000 //非零元最大个数值
struct Triple
{
    int i,j; //行下标和列下标
    int e; //该位置的值
};
struct TSMatrix
{
    Triple data[MAXSIZE+1]; //存非零元
    int mu,nu,tu; //行数、列数、非零元个数
};

//稀疏矩阵的转置
void Transpose(TSMatrix M,TSMatrix &T)
{
    T.mu=M.nu;
    T.nu=M.mu;
    T.tu=M.tu;
    int q;
    if(T.tu!=0)
    {
        for(int col=1;col<=T.mu;col++)
        {
            for(int p=1;p<=M.tu;p++)
            {
                if(M.data[p].j==col)
                {
                    T.data[q].i=M.data[p].j;
                    T.data[q].j=M.data[p].i;
                    T.data[q].e=M.data[p].e;
                    q++;
                }
            }
        }
    }
}

//快速转置 1-based
void FastTranspose(TSMatrix M,TSMatrix &T)
{
    int *num=(int*)malloc(sizeof(int)*(M.nu+1)); //辅助数组：num[col]表示矩阵第col列中非零元的个数
    int *cpot=(int*)malloc(sizeof(int)*(M.nu+1)); //辅助数组：cpot[col]表示第col列的第一个非零元素在T.data中的恰当位置
    T.mu=M.nu;
    T.nu=M.mu;
    T.tu=M.tu;
    if(T.tu!=0)
    {
        for(int col=1;col<=M.nu;col++)
        {
            num[col]=0;
        }
        for(int t=1;t<=M.tu;t++)
        {
            num[M.data[t].j]++;
        }
        //以上是建立Num数组
        cpot[1]=1;
        for(int col=2;col<=M.nu;col++)
        {
            cpot[col]=cpot[col-1]+num[col-1];
        }
        //以上是建立cpot数组 cpot是动态变化的
        for(int p=1;p<=M.tu;p++)
        {
            int col=M.data[p].j;
            int q=cpot[col];
            T.data[q].i=M.data[p].j;
            T.data[q].j=M.data[p].i;
            T.data[q].e=M.data[p].e;
            ++cpot[col];
        }
    }
}