#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

const int MAXV = 5000 + 5;     // n <= 5000
const int MAXE = 5000 + 5;     // 树边数 <= n-1
const int MAXDEP = 80;         // 每行 <70 字符，所以缩进不会太大，给 80 足够

struct Edge //用于表示一条从某个结点指向其孩子结点的边
{
    int to; //这条边指向的结点编号（孩子结点）
    int next; //指向同一起点的下一条边在 edges 数组中的下标
};

int head[MAXV]; // head[u] 存储的是：以 u 为起点的第一条边在 edges 数组中的下标
Edge edges[MAXE]; //edges[i] 表示第 i 条边，按插入顺序存储
int edgeCnt; //当前已经存入的边的数量，新加入的边会存到 edges[edgeCnt] 位置

/**
 * @brief  初始化图（清空邻接表）
 * @param  n 结点数量
 */
void InitGraph(int n)
{
    for (int i = 1; i <= n; ++i) head[i] = -1;
    edgeCnt = 0;
}

/**
 * @brief  添加一条有向边 u -> v（父 -> 子）
 * @param  u 父亲
 * @param  v 孩子
 */
void AddEdge(int u, int v)
{
    edges[edgeCnt].to = v;
    edges[edgeCnt].next = head[u];
    head[u] = edgeCnt;
    edgeCnt++;
}

//家谱
int parentOf[MAXV];   // parentOf[x] = x 的父亲编号；根的父亲为 0
int tin[MAXV];        // DFS 进入时间
int tout[MAXV];       // 子树范围的最大 tin（不单独 ++timer 退出，tout 是当前 timer）
int timerCnt;

/**
 * @brief  去掉字符串末尾的 '.'（用于解析语句最后的名字）
 * @param  s 输入输出字符串
 */
void TrimDot(string &s)
{
    if (!s.empty() && s.back() == '.') s.pop_back();
}

/**
 * @brief  统计行首空格数（缩进深度）
 * @param  line 一行原始字符串
 * @return 行首空格数量
 */
int CountLeadingSpaces(const string &line)
{
    int k = 0;
    while (k < (int)line.size() && line[k] == ' ') k++;
    return k;
}

/**
 * @brief  将一行用空格分割成单词序列 tokens
 * @param  line 输入行
 * @param  tokens 输出单词数组
 */
void SplitBySpace(const string &line, vector<string> &tokens)
{
    tokens.clear();
    string cur;
    for (int i = 0; i < (int)line.size(); ++i)
    {
        if (line[i] == ' ')
        {
            tokens.push_back(cur);
            cur.clear();
        }
        else
        {
            cur.push_back(line[i]);
        }
    }
    tokens.push_back(cur);
}

/**
 * @brief  用迭代 DFS 计算 tin/tout（避免递归栈问题）
 * @param  root 根节点编号
 * @param  n 结点数量
 *
 * tin/tout 的定义：
 * - 进入某节点 u 时：tin[u] = ++timer
 * - 退出 u 的整棵子树后：tout[u] = 当前 timer（此时 timer 已经是子树内最大 tin）
 *
 * 因此：
 * u 是 v 的祖先（允许 u==v）当且仅当：
 * tin[u] <= tin[v] 且 tout[u] >= tout[v]
 */
void BuildEulerByIterDFS(int root, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        tin[i] = 0;
        tout[i] = 0;
    }

    timerCnt = 0;

    // 用两个栈：nodeStack 存节点；iterStack 存该节点当前遍历到的边下标
    int nodeStack[MAXV];
    int iterStack[MAXV];
    int top = 0;

    // 入栈 root
    nodeStack[top] = root;
    iterStack[top] = head[root];
    tin[root] = ++timerCnt;
    top++;

    while (top > 0)
    {
        int u = nodeStack[top - 1];
        int &ei = iterStack[top - 1];

        if (ei == -1)
        {
            // u 的所有孩子都处理完了，记录 tout[u]
            tout[u] = timerCnt;
            top--;
            continue;
        }

        // 取一条边 u -> v，并把 ei 往后推进
        int v = edges[ei].to;
        ei = edges[ei].next;

        // 访问孩子 v：入栈
        tin[v] = ++timerCnt;
        nodeStack[top] = v;
        iterStack[top] = head[v];
        top++;
    }
}

