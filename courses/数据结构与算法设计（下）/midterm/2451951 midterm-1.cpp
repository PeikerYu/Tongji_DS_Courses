// 第k小元素：三种方法对比
// 方法1：基于堆的选择  O(k + (n-k)*logk)
// 方法2：随机划分线性选择 (QuickSelect)  期望O(n)，最坏O(n^2)
// 方法3：中位数的中位数线性选择  最坏O(n)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;

// ===== 方法1：大根堆选择 =====
// 用容量为k的大根堆维护最小的k个数，堆顶即为第k小
int heapSelect(vector<int> arr, int k) {
    priority_queue<int> pq;
    for (int i = 0; i < k; i++) pq.push(arr[i]);
    for (int i = k; i < (int)arr.size(); i++) {
        if (arr[i] < pq.top()) {
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}

// ===== 方法2：随机划分线性选择 =====
int randPartition(vector<int>& a, int l, int r) {
    int p = l + rand() % (r - l + 1);
    swap(a[p], a[r]);
    int pivot = a[r], i = l - 1;
    for (int j = l; j < r; j++)
        if (a[j] <= pivot) swap(a[++i], a[j]);
    swap(a[++i], a[r]);
    return i;
}

int randSelect(vector<int>& a, int l, int r, int k) {
    if (l == r) return a[l];
    int q = randPartition(a, l, r);
    int cnt = q - l + 1;
    if (k == cnt) return a[q];
    if (k < cnt) return randSelect(a, l, q - 1, k);
    return randSelect(a, q + 1, r, k - cnt);
}

// ===== 方法3：中位数的中位数线性选择 =====
// 每5个一组排序取中位数，递归找中位数的中位数作pivot，保证最坏O(n)
int medianSelect(vector<int>& a, int l, int r, int k) {
    int n = r - l + 1;
    if (n <= 5) {
        sort(a.begin() + l, a.begin() + r + 1);
        return a[l + k - 1];
    }

    // 每组5个排序，收集中位数
    vector<int> meds;
    for (int i = l; i <= r; i += 5) {
        int j = min(i + 4, r);
        sort(a.begin() + i, a.begin() + j + 1);
        meds.push_back(a[(i + j) / 2]);
    }

    // 递归求中位数的中位数
    int mm = (int)meds.size();
    int pivot = medianSelect(meds, 0, mm - 1, (mm + 1) / 2);

    // 在[l,r]中找pivot所在位置，移到末尾
    int pivotPos = l;
    for (int i = l; i <= r; i++)
        if (a[i] == pivot) { pivotPos = i; break; }
    swap(a[pivotPos], a[r]);

    // 以pivot划分
    int p = l - 1;
    for (int j = l; j < r; j++)
        if (a[j] <= pivot) swap(a[++p], a[j]);
    swap(a[++p], a[r]);

    int rank = p - l + 1;
    if (k == rank) return a[p];
    if (k < rank) return medianSelect(a, l, p - 1, k);
    return medianSelect(a, p + 1, r, k - rank);
}

using hrc = chrono::high_resolution_clock;

int main() {
    srand(42);

    // ===== 功能验证 =====
    vector<int> test = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    cout << "测试数组: ";
    for (int x : test) cout << x << " ";
    cout << "\n";

    vector<int> sorted_test = test;
    sort(sorted_test.begin(), sorted_test.end());

    cout << left << setw(5) << "k"
         << setw(12) << "堆选择"
         << setw(12) << "随机选择"
         << setw(12) << "线性选择"
         << setw(12) << "正确答案" << "\n";
    cout << string(53, '-') << "\n";

    for (int k = 1; k <= (int)test.size(); k++) {
        vector<int> t1 = test, t2 = test, t3 = test;
        cout << setw(5) << k
             << setw(12) << heapSelect(t1, k)
             << setw(12) << randSelect(t2, 0, t2.size() - 1, k)
             << setw(12) << medianSelect(t3, 0, t3.size() - 1, k)
             << setw(12) << sorted_test[k - 1] << "\n";
    }

    // ===== 不同n，k=n/2 的性能对比 =====
    cout << "\n不同n下的运行时间（微秒），k = n/2\n";
    cout << setw(12) << "n"
         << setw(15) << "堆选择"
         << setw(15) << "随机选择"
         << setw(15) << "线性选择" << "\n";
    cout << string(57, '-') << "\n";

    vector<int> sizes = {10000, 50000, 100000, 500000, 1000000};
    for (int n : sizes) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = rand();
        int k = n / 2;

        vector<int> a1 = arr, a2 = arr, a3 = arr;
        volatile int sink = 0;

        auto t0 = hrc::now();
        sink ^= heapSelect(a1, k);
        auto t1 = hrc::now();
        sink ^= randSelect(a2, 0, n - 1, k);
        auto t2 = hrc::now();
        sink ^= medianSelect(a3, 0, n - 1, k);
        auto t3 = hrc::now();
        (void)sink;

        cout << setw(12) << n
             << setw(15) << chrono::duration_cast<chrono::microseconds>(t1 - t0).count()
             << setw(15) << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
             << setw(15) << chrono::duration_cast<chrono::microseconds>(t3 - t2).count()
             << "\n";
    }

    // ===== 不同k，n=200000 的性能对比 =====
    int N = 200000;
    vector<int> bigArr(N);
    for (int i = 0; i < N; i++) bigArr[i] = rand();

    cout << "\nn=" << N << " 时，不同k的运行时间（微秒）\n";
    cout << setw(12) << "k"
         << setw(15) << "堆选择"
         << setw(15) << "随机选择"
         << setw(15) << "线性选择" << "\n";
    cout << string(57, '-') << "\n";

    vector<int> ks = {1, 2000, 20000, 100000, 180000, 198000, 200000};
    for (int k : ks) {
        vector<int> a1 = bigArr, a2 = bigArr, a3 = bigArr;
        volatile int sink = 0;

        auto t0 = hrc::now();
        sink ^= heapSelect(a1, k);
        auto t1 = hrc::now();
        sink ^= randSelect(a2, 0, N - 1, k);
        auto t2 = hrc::now();
        sink ^= medianSelect(a3, 0, N - 1, k);
        auto t3 = hrc::now();
        (void)sink;

        cout << setw(12) << k
             << setw(15) << chrono::duration_cast<chrono::microseconds>(t1 - t0).count()
             << setw(15) << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
             << setw(15) << chrono::duration_cast<chrono::microseconds>(t3 - t2).count()
             << "\n";
    }

    return 0;
}
