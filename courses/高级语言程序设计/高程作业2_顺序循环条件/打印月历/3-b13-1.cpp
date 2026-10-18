/* 2451951 大数据 于沛可 */
#include<iostream>
#include<limits>
#include<iomanip>
using namespace std;
int main()
{
	int year, month, week;
	while (1) 
	{
		cout << "请输入年份(2000-2030)和月份(1-12) : ";
		cin >> year>>month;  
		if (!cin.good())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入非法，请重新输入" << endl;
			continue;
		}
		else
		{
			if(year<2000||year>2030||month<1||month>12)
			{
				cout << "输入非法，请重新输入" << endl;
				continue;
			}
			else
			{
				break;
			}
		}
	}
	while (1)
	{
		cout << "请输入" << year << "年" << month << "月1日的星期(0-6表示星期日-星期六) : ";
		cin >> week;
		if (!cin.good())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入非法，请重新输入" << endl;
			continue;
		}
		else
		{
			if (week > 6 || week < 0)
			{
				cout << "输入非法，请重新输入" << endl;
				continue;
			}
			else
			{
				break;
			}
		}
	}
	cout << "\n" << year << "年" << month << "月的月历为:\n";
	int k; //该月天数
	if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
		k = 31;
	else if(month==4||month==6||month==9||month==11)
		k = 30;
	else
	{
		if((year%4==0&&year%100!=0)||year%400==0)
			k = 29;
		else
			k = 28;
	}
	cout << "星期日  星期一  星期二  星期三  星期四  星期五  星期六" << endl;
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
	for (i=2; j <= 52; )
	{
		if (i > k)
			break;
		if (j == 4)
		{
			cout << setw(j) << (i++);
		}
		else if(j!=4&&j!=52)
		{
			cout << setw(8) << (i++);
		}
		else if(j==52)
		{
			cout << setw(8) << (i++) << endl;
		}
		if (j == 52)
			j = 4;
		else
			j += 8;
	}
	cout << endl;
	return 0;
}