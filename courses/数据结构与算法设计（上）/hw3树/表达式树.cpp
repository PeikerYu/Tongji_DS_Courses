#include<iostream>
#include<stack>
#include<string>
#include<cstring>
using namespace std;

struct Var //建立变量与值之间的关系
{
    char name;
    int val;
};

struct TreeNode
{
    char val; //存储运算符或者变量
    TreeNode *left; //左子树
    TreeNode *right; //右子树
};

void createNode(char ch,TreeNode &tnode) //初始化树的节点
{
    tnode.left=tnode.right=NULL;
    tnode.val=ch;
}

int precedence(char ch) //判断运算符优先级
{
    if(ch=='+'||ch=='-') return 1;
    if(ch=='*'||ch=='/') return 2;
    return 0; // (   )按照顺序则被前面一部分执行
}

/**
 * @brief 中缀表达式转后缀表达式
 * @param s 中缀表达式
 * @return string 后缀表达式
 */
string infixToPostfix(const string& s) //中缀表达式转后缀
{
    stack<char>st; //运算符栈
    string postfix;
    for(int i=0;i<s.length();i++)
    {
        //1.判断是否为数字，若是，则直接进入后缀
        if(isalpha(s[i]))
            postfix+=s[i];
        else if(s[i]=='(') //左括号，直接进栈
            st.push(s[i]);
        else if(s[i]==')') //碰见右括号，栈顶元素循环出栈，进入后缀表达式，直到遇见左括号
        {
            while(!st.empty()&&st.top()!='(')
            {
                postfix+=st.top();
                st.pop();
            }
            if(!st.empty()&&st.top()=='(')
                st.pop();
        }
        else //+ - * /
        {
            while(!st.empty()&& precedence(st.top())>=precedence(s[i])) //栈顶元素优先级更高，则直接进入后缀表达式
            {
                postfix+=st.top();
                st.pop();
            }
            st.push(s[i]);
        }
    }
    while(!st.empty())
    {
        postfix+=st.top();
        st.pop();
    }
    return postfix;
}

int getVarVal(char ch,Var vars[],int n) //根据变量数组查找变量值
{
    for(int i=0;i<n;i++)
    {
        if(vars[i].name==ch)
            return vars[i].val;
    }
    return 0; // 如果没找到，返回0（题目中数据保证变量一定存在）
}
/**
 * @brief 后缀表达式求值
 * @param s 后缀表达式
 * @param vars 变量数组
 * @param n 变量数量
 * @return int 运算结果
 */
int evaluatePostfix(string& s,Var vars[],int n) //后缀表达式求值函数，后置表达式不含（）
{
    stack<int> st;
    for(int i=0;i<s.length();i++)
    {
        //遇见运算符，将栈顶两个元素一次弹出，并做相应运算
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
        {
            int num2=st.top(); //注意先弹出num2
            st.pop();
            int num1=st.top();
            st.pop();
            if(s[i]=='+') st.push(num1+num2);
            if(s[i]=='-') st.push(num1-num2);
            if(s[i]=='*') st.push(num1*num2);
            if(s[i]=='/') st.push(num1/num2);
        }
        //遇见变量（运算数），直接放入栈中
        else
            st.push(getVarVal(s[i],vars,n));
    }
    int res=st.top();
    st.pop();
    return res;
}

int cal_depth(TreeNode *root) //计算树的深度
{
    if(root==NULL)
        return 0;
    return max(cal_depth(root->left),cal_depth(root->right))+1; //递归调用求最大深度
}

TreeNode* buildTreeFromPostfix(const string &postfix) //由后缀表达式构造二叉树
{
    stack<TreeNode*> st;
    for (int i = 0; i < (int)postfix.size(); ++i) 
    {
        char ch = postfix[i];
        TreeNode *node = new TreeNode;
        createNode(ch, *node); // 初始化节点 (left/right=NULL, val=ch)
        if (isalpha(ch)) 
        {
            st.push(node);
        } 
        else 
        {
            // 弹出右、左
            TreeNode *right = st.top(); st.pop();
            TreeNode *left = st.top(); st.pop();
            node->left = left;
            node->right = right;
            st.push(node);
        }
    }
    if (st.empty()) return NULL;
    TreeNode *root = st.top(); st.pop();
    return root;
}

/**
 * @brief 将表达式树绘制到字符矩阵
 * @param root 当前节点
 * @param x 当前行
 * @param y 当前列
 * @param depth 当前递归深度
 * @param gap 当前水平偏移
 * @param h 树总高度
 * @param matrix 500x500字符矩阵
 */
void draw(TreeNode *root, int x, int y, int depth, int gap, int h, char matrix[500][500])
{
    if (root == NULL) return;

    // 1. 将当前节点放到矩阵
    matrix[x][y] = root->val;

    // 2. 左子树
    if (root->left != NULL)
    {
        // 左斜杠连接
        matrix[x + 1][y - 1] = '/';
        // 递归绘制左子树
        // 左子树x+2行，y-gap列
        int nextGap = gap / 2; // 下一层水平间隔减半
        if (nextGap < 1) nextGap = 1; // 保证gap至少为1，避免重叠
        draw(root->left, x + 2, y - gap, depth + 1, nextGap, h, matrix);
    }

    // 3. 右子树
    if (root->right != NULL)
    {
        // 右斜杠连接
        matrix[x + 1][y + 1] = '\\';
        // 递归绘制右子树
        int nextGap = gap / 2; // 下一层水平间隔减半
        if (nextGap < 1) nextGap = 1;
        draw(root->right, x + 2, y + gap, depth + 1, nextGap, h, matrix);
    }
}

int main()
{
    string expr;
    cin>>expr;
    int n;
    cin>>n;
    Var vars[26]; //建立变量与值的映射关系数组，题干中最多十个变量
    for(int i=0;i<n;i++)
        cin>>vars[i].name>>vars[i].val;
    string postfix=infixToPostfix(expr);
    cout<<postfix<<endl; //输出后缀表达式
    TreeNode* root=buildTreeFromPostfix(postfix); //构造树
    int h = cal_depth(root); // 树的高度
    if (h == 0)
    {
        cout << endl << 0 << endl;
        return 0;
    }
    char matrix[500][500];
    memset(matrix, ' ', sizeof(matrix));

    // 1. 矩阵总列数 = 2^h - 1
    int width = (1 << h) - 1; // 等价于pow(2,h)-1
    // 2. 根节点列 = 居中
    int root_col = (width - 1) / 2;
    // 3. 初始gap = 2^(h-2)，保证底层叶子间隔2
    int initialGap = 1;
    if (h >= 2) initialGap = 1 << (h - 2);

    // 绘制树到矩阵
    draw(root, 0, root_col, 1, initialGap, h, matrix);

    // 输出矩阵内容
    for (int i = 0; i < 2 * h - 1; i++) // 树每层占两行（节点+连接）
    {
        int j = 499;
        while (j >= 0 && matrix[i][j] == ' ') 
            j--;
        for (int k = 0; k <= j; k++) 
            cout << matrix[i][k];
        cout << endl;
    }
    int value=evaluatePostfix(postfix,vars,n);
    cout<<value<<endl; //输出计算结果
    return 0;
}
