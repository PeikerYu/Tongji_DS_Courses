
// #include <iostream>
// #define MAXSIZE 100500
// using namespace std;

// struct TreeNode {
//     bool infected;
//     int lchild, rchild, parent;
// };

// struct Queue {
//     int data[MAXSIZE];
//     int front, rear;
// };

// #define NEXT(x) ((x + 1) % MAXSIZE)

// void InitQueue(Queue &q) { q.front = q.rear = 0; }
// bool IsEmpty(Queue &q) { return q.front == q.rear; }
// void EnQueue(Queue &q, int x) { q.data[q.rear] = x; q.rear = NEXT(q.rear); }
// int DeQueue(Queue &q) { int val = q.data[q.front]; q.front = NEXT(q.front); return val; }

// TreeNode* BuildTree(int n) {
//     TreeNode* tree = new TreeNode[n];
//     for (int i = 0; i < n; i++) {
//         tree[i].infected = false;
//         tree[i].parent = -1;
//     }
//     for (int i = 0; i < n; i++) {
//         cin >> tree[i].lchild >> tree[i].rchild;
//         if (tree[i].lchild != -1) tree[tree[i].lchild].parent = i;
//         if (tree[i].rchild != -1) tree[tree[i].rchild].parent = i;
//     }
//     return tree;
// }

// int SpreadTime(TreeNode* tree, int start) {
//     Queue q; InitQueue(q);
//     EnQueue(q, start);
//     tree[start].infected = true;
//     int time = -1;
//     while (!IsEmpty(q)) {
//         int size = (q.rear - q.front + MAXSIZE) % MAXSIZE;
//         while (size--) {
//             int curr = DeQueue(q);
//             int arr[3] = {tree[curr].parent, tree[curr].lchild, tree[curr].rchild};
//             for (int j = 0; j < 3; j++) {
//                 int nxt = arr[j];
//                 if (nxt != -1 && !tree[nxt].infected) {
//                     tree[nxt].infected = true;
//                     EnQueue(q, nxt);
//                 }
//             }
//         }
//         time++;
//     }
//     return time;
// }

// int main() {
//     int n, start;
//     cin >> n >> start;
//     TreeNode* tree = BuildTree(n);
//     cout << SpreadTime(tree, start) << endl;
//     delete[] tree;
//     return 0;
// }
