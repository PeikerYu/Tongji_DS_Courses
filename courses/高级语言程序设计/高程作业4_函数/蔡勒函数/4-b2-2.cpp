/* 2451951 大数据 于沛可 */
#include<iostream>
#include<limits>
using namespace std;
int zeller(int y, int m, int d)
{
	int w;
	if(m == 1 || m == 2)
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
int main()
{
	int year, month, day;
	while (1)
	{
		cout << "请输入年[1900-2100]、月、日：" << endl;
		cin >> year >> month >> day;
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
		{
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			{
				if (day < 1 || day > 31)
				{
					cout << "日不正确，请重新输入" << endl;
					continue;
				}
				else
					break;
			}
			else if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				if (day < 1 || day > 30)
				{
					cout << "日不正确，请重新输入" << endl;
					continue;
				}
				else
					break;
			}
			else if (month == 2)
			{
				bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
				if (isLeap)
				{
					if (day < 1 || day > 29)
					{
						cout << "日不正确，请重新输入" << endl;
						continue;
					}
					else
						break;
				}
				else
				{
					if (day < 1 || day > 28)
					{
						cout << "日不正确，请重新输入" << endl;
						continue;
					}
					else
						break;
				}
			}
		}
	}
	int res = zeller(year, month, day);
	if (res == 0)
		cout << "星期日" << endl;
	else if (res == 1)
		cout << "星期一" << endl;
	else if (res == 2)
		cout << "星期二" << endl;
	else if (res == 3)
		cout << "星期三" << endl;
	else if (res == 4)
		cout << "星期四" << endl;
	else if (res == 5)
		cout << "星期五" << endl;
	else
		cout << "星期六" << endl;
	return 0;
}