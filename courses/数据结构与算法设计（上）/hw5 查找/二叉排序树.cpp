#include <iostream>
using namespace std;

struct BSTNode
{
    int key;            // 关键字
    int cnt;            // 该关键字出现次数（允许重复）
    BSTNode* left;      // 左子树
    BSTNode* right;     // 右子树
};

BSTNode* root = nullptr;

/**
 * @brief  创建新结点
 * @param  x 关键字
 * @return 新结点指针
 */
BSTNode* NewNode(int x)
{
    BSTNode* p = new BSTNode;
    p->key = x;
    p->cnt = 1;
    p->left = nullptr;
    p->right = nullptr;
    return p;
}

/**
 * @brief  在 BST 中插入一个整数 x（允许重复）
 * @param  root BST 根指针
 * @param  x 要插入的值
 */
void Insert(BSTNode* &root, int x)
{
    if (root == nullptr)
    {
        root = NewNode(x);
        return;
    }

    BSTNode* cur = root;
    BSTNode* parent = nullptr;

    while (cur != nullptr)
    {
        parent = cur;
        if (x == cur->key)
        {
            cur->cnt++;
            return;
        }
        else if (x < cur->key)
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }

    // 找到位置，插入新节点：cur 走到空，parent 是插入位置的父结点
    if (x < parent->key) 
        parent->left = NewNode(x);
    else 
        parent->right = NewNode(x);
}

/**
 * @brief  在 BST 中查找 key==x 的结点
 * @param  root BST 根指针
 * @param  x 要查找的值
 * @return 若存在返回结点指针，否则返回 nullptr
 */
BSTNode* Find(BSTNode* root, int x)
{
    BSTNode* cur = root;
    while (cur != nullptr)
    {
        if (x == cur->key) return cur;
        else if (x < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    return nullptr;
}

/**
 * @brief  查询 x 在集合中出现次数
 * @param  root BST 根指针
 * @param  x 要查询的值
 * @return 出现次数（若不存在返回 0）
 */
int CountKey(BSTNode* root, int x)
{
    BSTNode* p = Find(root, x);
    if (p == nullptr) return 0;
    return p->cnt;
}

/**
 * @brief  查找 BST 中的最小值结点（最左结点）
 * @param  root BST 根指针（保证非空时调用）
 * @return 最小值结点指针
 */
BSTNode* FindMinNode(BSTNode* root)
{
    BSTNode* cur = root;
    while (cur->left != nullptr)
        cur = cur->left;
    return cur;
}

/**
 * @brief  递归删除节点的辅助函数
 * @param  node 当前节点
 * @param  x 要删除的值
 * @param  deleted 是否成功删除
 * @return 删除后的子树根节点
 */
BSTNode* DeleteNode(BSTNode* node, int x, bool &deleted)
{
    if (node == nullptr)
    {
        deleted = false;
        return nullptr;
    }
    if (x < node->key)
    {
        node->left = DeleteNode(node->left, x, deleted);
        return node;
    }
    else if (x > node->key)
    {
        node->right = DeleteNode(node->right, x, deleted);
        return node;
    }
    else  // x == node->key
    {
        deleted = true;
        // 如果有重复，只减少计数
        if (node->cnt > 1)
        {
            node->cnt--;
            return node;
        }

        // 以下是cnt == 1，需要删除节点的情况：
        // 情况1：叶子节点或只有一个子节点
        if (node->left == nullptr)
        {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        // 情况2：有两个子节点
        // 找右子树的最小节点（后继）
        BSTNode* minRight = FindMinNode(node->right);
        
        // 用后继的值替换当前节点
        node->key = minRight->key;
        node->cnt = minRight->cnt;
        
        // 删除后继节点（注意：将后继的cnt设为1，确保删除整个节点）
        minRight->cnt = 1;
        bool dummyDeleted = false;
        node->right = DeleteNode(node->right, minRight->key, dummyDeleted);
        
        return node;
    }
}

/**
 * @brief  删除一个整数 x（若存在只删除一个）
 * @param  root BST 根指针（引用，可能改变根）
 * @param  x 要删除的值
 * @return true 表示删除成功；false 表示不存在
 */
bool DeleteOne(BSTNode* &root, int x)
{
    bool deleted = false;
    root = DeleteNode(root, x, deleted);
    return deleted;
}

/**
 * @brief  查询 x 的前驱：集合中严格小于 x 的最大值
 * @param  root BST 根指针
 * @param  x 查询值（x 不一定在树中）
 * @param  hasPred 输出参数：是否存在前驱
 * @return 若存在前驱，返回前驱值；否则返回值无意义（配合 hasPred 使用）
 */
int Predecessor(BSTNode* root, int x, bool &hasPred)
{
    BSTNode* cur = root;
    BSTNode* pred = nullptr;
    while (cur != nullptr)
    {
        if (cur->key < x)
        {
            pred = cur;
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }
    }
    hasPred = (pred != nullptr);
    if (!hasPred) return 0;
    return pred->key;
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int op;
        cin >> op;

        if (op == 1)
        {
            int x;
            cin >> x;
            Insert(root, x);
        }
        else if (op == 2)
        {
            int x;
            cin >> x;
            bool ok = DeleteOne(root, x);
            if (!ok) cout << "None\n";
        }
        else if (op == 3)
        {
            int x;
            cin >> x;
            cout << CountKey(root, x) << "\n";
        }
        else if (op == 4)
        {
            // 题目保证集合非空
            BSTNode* p = FindMinNode(root);
            cout << p->key << "\n";
        }
        else if (op == 5)
        {
            int x;
            cin >> x;
            bool hasPred = false;
            int pred = Predecessor(root, x, hasPred);
            if (!hasPred) cout << "None\n";
            else cout << pred << "\n";
        }
    }

    return 0;
}