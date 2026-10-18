/* 2451951 大数据 于沛可 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    int year, month, day;
    int total = 0;
    int is_leap, feb_days, max_day;
    printf("请输入年，月，日\n");
    scanf("%d %d %d", &year, &month, &day);
    if (month < 1 || month > 12)
    {
        printf("输入错误-月份不正确\n");
        return 0;
    }
    is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    feb_days = is_leap ? 29 : 28;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        max_day = 31;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        max_day = 30;
    }
    else
    {
        max_day = feb_days;
    }
    if (day < 1 || day > max_day)
    {
        printf("输入错误-日与月的关系非法\n");
        return 0;
    }
    if (month > 1) total += 31;
    if (month > 2) total += feb_days;
    if (month > 3) total += 31;
    if (month > 4) total += 30;
    if (month > 5) total += 31;
    if (month > 6) total += 30;
    if (month > 7) total += 31;
    if (month > 8) total += 31;
    if (month > 9) total += 30;
    if (month > 10) total += 31;
    if (month > 11) total += 30;
    total += day;
    printf("%d-%d-%d是%d年的第%d天\n", year, month, day, year, total);
    return 0;
}