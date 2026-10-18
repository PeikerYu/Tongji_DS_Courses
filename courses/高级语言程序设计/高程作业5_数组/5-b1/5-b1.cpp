/* 2451951 大数据 于沛可*/
#include<iostream>
using namespace std;
int main()
{
	cout << "请输入任意个正整数（升序，最多20个），0或负数结束输入\n";
	int arr[21] = { 0 };
	int temp, count = 0;
	while (1)
	{
		cin >> temp;
		count++;
		if (temp <= 0)
		{
			cin.clear();
			cin.ignore(65536,'\n');
			count--;
			break;
		}
		else if (count < 20)
		{
			arr[count - 1] = temp;
		}
		else if (count == 20)
		{
			arr[count - 1] = temp;
			cin.clear();
			cin.ignore(65536, '\n');
			break;
		}
	}
	if (count == 0)
	{
		cout << "无有效输入\n";
		return 0;
	}
	else
	{
		cout << "原数组为：\n";
		for (int i = 0; i < count; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
	int num;
	cout << "请输入要插入的正整数\n";
	cin >> num;
	int i;
	for (i = 0; i < count; i++)
	{
		if (arr[i] >= num)
		{
			for (int j = count - 1; j >= i; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[i] = num;
			break; //插入后要结束循环！
		}
	}
	if (i == count)
		arr[count] = num;
	cout << "插入后的数组为：\n";
	for (int i = 0; i < count + 1; i++)
		cout << arr[i] << " ";
	cout << endl;
	return 0;
}