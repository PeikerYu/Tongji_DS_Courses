/* 2451951 大数据 于沛可 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int year, month, week, ret, c;
	while (1) 
	{
		printf("请输入年份(2000-2030)和月份(1-12) : ");
		ret=scanf("%d %d", &year, &month);
		if (ret == 2 && year <= 2030 && year >= 2000 && month <= 12 && month >= 1)
			break;
		if (ret == 2 && (year < 2000 || year>2030 || month < 1 || month>12))
		{
			printf("输入非法，请重新输入\n");
			continue;
		}
		if (ret != 2)
		{
			printf("输入非法，请重新输入\n");
			while ((c = getchar()) != '\n'); //清除输入缓冲区
		}
	}
	while (1)
	{
		printf("请输入%d年%d月1日的星期(0-6表示星期日-星期六) : ",year,month);
		ret = scanf("%d", &week);
		if (ret == 1 && week >= 0 && week <= 6)
			break;
		if (ret == 1 && (week > 6 || week < 0))
		{
			printf("输入非法，请重新输入\n");
			continue;
		}
		if (ret != 1)
		{
			printf("输入非法，请重新输入\n");
			while ((c = getchar()) != '\n'); //清除输入缓冲区
		}
	}
	printf("\n%d年%d月的月历为:\n", year, month);
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
	printf("星期日  星期一  星期二  星期三  星期四  星期五  星期六\n");
	int i = 1, j = 8 * week + 4;
	if (j == 52)
	{
		printf("%52d\n", i);
		j = 4;
	}
	else
	{
		printf("%*d", j, i);
		j += 8;
	}
	for (i = 2; j <= 52; )
	{
		if (i > k)
			break;
		if (j == 4)
		{
			printf("%4d", i++);
		}
		else if (j != 4 && j != 52)
		{
			printf("%8d", i++);
		}
		else if (j == 52)
		{
			printf("%8d\n", i++);
		}
		if (j == 52)
			j = 4;
		else
			j += 8;
	}
	printf("\n");
	return 0;
}