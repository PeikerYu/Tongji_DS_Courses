#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
递归本身隐式维护了树的层次关系：

每进入一次 dfs 相当于进入一个节点

fatherDepth + childCount + 1 得到当前子节点的深度

遇到 'u' 返回上一层，递归栈自动“弹出”，恢复父节点状态

所以DFS 栈帧就相当于每个节点的 fatherDepth 和 childCount，不需要显式指针或数组维护父子关系。
*/

struct TreeNode 
{
    int fatherDepth;  // 当前节点的父节点在二叉树中的深度
    int childCount;   // 当前节点的已处理孩子数（用于右兄弟偏移计算）
};

int dfs(int fatherDepth,int &i,string &s) //根据字符串构造二叉树，返回最大深度
{
    int maxDepth=fatherDepth; //记录当前二叉树到达的最大深度
    int childCount=0;
    while(i<s.length())
    {
        if(s[i]=='d') //下行进入子节点
        {
            int childDepth=childCount+fatherDepth+1; //记录当前孩子的二叉树深度
            childCount++;
            i++;
            int subDepth=dfs(childDepth,i,s); //递归计算该孩子子树的最大深度
            maxDepth=max(maxDepth,subDepth); //更新最大深度，因为一个节点可能有多个孩子。每个孩子都是一个子树，它们的“最大深度”可以不同。
        }
        else if(s[i]=='u') //返回上一层，相当于递归的边界条件
        {
            i++;
            break;
        }
    }
    return maxDepth;
}

int main() 
{
    string s;
    int count=0; //用来记录打印第几颗树
    while (cin >> s)
    {
        if (!s.empty() && s[0] == '#') break;
        // 计算原树的深度（h1）
        int cur = 0, h1 = 0; //cur为当前深度，h1为当前深度最大值
        for (int i=0;i<s.length();i++) 
        {
            if (s[i] == 'd') 
            {
                ++cur;
                h1 = max(h1, cur); //更新节点最大深度
            }
            else if (s[i] == 'u') {
                --cur;
            }
        }

        // 计算转化后二叉树的深度（h2）
        int i=0;
        int h2=dfs(0,i,s);
        ++count;
        cout<<"Tree "<<count<<": "<<h1<<" => "<<h2<<endl;
    }
    return 0;
}
