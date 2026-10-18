/* 2451951 大数据 于沛可 */
#include <iostream>
#include <conio.h>
#include "7-b6.h"
using namespace std;

/* 给出 Date 类的所有成员函数的体外实现 */
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
/* 无参构造 */
Date::Date()
{
    year = 2000;
    month = 1;
    day = 1;
}

/* 三参构造 */
Date::Date(int y, int m, int d)
{
    set(y, m, d);
}

/* 一参构造（天数） */
Date::Date(int num)
{
    if (num < 1) 
        num = 1;
    if (num > 73049) 
        num = 73049;

    year = 1900;
    month = 1;
    day = 1;

    num--;  // 从1900.1.1开始

    while (num > 0) 
    {
        int days = is_leap(year) ? 366 : 365;
        if (num >= days)
        {
            num -= days;
            year++;
        }
        else break;
    }

    for (month = 1; month <= 12; month++) 
    {
        int dm = days_in_month(year, month);
        if (num >= dm)
        {
            num -= dm;
        }
        else break;
    }

    day += num;
}

/* set 函数 */
void Date::set(int y, int m, int d)
{
    // 年
    if (y != 0) 
    {
        if (y < 1900 || y > 2099)
            year = 2000;
        else
            year = y;
    }

    // 月
    if (m != 0) 
    {
        if (m < 1 || m > 12)
            month = 1;
        else
            month = m;
    }

    // 日
    if (d != 0)
    {
        int maxd = days_in_month(year, month);
        if (d < 1 || d > maxd)
            day = 1;
        else
            day = d;
    }
}

/* get */
void Date::get(int& y, int& m, int& d) const
{
    y = year;
    m = month;
    d = day;
}

/* show */
void Date::show() const
{
    cout << year << "." << month << "." << day << endl;
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
/* 判断闰年 */
bool is_leap(int y)
{
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

/* 返回某年某月的天数 */
int days_in_month(int y, int m)
{
    int d[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && is_leap(y))
        return 29;
    return d[m - 1];
}
