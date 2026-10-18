/* 2451951 大数据 于沛可 */
#include <iostream>
using namespace std;
int main()
{
	cout << "请输入成绩（最多1000个），负数结束输入\n";
	int arr_score[1000];
	int temp, count = 0;
	while (1)
	{
		cin >> temp;
		count++;
		if (temp < 0)
		{
			count--;
			break;
		}
		else if (count == 1000)
		{
			arr_score[count - 1] = temp;
			break;
		}
		else
			arr_score[count - 1] = temp;
	}
	if (count == 0)
		cout << "无有效输入\n";
	else
	{
		cout << "输入的数组为:\n";
		for (int i = 0; i < count; i++)
		{
			cout << arr_score[i] << " ";
			if ((i + 1) % 10 == 0)
				cout << "\n";
		}
		if (count % 10 != 0)
			cout << "\n";
	}
	int rank = 1;
	int arr_num[101] = { 0 };
	for (int i = 0; i < count; i++)
	{
		arr_num[arr_score[i]]++;
	}
	cout << "分数与名次的对应关系为:\n";
	for (int i = 100; i >= 0; i--)
	{
		if (arr_num[i] == 1)
		{
			cout << i << " " << rank << endl;
			rank++;
		}
		else if (arr_num[i] > 1)
		{
			for (int j = 0; j < arr_num[i]; j++)
				cout << i << " " << rank << endl;
			rank += arr_num[i];
		}	
	}
	return 0;
}



