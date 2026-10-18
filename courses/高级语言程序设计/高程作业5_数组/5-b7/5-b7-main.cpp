/* 2451951 大数据 于沛可 */
#include <iostream>
#include <iomanip>
#include <conio.h>
#include "5-b7.h"
#include <Windows.h>
using namespace std;

const int X_A = 20;
const int X_B = 30;
const int X_C = 40; // A B C柱子的x中心坐标
const int BASE_Y = 15; // 底部y坐标

static int delay = 0; // 移动延时
static bool show = 0; // 是否显示内部数组值
int count_num = 0;
int arr_A[10], arr_B[10], arr_C[10];
int top_A = 0, top_B = 0, top_C = 0;  // 分别对应A B C柱

void set_delay() // 设置延时等级
{
    int level;
    while (1)
    {
        cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)\n";
        cin >> level;
        if (!cin.good() || (cin.good() && (level > 5 || level < 0)))
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        else
        {
            if (level == 0)
                delay = -1;
            else if (level == 1)
                delay = 1000;
            else if (level == 2)
                delay = 500;
            else if (level == 3)
                delay = 200;
            else if (level == 4)
                delay = 50;
            else
                delay = 10;
            break;
        }
    }
}

void perform_delay() // 执行延时
{
    if (delay == -1)
    {
        _getch();
    }
    else
    {
        Sleep(delay);
    }
}

void draw_hanoi() // 打印纵向汉诺塔
{
    // 打印初始底座
    cct_gotoxy(10, BASE_Y + 1);
    cout << "=========================================";
    cct_gotoxy(X_A, BASE_Y + 2);
    cout << "A";
    cct_gotoxy(X_B, BASE_Y + 2);
    cout << "B";
    cct_gotoxy(X_C, BASE_Y + 2);
    cout << "C";

    // 只更新柱子的内容，而不是每次都清空
    // 纵向打印ABC柱
    for (int i = 0; i < top_A; i++)
    {
        cct_gotoxy(X_A - 1, BASE_Y - 1 - i);
        cout << setw(2) << arr_A[i];
    }
    for (int i = 0; i < top_B; i++)
    {
        cct_gotoxy(X_B - 1, BASE_Y - 1 - i);
        cout << setw(2) << arr_B[i];
    }
    for (int i = 0; i < top_C; i++)
    {
        cct_gotoxy(X_C - 1, BASE_Y - 1 - i);
        cout << setw(2) << arr_C[i];
    }
}

void print_internal_state() // 打印内部数组值
{
    if (show == 1)
    {
        cout << "A:";
        for (int i = 0; i < top_A; i++)
            cout << setw(2) << arr_A[i];
        for (int i = top_A; i < 10; i++)
            cout << " ";
        cout << "B:";
        for (int i = 0; i < top_B; i++)
            cout << setw(2) << arr_B[i];
        for (int i = top_B; i < 10; i++)
            cout << " ";
        cout << "C:";
        for (int i = 0; i < top_C; i++)
            cout << setw(2) << arr_C[i];
        for (int i = top_C; i < 10; i++)
            cout << " ";
    }
    else
        return;
}

void move_plate(char src, char dst)
{
    int plate;

    // 清除源柱上最上面的盘子
    if (src == 'A') {
        // 清除 A 柱上最上面的盘子
        cct_gotoxy(X_A - 1, BASE_Y - 1 - (top_A - 1));
        cout << "  ";  // 清除
        plate = arr_A[--top_A];  // 取出最上面的盘子
    }
    else if (src == 'B') {
        // 清除 B 柱上最上面的盘子
        cct_gotoxy(X_B - 1, BASE_Y - 1 - (top_B - 1));
        cout << "  ";  // 清除
        plate = arr_B[--top_B];  // 取出最上面的盘子
    }
    else {
        // 清除 C 柱上最上面的盘子
        cct_gotoxy(X_C - 1, BASE_Y - 1 - (top_C - 1));
        cout << "  ";  // 清除
        plate = arr_C[--top_C];  // 取出最上面的盘子
    }

    // 将盘子放入目标柱
    if (dst == 'A')
        arr_A[top_A++] = plate;
    else if (dst == 'B')
        arr_B[top_B++] = plate;
    else
        arr_C[top_C++] = plate;

    count_num++;
    draw_hanoi();  // 更新绘制
    cct_gotoxy(0, BASE_Y + 5);
    cout << "第" << setw(4) << count_num << "步(" << setw(2) << plate << "# ):" << src << "-->" << dst;
    cout << "     ";
    print_internal_state();
    perform_delay();
}

