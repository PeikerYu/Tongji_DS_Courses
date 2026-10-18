//这个文件用于存放所有共享的定义和声明
#pragma once
#include<stdlib.h>
#include<stddef.h> //包含NULL等定义
//宏定义
#define LIST_INT_SIZE 100 //数组存储空间的初始分配量
#define LIST_INCREMENT 10 //线性表存储空间的分配增量
//结构体定义
struct SqList  
{
    int *arr; //存储空间基地址
    int length; //当前长度
    int listsize; //当前分配的存储容量（这里以sizeof(int)为准）
};
//函数声明
int InitSqList(SqList &L); //构造一个空的线性表
int ListInsert(SqList &L,int num,int pos); //在L中第pos个位置之前插入新元素num
int ListDelete(SqList&L,int pos,int&e); //删除函数
int ListLocate(SqList&L,int num); //查找
void ListMerge(const SqList&L1,const SqList&L2,SqList &L3);  //将两个非递减顺序表按非递减方式排列
void ListTraverse(SqList&L); //遍历写入
void ListPrint(SqList L1);  //遍历打印
int ListOrderInsert(SqList &L,int num); //递增插入有序表
void ListDestroy(SqList &L); //销毁数组

