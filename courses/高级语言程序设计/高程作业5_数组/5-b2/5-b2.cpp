/* 2451951 大数据 于沛可*/
#include<iostream>
using namespace std;
int main()
{
	int arr[100];
	for (int i = 0; i < 100; i++)
	{
		arr[i] = -1;
	}
	for (int i = 1; i <= 100; i++)
	{
		for (int j = i; j <= 100; j += i)
		{
			arr[j - 1] *= (-1);
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (arr[i] == 1)
			cout << i + 1 << " ";
	}
	cout << endl;
	return 0;
}