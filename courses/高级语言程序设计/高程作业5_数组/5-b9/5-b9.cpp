/* 2451951 大数据 于沛可 */
#include <iostream>
using namespace std;
bool isSudoku(int arr[9][9])
{
	bool tag = 1;
	int count_num_row[9][9] = { 0 }; //列：数字   行：数字在第几行  存储的数：该列的数字在该行总共出现了多少次
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			count_num_row[i][arr[i][j] - 1]++;
			if (count_num_row[i][arr[i][j] - 1] > 1)
			{
				tag = 0;
			}
		}
	int count_num_col[9][9] = { 0 }; //行：数字   列：数字在第几列  存储的数：该行的数字在该列总共出现了多少次
	for (int j = 0; j < 9; j++)
		for (int i = 0; i < 9; i++)
		{
			count_num_col[j][arr[i][j] - 1]++;
			if (count_num_col[j][arr[i][j] - 1] > 1)
			{
				tag = 0;
			}
		}
	for (int block = 0; block < 9; block++)
	{
		int count[9] = { 0 };
		for (int k = 0; k < 9; k++)
		{
			int row = (block / 3) * 3 + (k / 3); //行起点+行偏移
			int col = (block % 3) * 3 + (k % 3); //列起点+列偏移
			int num = arr[row][col] - 1;
			count[num]++;
			if (count[num] > 1)
			{
				tag = 0;
			}
		}
	}
	return tag;
}
int main()
{
	cout << "请输入9*9的矩阵，值为1-9之间\n";
	int arr[9][9];
	for(int i=0;i<9;i++)
		for (int j = 0; j < 9; j++)
		{
			while(1)
			{
				cin >> arr[i][j];
				if (!cin.good())
				{
					cout << "请重新输入第" << i + 1 << "行" << j + 1 << "列(行列均从1开始计数)的值\n";
					cin.clear();
					cin.ignore(65536, '\n');
					continue;
				}
				else if (cin.good() && (arr[i][j] > 9 || arr[i][j] < 1))
				{
					cout << "请重新输入第" << i + 1 << "行" << j + 1 << "列(行列均从1开始计数)的值\n";
					continue;
				}
				else
					break;
			}
		}
	cout << (isSudoku(arr) ? "是" : "不是") << "数独的解\n";
	return 0;
}