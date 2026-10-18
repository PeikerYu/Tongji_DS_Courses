/* 2451951 大数据 于沛可 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int CAL_CELL_WIDTH = 4; //每格的宽度
const int MONTH_TABLE_WIDTH = 7 * CAL_CELL_WIDTH; // 一个月的宽度：7*4=28
const int MAX_ROW_HEIGHT = 8;  // 1+1+6= 8
const int GAP_WIDTH = 4;       // 月份之间固定间隔
const int MAX_MONTHS_PER_ROW = 12;  //一行最大显示的月份数
const int MAX_TOTAL_ROW_WIDTH = MAX_MONTHS_PER_ROW * MONTH_TABLE_WIDTH + (MAX_MONTHS_PER_ROW - 1) * GAP_WIDTH; //在屏幕上最大显示的行宽

int week_zeller(int y, int m) //该月1号是星期几
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
	w = (y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + 1 - 1);
	while (w < 0)
	{
		w += 7;
	}
	return w % 7;
}

int is_leap(int y) //是否为闰年
{
    return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);
}


//将一个月份填入8*28的month_buffer缓冲区
void draw_month_to_buffer(int year, int month,char buffer[MAX_ROW_HEIGHT][MONTH_TABLE_WIDTH + 1])
{
    //初始化：全部填空格
    for (int r = 0; r < MAX_ROW_HEIGHT; r++) 
    {
        for (int c = 0; c < MONTH_TABLE_WIDTH; c++)
            buffer[r][c] = ' ';
        buffer[r][MONTH_TABLE_WIDTH] = '\0';
    }

    //1.写第几个月标题
    char title[8];
    int i = 0;
    if (month >= 10) 
    {
        title[i++] = (month / 10) + '0'; //写入十位数字
    }
    title[i++] = (month % 10) + '0'; //个位
    title[i] = '\0';
    strcat(title, "月");

    int title_len = strlen(title);
    int left;
    if (month >= 10)
        left = 11;
    else
        left = (MONTH_TABLE_WIDTH - title_len) / 2;

    for (int i = 0; i < title_len; i++)
        buffer[0][left + i] = title[i];

    //写星期行
    char weekstr[30] = "Sun Mon Tue Wed Thu Fri Sat";
    int wklen = strlen(weekstr);
    for (int i = 0; i < wklen; i++)
        buffer[1][i] = weekstr[i];
    //剩余补空格
    for (int i = wklen; i < MONTH_TABLE_WIDTH; i++)
        buffer[1][i] = ' ';
    buffer[1][MONTH_TABLE_WIDTH] = '\0';

    //写日期行
    int begin = week_zeller(year, month); //该月起始星期

    int month_days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (is_leap(year))
        month_days[1] = 29;
    int total = month_days[month - 1];

    int day = 1;
    int weekday = begin;
    int row = 2;

    while (day <= total) 
    {
        //计算此日的列位置
        int col = weekday * CAL_CELL_WIDTH;

        //写入单元（4列宽）
        if (day < 10) 
        {
            buffer[row][col + 0] = day + '0';
            buffer[row][col + 1] = ' ';
            buffer[row][col + 2] = ' ';
            buffer[row][col + 3] = ' ';
        }
        else 
        {
            buffer[row][col + 0] = (day / 10) + '0';
            buffer[row][col + 1] = (day % 10) + '0';
            buffer[row][col + 2] = ' ';
            buffer[row][col + 3] = ' ';
        }
        
        if (weekday == 6)  //星期六换行
        {
            row++;
            weekday = 0;
        }
        else 
        {
            weekday++;
        }
        day++;
    }

    for (int r = 0; r < MAX_ROW_HEIGHT; r++) //所有行保证固定宽为28
    {
        buffer[r][MONTH_TABLE_WIDTH] = '\0';
    }
}

int calculate_weeks(int year, int month) //计算该月需要的日期行数
{
    int month_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (is_leap(year))
        month_days[1] = 29;

    int total_days = month_days[month - 1];

    int first_day_weekday = week_zeller(year, month);

    int total_cells = first_day_weekday + total_days;

    return (total_cells + 6) / 7; //向上取整得到周数
}

void print_year_synchronized(int num, int year)
{
    char month_buffer[MAX_ROW_HEIGHT][MONTH_TABLE_WIDTH + 1];
    char row_buffer[MAX_ROW_HEIGHT][MAX_TOTAL_ROW_WIDTH + 1];

    for (int start_month = 1; start_month <= 12; start_month += num) 
    {
        for (int r = 0; r < MAX_ROW_HEIGHT; r++) //初始化清空row_buffer
        {
            for (int c = 0; c < MAX_TOTAL_ROW_WIDTH; c++)
                row_buffer[r][c] = ' ';
            row_buffer[r][0] = '\0';
        }

        int end_month = start_month + num - 1;
        if (end_month > 12) end_month = 12;

        //计算当前组需要的最大行数
        int max_weeks_in_row = 0;
        for (int m = start_month; m <= end_month; m++) 
        {
            int current_weeks = calculate_weeks(year, m);
            if (current_weeks > max_weeks_in_row) 
            {
                max_weeks_in_row = current_weeks;
            }
        }
        int max_rows_to_print = max_weeks_in_row + 2; //总行数

        for (int m = start_month; m <= end_month; m++) 
        {

            //获取该月的8*28表
            draw_month_to_buffer(year, m, month_buffer);

            for (int r = 0; r < MAX_ROW_HEIGHT; r++) 
            {

                int cur_len = strlen(row_buffer[r]); //当前已拼接长度

                //非首月则加GAP_WIDTH个空格
                if (m > start_month) 
                {
                    for (int g = 0; g < GAP_WIDTH; g++)
                        row_buffer[r][cur_len + g] = ' ';
                    cur_len += GAP_WIDTH;
                }

                //追加月份的28个字符
                for (int c = 0; c < MONTH_TABLE_WIDTH; c++)
                    row_buffer[r][cur_len + c] = month_buffer[r][c];
                row_buffer[r][cur_len + MONTH_TABLE_WIDTH] = '\0';
            }
        }

        //打印这一行的所有 8 行
        for (int r = 0; r < max_rows_to_print; r++)
            cout << row_buffer[r] << endl;

		if (start_month + num <= 12)
            cout << endl;
    }
}

int main()
{
    int year;
    while (1) 
    {
        cout << "请输入年份[1900-2100]\n";
        cin >> year;
        if (!cin.fail() && year >= 1900 && year <= 2100) 
            break;
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
        }
    }

    int month_days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (is_leap(year)) 
        month_days[1] = 29;

    int num;
    while (1) 
    {
        cout << "请输入每行打印的月份数[1/2/3/4/6/12]\n";
        cin >> num;
        if (!cin.fail() &&(num == 1 || num == 2 || num == 3 || num == 4 || num == 6 || num == 12)) 
            break;
        else
        {
            cin.clear();
            cin.ignore(1024, '\n');
        }
    }

    cout << year << "年的日历:\n\n";

    print_year_synchronized(num, year);

    cout << "\n\n";
    return 0;
}
