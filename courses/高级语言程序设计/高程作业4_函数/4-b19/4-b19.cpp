/* 2451951 于沛可 大数据 */
#include<iostream>
using namespace std;
#define MAX 2147483647
int min(int x1, int x2, int x3 = MAX, int x4 = MAX)
{
	int res = x1;
	if (res > x2)
		res = x2;
	if (res > x3)
		res = x3;
	if (res > x4)
		res = x4;
	return res;
}

int main()
{
	int num;
	while (1)
	{
		cout << "请输入个数num及num个正整数：\n";
		cin >> num;
		if (num == 2)
		{
			int x1, x2;
			cin >> x1 >> x2;
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(65536, '\n');
				continue;
			}
			else if (x1 <= 0 || x2 <= 0)
			{
				cin.clear();
				cin.ignore(65536, '\n');
				continue;
			}
			else
			{
				int res = min(x1, x2);
				cout << "min=" << res << endl;
				return 0;
			}
		}
		else if (num == 3)
		{
			int x1, x2, x3;
			cin >> x1 >> x2 >> x3;
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(65536, '\n');
				continue;
			}
			else if (x1 <= 0 || x2 <= 0 || x3 <= 0)
			{
				cin.clear();
				cin.ignore(65536, '\n');
				continue;
			}
			else
			{
				int res = min(x1, x2, x3);
				cout << "min=" << res << endl;
				return 0;
			}
		}
		else if (num == 4)
		{
			int x1, x2, x3, x4;
			cin >> x1 >> x2 >> x3 >> x4;
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(65536, '\n');
				continue;
			}
			else if (x1 <= 0 || x2 <= 0 || x3 <= 0 || x4 <= 0)
			{
				cin.clear();
				cin.ignore(65536, '\n');
				continue;
			}
			else
			{
				int res = min(x1, x2, x3, x4);
				cout << "min=" << res << endl;
				return 0;
			}
		}
		else if (!cin.good())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		else
		{
			cout << "个数输入错误\n";
			return 0;
		}
	}
}