/**
 * @brief  判断 u 是否为 v 的祖先（允许 u==v）
 * @param  u 祖先候选
 * @param  v 后代候选
 * @return true/false
 */
bool IsAncestor(int u, int v)
{
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

/**
 * @brief  判断语句关系是否为真
 * @param  mp 名字->编号的映射
 * @param  X 左边名字
 * @param  rel 关系词：child/parent/sibling/descendant/ancestor
 * @param  Y 右边名字
 * @return True/False
 */
bool CheckStatement(map<string, int> &mp, const string &X, const string &rel, const string &Y)
{
    int x = mp[X];
    int y = mp[Y];

    if (rel == "child")
    {
        // X is a child of Y.  => parentOf[x] == y 且 x!=y
        if (x == y) return false;
        return parentOf[x] == y;
    }
    else if (rel == "parent")
    {
        // X is the parent of Y. => parentOf[y] == x 且 x!=y
        if (x == y) return false;
        return parentOf[y] == x;
    }
    else if (rel == "sibling")
    {
        // 兄弟允许自己：X==Y 直接 True
        if (x == y) return true;

        // 根节点没有父亲：与别人不可能是兄弟
        if (parentOf[x] == 0 || parentOf[y] == 0) return false;

        return parentOf[x] == parentOf[y];
    }
    else if (rel == "descendant")
    {
        // X is a descendant of Y. => Y 是 X 的祖先（允许同一人）
        return IsAncestor(y, x);
    }
    else if (rel == "ancestor")
    {
        // X is an ancestor of Y. => X 是 Y 的祖先（允许同一人）
        return IsAncestor(x, y);
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0) break;

        // 读完 n,m 后，下一行开始要用 getline 读整行（含缩进）
        string line;
        getline(cin, line); // 吃掉行尾换行

        map<string, int> mp;        // name -> id
        string names[MAXV];         // id -> name
        int lastAtDepth[MAXDEP];    // lastAtDepth[d] = 最近出现的 depth=d 的节点编号

        for (int i = 0; i < MAXDEP; ++i) lastAtDepth[i] = 0;

        InitGraph(n);

        int root = 0;

        /* 1) 读家谱 n 行：根据缩进确定父子 */
        for (int id = 1; id <= n; ++id)
        {
            getline(cin, line);

            int dep = CountLeadingSpaces(line);
            string name = line.substr(dep);

            names[id] = name;
            mp[name] = id;

            if (dep == 0)
            {
                root = id;
                parentOf[id] = 0;
            }
            else
            {
                // dep>=1：父亲一定是 dep-1 层最后出现的人
                int fa = lastAtDepth[dep - 1];
                parentOf[id] = fa;
                AddEdge(fa, id);
            }

            // 更新该层最新节点
            if (dep < MAXDEP) lastAtDepth[dep] = id;
        }

        /* 2) DFS 建 tin/tout，用于祖先/后代判断 */
        BuildEulerByIterDFS(root, n);

        /* 3) 处理 m 条语句 */
        for (int i = 1; i <= m; ++i)
        {
            getline(cin, line);

            // 分词：格式固定为
            // X is a/the/an REL of Y.
            vector<string> tokens;
            SplitBySpace(line, tokens);

            string X = tokens[0];
            string rel = tokens[3];
            string Y = tokens.back();
            TrimDot(Y);

            bool ok = CheckStatement(mp, X, rel, Y);
            cout << (ok ? "True" : "False") << "\n";
        }

        // 每个测试用例后输出空行
        cout << "\n";
    }

    return 0;
}
