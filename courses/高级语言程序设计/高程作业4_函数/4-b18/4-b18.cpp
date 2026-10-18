/* 2451951 于沛可 大数据 */
#include<iostream>
using namespace std;

int max(int x1, int x2)
{
	return ((x1 > x2) ? x1 : x2);
}

int max(int x1, int x2, int x3)
{
	int t = ((x1 > x2) ? x1 : x2);
	return ((t > x3) ? t : x3);
}

int max(int x1, int x2, int x3, int x4)
{
	int t1 = ((x1 > x2) ? x1 : x2);
	int t2 = ((x3 > x4) ? x3 : x4);
	return ((t1 > t2) ? t1 : t2);
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
				int res = max(x1, x2);
				cout << "max=" << res << endl;
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
				int res = max(x1, x2, x3);
				cout << "max=" << res << endl;
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
				int res = max(x1, x2, x3, x4);
				cout << "max=" << res << endl;
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
