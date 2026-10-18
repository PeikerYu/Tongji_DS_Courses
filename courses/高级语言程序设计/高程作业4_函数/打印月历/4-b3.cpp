/* 2451951 大数据 于沛可 */
#include<iostream>
#include<limits>
#include<iomanip>
using namespace std;
int zeller(int y, int m, int d)
{
	int w;
	if (m == 1 || m == 2)
	{
		m += 12;
		y--;
	}
	int c1 = y / 1000;
	int c2 = (y % 1000) / 100;
	int c3 = (y % 100) / 10;
	int c4 = y % 10;
	int c = 10 * c1 + c2;
	y = 10 * c3 + c4;
	w = (y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1);
	while (w < 0)
	{
		w += 7;
	}
	return w % 7;
}

void calendar(int year, int month)
{
	int k; //该月天数
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		k = 31;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		k = 30;
	else
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			k = 29;
		else
			k = 28;
	}
	int week = zeller(year, month, 1); //该月1号是星期几

	cout << endl;
	cout << year << "年" << month << "月" << endl;
	cout << "======================================================" << endl;
	cout << "星期日  星期一  星期二  星期三  星期四  星期五  星期六" << endl;
	cout << "======================================================" << endl;
	int i = 1, j = 8 * week + 4;
	if (j == 52)
	{
		cout << setw(j) << i << endl;
		j = 4;
	}
	else
	{
		cout << setw(j) << i;
		j += 8;
	}
	for (i = 2; j <= 52; )
	{
		if (i > k)
			break;
		if (j == 4)
		{
			cout << setw(j) << (i++);
		}
		else if (j != 4 && j != 52)
		{
			cout << setw(8) << (i++);
		}
		else if (j == 52)
		{
			cout << setw(8) << (i++) << endl;
		}
		if (j == 52)
			j = 4;
		else
			j += 8;
	}
	if (j != 4)
		cout << endl;
	cout << "======================================================" << endl;
}

int main()
{
	int year, month;
	while (1)
	{
		cout << "请输入年[1900-2100]、月" << endl;
		cin >> year >> month;
		if (!cin.good())
		{
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else if (year > 2100 || year < 1900)
		{
			cout << "年份不正确，请重新输入" << endl;
			continue;
		}
		else if (month < 1 || month > 12)
		{
			cout << "月份不正确，请重新输入" << endl;
			continue;
		}
		else
			break;
	}
	calendar(year, month);
	return 0;
}