// 汉诺塔递归函数
void hanoi(int n, char src, char tmp, char dst)
{
    if (n == 1)
    {
        move_plate(src, dst);
        return;
    }

    hanoi(n - 1, src, dst, tmp);  // 将上面n-1个从起始柱移到中间柱
    move_plate(src, dst);          // 将最大的盘子从起始柱移到目标柱
    hanoi(n - 1, tmp, src, dst);  // 将n-1个从中间柱移到目标柱
}

void init_state(char src, int layer) // 初始化栈
{
    int i;
    if (src == 'A')
    {
        for (i = layer; i >= 1; i--)
            arr_A[top_A++] = i;
    }
    else if (src == 'B')
    {
        for (i = layer; i >= 1; i--)
            arr_B[top_B++] = i;
    }
    else
    {
        for (i = layer; i >= 1; i--)
            arr_C[top_C++] = i;
    }
}

int main()
{
    int layer;
    while (1) // 输入层数的循环判断
    {
        cout << "请输入汉诺塔的层数(1-10)\n";
        cin >> layer;
        if (!cin.good() || (cin.good() && (layer < 1 || layer > 10)))
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
            break;
        }
    }
    char src, dst;
    while (1) // 处理输入src循环
    {
        cout << "请输入起始柱(A-C)\n";
        cin >> src;
        if (cin.good() && ((src <= 'c' && src >= 'a') || (src <= 'C' && src >= 'A')))
        {
            cin.clear();
            cin.ignore(65536, '\n');
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
    }
    if (src <= 'c' && src >= 'a') // 将src转换成大写，方便后续处理
    {
        src = src + 'A' - 'a';
    }
    while (1) // 处理输入dst循环
    {
        cout << "请输入目标柱(A-C)\n";
        cin >> dst;
        if (cin.good() && (dst <= 'c' && dst >= 'a')) // 将dst转换成大写，方便后续处理
        {
            dst = dst + 'A' - 'a';
        }
        if (cin.good() && (dst <= 'C' && dst >= 'A') && (dst != src))
        {
            cin.clear();
            cin.ignore(65536, '\n');
            break;
        }
        else if (dst == src)
        {
            cout << "目标柱(A)不能与起始柱(A)相同\n";
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
    }
    set_delay();
    int show_flag;
    while (1)
    {
        cout << "请输入是否显示内部数组值(0-不显示 1-显示)\n";
        cin >> show_flag;
        if (cin.good() && (show_flag == 0 || show_flag == 1))
        {
            cin.clear();
            cin.ignore(65536, '\n');
            show = (show_flag == 1); // 设置是否显示
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
    }
    cct_cls();
    char tmp = 'A' + 'B' + 'C' - src - dst;
    init_state(src, layer);
    if (show == 1)
        cout << "从" << src << "移动到" << dst << "，共" << layer << "层，延时设置为" << (delay == -1 ? 0 : delay) << "，显示内部数组值";
    else
        cout << "从" << src << "移动到" << dst << "，共" << layer << "层，延时设置为" << (delay == -1 ? 0 : delay) << "，不显示内部数组值";
    draw_hanoi();
    cct_gotoxy(0, BASE_Y + 5);
    cout << "初始:                ";
    print_internal_state();
    perform_delay();
    hanoi(layer, src, tmp, dst);
    return 0;
}
