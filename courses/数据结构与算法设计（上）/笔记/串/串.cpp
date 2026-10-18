#include<iostream>
using namespace std;

//串的顺序存储
//静态数组实现（定长）
#define MAXLEN 100
struct SString
{
    char ch[MAXLEN];
    int length; //串的实际长度
};

//动态数组实现
struct HString
{
    char *ch;
    int length;
};

void InitHString(HString &s)
{
    s.ch=(char *)malloc(MAXLEN*sizeof(char));
    s.length=0;
}

//串的区块链实现
#define CHUNKSIZE 20
struct Chunk
{
    char ch[CHUNKSIZE];
    Chunk *next;
};
struct LString
{
    Chunk *head,*tail;
    int curlen;
};

//串的插入，在第pos个字符之前
bool StrInsert(HString &s,int pos,HString t)
{
    int i;
    if(pos<1||pos>s.length+1)
        return false;
    if(t.length!=0)
    {
        s.ch=(char*)realloc(s.ch,sizeof(char)*(s.length+t.length)); //扩容
        for(int i=s.length-1;i>=pos-1;i--) //将s里原有位置整体右移
        {
            s.ch[i+t.length]=s.ch[i];
        }
        for(int i=0;i<t.length;i++)
        {
            s.ch[pos-1+i]=t.ch[i];
        }
        s.length+=t.length; //更新长度
    }
}

int StrCompare(HString s,HString t) //比较两个串
{
    for(int i=0;s.length<t.length;i++)
    {
        if(s.ch[i]!=t.ch[i])
            return s.ch[i]-t.ch[i];
        return s.length-t.length;
    }
}

void ClearString(HString &s) //清空/销毁串
{
    if(s.ch!=NULL)
    {
        free(s.ch);
        s.length=0;
    }
}

void StrAssign(HString &s,char *chars) //生成一个值为串常量的串s
{
    char *c=chars;
    int length_chars;
    for(length_chars=0;*c!='\0';length_chars++,c++) //求传入的串长度
        ;
    if(length_chars==0)
    {
        s.ch=NULL;
        s.length=0;
    }
    else
    {
        s.ch=(char*)malloc(sizeof(char)*length_chars);
        for(int j=0;j<=length_chars-1;j++)
        {
            s.ch[j]=chars[j];
        }
        s.length=length_chars;
    }
}

void StirngCat(HString s1,HString s2,HString &s)
{
    s.ch=(char*)malloc(sizeof(char)*(s1.length+s2.length));
    s.length=s1.length+s2.length;
    int i;
    for(i=0;i<=s1.length-1;i++)
    {
        s.ch[i]=s1.ch[i];
    }
    for(int j=0;j<=s2.length;j++)
    {
        s.ch[i+j]=s2.ch[j];
    }
}

//用sub串返回串s的第pos个字符开始长度为len的子串
bool substring(HString &s,HString &sub,int pos,int len)
{
    if(pos<1||pos>s.length||len<0||len>s.length-pos+1)
        return false;
    if(len==0)
    {
        sub.ch=NULL;
        sub.length=0;
    }
    else
    {
        sub.ch=(char*)malloc(len*sizeof(char));
        for(int j=0;j<len;j++)
        {
            sub.ch[j]=s.ch[j+pos-1];
        }
        sub.length=len;
        return 1;
    }
}

//朴素模式匹配
int Index(SString S,SString T)
{
    int n=S.length;
    int m=T.length;
    SString sub;
    int i=0,j;
    bool tag=1;
    while(i<n-m+1) //最多匹配n-m+1个子串
    {
        for(j=0;j<m;j++)
        {
            if(T.ch[j]!=S.ch[j+i])
            {
                break;
            }
        }
        if(j==m)
        {
            return i+1;
        }
        i++;
    }
    return -1;
}