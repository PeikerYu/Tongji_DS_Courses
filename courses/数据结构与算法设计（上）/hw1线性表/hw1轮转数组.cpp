// w1:两次循环迭代
#include <iostream>
using namespace std;
int main()
{
	int n, k;
	cin >> n >> k;
	int *arr=new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	int t;
	for (int i = 0; i < k; i++) //双重循环，第一层循环移动次数，第二层遍历数组内所有元素
	{
		t = arr[n - 1];   // 保存最后一个元素
		for (int j = n - 2; j >= 0; j--)
			arr[j + 1] = arr[j];   // 所有元素右移一位
		arr[0] = t;       // 把末尾放到首位
	}
	for (int i = 0; i < n; i++)
		cout<<arr[i]<<" ";
}
//w2:创建新数组
#include <iostream>
using namespace std;
int main()
{
	int n, k;
	cin >> n >> k;
	int *arr=new int[n];
	int *arr_new=new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	for (int i = 0; i < n; i++)
		arr_new[(i + k) % n] = arr[i]; //新位置计算
	arr = arr_new; //赋值回原数组
}
//w3:使用reverse函数
#include <iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n, k;
	cin >> n >> k;
	int *arr=new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	reverse(arr, arr+n);         // 先整体反转
	reverse(arr, arr + k%n); // 反转前 k 个
	reverse(arr + k%n, arr);   // 反转剩余部分
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}