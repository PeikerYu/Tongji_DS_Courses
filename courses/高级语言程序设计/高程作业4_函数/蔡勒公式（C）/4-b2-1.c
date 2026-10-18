/* 2451951 大数据 于沛可 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<limits.h>
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
int main()
{
	int year, month, day;
	int ret;
	while (1)
	{
		printf("请输入年[1900-2100]、月、日：\n");
		ret = scanf("%d %d %d", &year, &month, &day);
		if (ret != 3)
		{
			printf("输入错误，请重新输入\n");
			while (getchar() != '\n');
			continue;
		}
		else
		{
			if (year > 2100 || year < 1900)
			{
				printf("年份不正确，请重新输入\n");
				continue;
			}
			else if (month < 1 || month > 12)
			{
				printf("月份不正确，请重新输入\n");
				continue;
			}
			else
			{
				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					if (day < 1 || day > 31)
					{
						printf("日不正确，请重新输入\n");
						continue;
					}
					else
						break;
				}
				else if (month == 4 || month == 6 || month == 9 || month == 11)
				{
					if (day < 1 || day > 30)
					{
						printf("日不正确，请重新输入\n");
						continue;
					}
					else
						break;
				}
				else
				{
					if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
					{
						if (day < 1 || day > 29)
						{
							printf("日不正确，请重新输入\n");
							continue;
						}
						else
							break;
					}
					else
					{
						if (day < 1 || day > 28)
						{
							printf("日不正确，请重新输入\n");
							continue;
						}
						else
							break;
					}
				}
			}
		}
	}
	int res = zeller(year, month, day);
	if(res==0)
		printf("星期日\n");
	else if (res == 1)
		printf("星期一\n");
	else if (res == 2)
		printf("星期二\n");
	else if (res == 3)
		printf("星期三\n");
	else if (res == 4)
		printf("星期四\n");
	else if (res == 5)
		printf("星期五\n");
	else 
		printf("星期六\n");
	return 0;
}
