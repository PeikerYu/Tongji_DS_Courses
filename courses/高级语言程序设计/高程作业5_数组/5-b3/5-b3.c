/* 2451951 大数据 于沛可 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int is_leap_fun(int year)
{
    int is_leap;
    is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    return is_leap;
}

int days_fun(int year, int month, int day)
{
    int total = 0;
    int is_leap = is_leap_fun(year);
    int feb_days = is_leap ? 29 : 28;
    int month_max_day[12] = { 31,feb_days,31,30,31,30,31,31,30,31,30,31 };
    if (month < 1 || month > 12)
    {
        printf("输入错误-月份不正确\n");
        return -1;
    }
	if (day < 1 || day > month_max_day[month - 1])
    {
        printf("输入错误-日与月的关系非法\n");
        return -1;
    }
    else
    {
        for (int i = 1; i <= month - 1; i++)
        {
            total += month_max_day[i - 1];
        }
        total += day;
        return total;
    }
}

int main()
{
    int year, month, day;
    printf("请输入年，月，日\n");
    scanf("%d %d %d", &year, &month, &day);
    int total = days_fun(year, month, day);
    if(total!=-1)
        printf("%d-%d-%d是%d年的第%d天\n", year, month, day, year, total);
    return 0;
}