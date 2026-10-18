/* 2451951 大数据 于沛可 */

/* ----------------------------------------------------------------------------------
 
     本文件功能：
    1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数
     
     本文件要求：
    1、不允许定义外部全局变量（const及#define不在限制范围内）
    2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
    3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
    4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

#include<iostream>
#include<iomanip>
#include"hanoi.h"
#include<Windows.h>
#include<conio.h> 
using namespace std;
static int count_step = 0;
static int arr_A[10], arr_B[10], arr_C[10];
static int top_A = 0, top_B = 0, top_C = 0;  // 分别对应A B C柱

static int delay = 0; //移动延时

int input(char* src, char* dst, char* tmp) //输入函数
{
    int layer;
    while (1) //输入层数的循环判断
    {
        cout << "请输入汉诺塔的层数(1-10)\n";
        cin >> layer;
        if (!cin.good() || (cin.good() && (layer < 1 || layer>10)))
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

    char usr_src, usr_dst;
    while (1) //处理输入src循环
    {
        cout << "请输入起始柱(A-C)\n";
        cin >> usr_src;
        if (cin.good() && ((usr_src <= 'c' && usr_src >= 'a') || (usr_src <= 'C' && usr_src >= 'A')))
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
    if (usr_src <= 'c' && usr_src >= 'a') //将src转换成大写，方便后续处理
    {
        usr_src = usr_src + 'A' - 'a';
    }

    while (1) //处理输入dst循环
    {
        cout << "请输入目标柱(A-C)\n";
        cin >> usr_dst;
        if (cin.good() && (usr_dst <= 'c' && usr_dst >= 'a')) //将dst转换成大写，方便后续处理
        {
            usr_dst = usr_dst + 'A' - 'a';
        }
        if (cin.good() && (usr_dst <= 'C' && usr_dst >= 'A') && (usr_dst != usr_src))
        {
            cin.clear();
            cin.ignore(65536, '\n');
            break;
        }
        else if (usr_dst == usr_src)
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

    *src = usr_src;
    *dst = usr_dst;

    *tmp = 'A' + 'B' + 'C' - *dst - *src;

    return layer;
}


int move_plate(char src, char dst, int mode)  //返回移动的盘子号
{
    int X_A, Y_A, X_B, Y_B, X_C, Y_C;
    if (mode == 4)
    {
        X_A = MenuItem4_Start_X + Underpan_A_X_OFFSET;
        Y_A = MenuItem4_Start_Y + Underpan_A_Y_OFFSET;
        X_B = X_A + Underpan_Distance;
        Y_B = Y_A;
        X_C = X_B + Underpan_Distance;
        Y_C = Y_A;
    }
    else if (mode == 8)
    {
        X_A = MenuItem8_Start_X + Underpan_A_X_OFFSET;
        Y_A = MenuItem8_Start_Y + Underpan_A_Y_OFFSET;
        X_B = X_A + Underpan_Distance;
        Y_B = Y_A;
        X_C = X_B + Underpan_Distance;
        Y_C = Y_A;
    }

    if (mode == 4 || mode == 8)
    {
        // 只清除最上面一个盘子
        if (src == 'A' && top_A > 0)
        {
            cct_gotoxy(X_A - 1, Y_A - 2 - (top_A - 1)); // 定位到最上面盘子的位置
            cout << "  "; // 清除最上面盘子
        }
        else if (src == 'B' && top_B > 0)
        {
            cct_gotoxy(X_B - 1, Y_B - 2 - (top_B - 1)); // 定位到最上面盘子的位置
            cout << "  "; // 清除最上面盘子
        }
        else if (src == 'C' && top_C > 0)
        {
            cct_gotoxy(X_C - 1, Y_C - 2 - (top_C - 1)); // 定位到最上面盘子的位置
            cout << "  "; // 清除最上面盘子
        }
    }
    int plate;
    //从src出栈
    if (src == 'A')
        plate = arr_A[--top_A];
    else if (src == 'B')
        plate = arr_B[--top_B];
    else
        plate = arr_C[--top_C];
    // 入栈到dst
    if (dst == 'A')
        arr_A[top_A++] = plate;
    else if (dst == 'B')
        arr_B[top_B++] = plate;
    else
        arr_C[top_C++] = plate;
    count_step++;
    return plate;
}

void print_state_row() //横向打印三个柱子的状态
{
    int i;
    cout << "A:"; //打印A柱
    for (i = 0; i < top_A; i++)
        cout << setw(2) << arr_A[i];
    for (i = top_A; i < 10; i++)
        cout << "  ";
    cout << "B:"; //打印B柱
    for (i = 0; i < top_B; i++)
        cout << setw(2) << arr_B[i];
    for (i = top_B; i < 10; i++)
        cout << "  ";
    cout << " C:"; //打印C柱
    for (i = 0; i < top_C; i++)
        cout << setw(2) << arr_C[i];
    for (i = top_C; i < 10; i++)
        cout << "  ";
}

void show_row(int plate, char src, char dst) //横向显示每一步移动
{
    cout << "第" << setw(4) << count_step << " 步(" << setw(2) << plate << "# " << src << " -->" << dst << ")  ";
    print_state_row();
    cout << endl;
}

void set_delay(int mode) //设置延时等级
{
    int level;
    if (mode == 4)
    {
        while (1)
        {
            cout << "请输入移动速度(0-200：0-按回车单步演示 1-200:延时1-200ms)\n";
            cin >> level;
            if (!cin.good() || (cin.good() && (level > 200 || level < 0)))
            {
                cin.clear();
                cin.ignore(65536, '\n');
                continue;
            }
            else
            {
                if (level == 0)
                    delay = -1;
                else
                    delay = level;
                break;
            }
        }
    }
    if (mode == 7 || mode == 8 || mode == 9)
    {
        while (1)
        {
            cout << "请输入移动速度(0 - 20：0 - 按回车单步演示 1 - 20:延时1 - 20ms)\n";
            cin >> level;
            if (!cin.good() || (cin.good() && (level > 20 || level < 0)))
            {
                cin.clear();
                cin.ignore(65536, '\n');
                continue;
            }
            else
            {
                if (level == 0)
                    delay = -1;
                else
                    delay = level;
                break;
            }
        }
    }
}

void perform_delay(bool is_eight) //执行延时
{
    if (is_eight==1 && count_step > 7)
    {
        return;
    }
    if (delay == -1)
    {
        _getch();
    }
    else
    {
        Sleep(delay);
    }
}

void draw_hanoi(int mode, char src) //打印纵向汉诺塔
{
    int X_A, Y_A;
    if (mode == 4)
    {
        //打印初始底座
        X_A = MenuItem4_Start_X + Underpan_A_X_OFFSET;
        Y_A = MenuItem4_Start_Y + Underpan_A_Y_OFFSET;
    }
    else if (mode == 8)
    {
        X_A = MenuItem8_Start_X + Underpan_A_X_OFFSET;
        Y_A = MenuItem8_Start_Y + Underpan_A_Y_OFFSET;
    }
    int X_B = X_A + Underpan_Distance;
    int Y_B = Y_A;
    int X_C = X_B + Underpan_Distance;
    int Y_C = Y_A;

    cct_gotoxy(X_A, Y_A);
    cout << "A";

    cct_gotoxy(X_B, Y_B);
    cout << "B";

    cct_gotoxy(X_C, Y_A);
    cout << "C";
    cct_gotoxy(X_A - 2, Y_A - 1);
    cout << "===================================";

    //纵向打印ABC柱
    for (int i = 0; i < top_A; i++)
    {
        cct_gotoxy(X_A - 1, Y_A - 2 - i);
        cout << setw(2) << arr_A[i];
    }
    for (int i = 0; i < top_B; i++)
    {
        cct_gotoxy(X_B - 1, Y_B - 2 - i);
        cout << setw(2) << arr_B[i];
    }
    for (int i = 0; i < top_C; i++)
    {
        cct_gotoxy(X_C - 1, Y_C - 2 - i);
        cout << setw(2) << arr_C[i];
    }
}

void show_col(int plate, char src, char dst) //纵向显示每一步移动
{
    cct_gotoxy(MenuItem4_Start_X, MenuItem4_Start_Y);
    cout << "第" << setw(4) << count_step << " 步(" << setw(2) << plate << "# " << src << " -->" << dst << ")  ";
    print_state_row();
    cout << "                           ";
    draw_hanoi(4, src);
    perform_delay(0);
}

void reset_state() //初始化清空所有值
{
    top_A = top_B = top_C = 0;
}

void init_state(char src, int layer) //初始化栈
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

void move_disk_hdc(int plate, char src, char dst, int layer,int mode);

void move_and_show(char src, char dst, int plate, int mode, int layer) //根据模式选择，移动并打印
{
    if (mode == 8)
    {
        move_disk_hdc(plate, src, dst, layer,8);

        move_plate(src, dst, 8);
        //同步显示文字部分（横向打印）
        cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y);
        show_row(plate, src, dst);
        cout << "            ";  // 清除行尾残留

        // 显示纵向数组
        draw_hanoi(8, src);
    }
    else
    {
        if (mode == 1)
        {
            plate = move_plate(src, dst, 1);
            cout << plate << "# " << src << "--->" << dst << endl;
        }
        else if (mode == 2)
        {
            plate = move_plate(src, dst, 2);
			cout << "第" << setw(4) << count_step << " 步(" << setw(2) << plate << "# " << src << " -->" << dst << ")" << endl;
        }
        else if (mode == 3)
        {
            plate = move_plate(src, dst, 3);
            show_row(plate, src, dst);
        }
        else
        {
            plate = move_plate(src, dst, 4);
            show_col(plate, src, dst);
        }
    }
}

void draw_three_columns() //画立柱和底座
{
    int base_color = HDC_COLOR[MAX_LAYER + 1]; //底座和立柱的颜色
    //计算坐标：

    //计算底座和立柱的公共参数
    int base_width = 23 * HDC_Base_Width;   // 底座宽 = 23w
    int base_high = HDC_Base_High;          // 底座高 = h
    int column_w = HDC_Base_Width;          // 立柱宽 = w
    int column_h = 12 * HDC_Base_High;      // 立柱高 = 12h

    //A B C 三个底座左上角坐标
    int baseA_x = HDC_Start_X;
    int baseA_y = HDC_Start_Y;

    int baseB_x = baseA_x + HDC_Underpan_Distance + base_width;
    int baseB_y = baseA_y;

    int baseC_x = baseB_x + HDC_Underpan_Distance + base_width;
    int baseC_y = baseA_y;

    //A B C 三个立柱左上角坐标——放在各自底座的中间
    int colA_x = baseA_x + (base_width - column_w) / 2;
    int colA_y = baseA_y - column_h;

    int colB_x = baseB_x + (base_width - column_w) / 2;
    int colB_y = colA_y;

    int colC_x = baseC_x + (base_width - column_w) / 2;
    int colC_y = colA_y;

    //依次画三块底座
    hdc_rectangle(baseA_x, baseA_y, base_width, base_high, base_color);
    Sleep(HDC_Init_Delay);

    hdc_rectangle(baseB_x, baseB_y, base_width, base_high, base_color);
    Sleep(HDC_Init_Delay);

    hdc_rectangle(baseC_x, baseC_y, base_width, base_high, base_color);
    Sleep(HDC_Init_Delay);

    //再画三根立柱
    hdc_rectangle(colA_x, colA_y, column_w, column_h, base_color);
    Sleep(HDC_Init_Delay);

    hdc_rectangle(colB_x, colB_y, column_w, column_h, base_color);
    Sleep(HDC_Init_Delay);

    hdc_rectangle(colC_x, colC_y, column_w, column_h, base_color);
    Sleep(HDC_Init_Delay);
}

void draw_init_disk(int layer, char src) //在初始柱子src上画初始盘子
{
    int base_width = 23 * HDC_Base_Width;
    int base_high = HDC_Base_High;
    int base_x; //计算柱子底座左上角坐标
    if (src == 'A')
        base_x = HDC_Start_X;
    else if (src == 'B')
        base_x = HDC_Start_X + base_width + HDC_Underpan_Distance;
    else
        base_x = HDC_Start_X + 2 * (base_width + HDC_Underpan_Distance);
    int base_y = HDC_Start_Y;
    int center_x = base_x + base_width / 2; //柱子的中心位置
    //从下往上画盘子
    for (int i = 1; i <= layer; i++)
    {
        int disk = layer - i + 1;
        int disk_w = (2 * disk + 1) * HDC_Base_Width;
        int disk_x = center_x - disk_w / 2;
        int disk_y = base_y - i * base_high;
        int color = HDC_COLOR[disk];
        hdc_rectangle(disk_x, disk_y, disk_w, base_high, color);
        Sleep(HDC_Init_Delay);
    }
}

int get_base_x(char col) //计算某个柱子底座左上角的x坐标
{
    int base_width = 23 * HDC_Base_Width;
    if (col == 'A')
        return HDC_Start_X;
    else if (col == 'B')
        return HDC_Start_X + base_width + HDC_Underpan_Distance;
    else
        return HDC_Start_X + 2 * (base_width + HDC_Underpan_Distance);
}

void move_disk_hdc(int plate, char src, char dst, int layer,int mode)
{
    bool is_eight=0;
    if (mode == 8)
    {
        is_eight = 1;
    }
    if (delay == -1 && count_step < 7) 
    {
        _getch();
    }
    // 获取移动前的层数
    int cur_layer_src;
    if (src == 'A')
        cur_layer_src = top_A;
    else if (src == 'B')
        cur_layer_src = top_B;
    else
        cur_layer_src = top_C;

    int cur_layer_dst;
    if (dst == 'A')
        cur_layer_dst = top_A;
    else if (dst == 'B')
        cur_layer_dst = top_B;
    else
        cur_layer_dst = top_C;

    // 计算盘子参数
    int disk = plate;
    int disk_w = (2 * disk + 1) * HDC_Base_Width;
    int disk_h = HDC_Base_High;

    // 计算柱子中心位置
    int base_width = 23 * HDC_Base_Width;
    int src_base_x = get_base_x(src);
    int dst_base_x = get_base_x(dst);
    int src_center_x = src_base_x + base_width / 2;
    int dst_center_x = dst_base_x + base_width / 2;

    // 盘子当前位置
    int cur_x = src_center_x - disk_w / 2;
    int cur_y = HDC_Start_Y - cur_layer_src * disk_h;

    // 立柱顶部Y坐标
    int column_top_y = HDC_Start_Y - 12 * HDC_Base_High;

    //  向上移动
    while (cur_y > HDC_Top_Y)
    {
        // 画上方的新位置
        cur_y -= HDC_Step_Y;
        hdc_rectangle(cur_x, cur_y, disk_w, HDC_Step_Y, HDC_COLOR[disk]);
        // 擦除下方的旧位置
        hdc_rectangle(cur_x, cur_y + disk_h, disk_w, HDC_Step_Y, HDC_COLOR[0]);
        // 如果还在立柱范围内，需要恢复被擦除的立柱中间部分
        if (cur_y > column_top_y - disk_h)
        {
            int col_x = src_center_x - HDC_Base_Width / 2;
            int col_y = cur_y + disk_h;
            hdc_rectangle(col_x, col_y, HDC_Base_Width, HDC_Step_Y, HDC_COLOR[MAX_LAYER + 1]);
        }
        perform_delay(is_eight);
    }

    // 水平移动 
    int dst_x = dst_center_x - disk_w / 2;
    int step_x = (dst_x > cur_x ? HDC_Step_X : -HDC_Step_X);

    while (cur_x != dst_x)
    {
        if (step_x > 0)
        {
            // 向右移动：画右边的新strip
            hdc_rectangle(cur_x + disk_w, cur_y, HDC_Step_X, disk_h, HDC_COLOR[disk]);
            hdc_rectangle(cur_x, cur_y, HDC_Step_X, disk_h, HDC_COLOR[0]);
            cur_x += step_x;
        }
        else
        {
            // 向左移动：画左边的新strip
            hdc_rectangle(cur_x + step_x, cur_y, -step_x, disk_h, HDC_COLOR[disk]);
            cur_x += step_x;
            hdc_rectangle(cur_x + disk_w, cur_y, -step_x, disk_h, HDC_COLOR[0]);
        }
        perform_delay(is_eight);
    }

    // 向下移动 
    int dst_y = HDC_Start_Y - (cur_layer_dst + 1) * disk_h;
    int dst_column_top_y = HDC_Start_Y - 12 * HDC_Base_High;

    while (cur_y < dst_y)
    {
        // 画下方的新位置
        hdc_rectangle(cur_x, cur_y + disk_h, disk_w, HDC_Step_Y, HDC_COLOR[disk]);

        // 擦除上方的旧位置
        hdc_rectangle(cur_x, cur_y, disk_w, HDC_Step_Y, HDC_COLOR[0]);

        // 如果还在立柱范围内，需要恢复被擦除的立柱中间部分
        if (cur_y >= dst_column_top_y)
        {
            int col_x = dst_center_x - HDC_Base_Width / 2;
            int col_y = cur_y;
            hdc_rectangle(col_x, col_y, HDC_Base_Width, HDC_Step_Y, HDC_COLOR[MAX_LAYER + 1]);
        }
        cur_y += HDC_Step_Y;
        perform_delay(is_eight);
    }
}

/***************************************************************************
  函数名称：
  功    能：打印n层汉诺塔的移动顺序 ！！！！唯一的递归函数，其他的细节实现用参数！！！
            不能超过15行！！！！
  输入参数：int n：层数
            char src：起始柱
            char tmp：中间柱
            char dst：目标柱
  返 回 值：
  说    明：1、函数名、形参、返回类型均不准动
            2、本函数不允许出现任何形式的循环
***************************************************************************/
void hanoi(int n, char src, char tmp, char dst, int mode, int layer)
{
    if (n == 1)
    {
        move_and_show(src, dst, 1, mode, layer);
        return;
    }
    hanoi(n - 1, src, dst, tmp, mode, layer); //先将上面的n-1个从起始柱移动到中间柱
    move_and_show(src, dst, n, mode, layer); //将最下面的从起始柱移动到目标柱
    hanoi(n - 1, tmp, src, dst, mode, layer); //最后将上面的n-1个从中间柱移动到目标柱
}

void fun1()  //实现菜单1中的函数：1.基本解
{
    int layer;
    char src, dst, tmp;
    reset_state();
    layer = input(&src, &dst, &tmp);
    init_state(src, layer);
    count_step = 0;
    hanoi(layer, src, tmp, dst, 1, layer);
}

void fun2()  //实现菜单2中的函数：2.基本解(步数记录)
{
    int layer;
    char src, dst, tmp;
    reset_state();
    layer = input(&src, &dst, &tmp);
    init_state(src, layer);
    count_step = 0;
    hanoi(layer, src, tmp, dst, 2, layer);
}

void fun3()  //实现菜单3中的函数：3.内部数组显示(横向)
{
    int layer;
    char src, dst, tmp;
    reset_state();
    layer = input(&src, &dst, &tmp);
    init_state(src, layer);
    count_step = 0;
    hanoi(layer, src, tmp, dst, 3, layer);
}

void fun4() //实现菜单4中的函数：4.内部数组显示(纵向+横向)
{
    int layer;
    char src, dst, tmp;
    reset_state();
    layer = input(&src, &dst, &tmp);
    init_state(src, layer);
    count_step = 0;
    set_delay(4);
    cct_cls();
    cct_gotoxy(0, MenuItem4_Start_Y + Underpan_A_Y_OFFSET+20);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << layer << " 层，延时设置为 " << delay << " ms";
    cct_gotoxy(MenuItem4_Start_X, MenuItem4_Start_Y);
    cout << "初始: ";
    print_state_row();
    draw_hanoi(4, src);
    perform_delay(0);
    hanoi(layer, src, tmp, dst, 4, layer);
}

void fun5() //实现菜单5中的函数：5.图形解-预备-画三个圆柱
{
    cct_cls();
    cct_gotoxy(0, Status_Line_Y);
    hdc_init(HDC_COLOR[0], HDC_COLOR[MAX_LAYER + 1]); //创建画图环境（类似于canvas），第一个参数是画布颜色，第二个参数是默认的画笔颜色如果没有设置的话
    hdc_cls();
    draw_three_columns(); //画三个底座和立柱
}

void fun6() //实现菜单6中的函数：6.图形解-预备-在起始柱上画n个盘子
{
    int layer;
    char src, dst, tmp;
    reset_state();
    layer = input(&src, &dst, &tmp);
    init_state(src, layer);
    cct_cls();
    cct_gotoxy(0, MenuItem4_Start_Y + 5);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << layer << " 层" << endl;
    hdc_init(HDC_COLOR[0], HDC_COLOR[MAX_LAYER + 1]); //创建画图环境（类似于canvas），第一个参数是画布颜色，第二个参数是默认的画笔颜色如果没有设置的话
    hdc_cls();
    draw_three_columns(); //画三个底座和立柱
    draw_init_disk(layer, src);
    hdc_release(); // 图形句柄释放掉，图还是会留在窗口上
}

void fun7() //实现菜单7中的函数：7.图形解-预备-第一次移动
{
    int layer;
    char src, dst, tmp;
    reset_state();
    layer = input(&src, &dst, &tmp);
    init_state(src, layer);
    set_delay(7);
    cct_cls(); 
    cct_gotoxy(0, MenuItem8_Start_Y);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << layer << " 层" << endl;

    hdc_init(HDC_COLOR[0], HDC_COLOR[MAX_LAYER + 1], 1400, 900);
    hdc_cls();
    draw_three_columns();
    draw_init_disk(layer, src);

    char first_dst = (layer % 2 == 1) ? dst : tmp;
    move_disk_hdc(1, src, first_dst, layer,7);
    hdc_release();
}

void fun8() //实现菜单8中的函数：8.图形解-自动移动版本
{
    int layer;
    char src, dst, tmp;
    reset_state();
    layer = input(&src, &dst, &tmp);
    init_state(src, layer);
    set_delay(8);
    cct_cls();
    cct_gotoxy(0, MenuItem8_Start_Y + 3);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << layer << " 层，延时设置为 " << delay << "ms（前7步，后面自动变为0ms）";
    cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y);
    cout << "初始: ";
    print_state_row();
    draw_hanoi(8, src);
    hdc_init(HDC_COLOR[0], HDC_COLOR[MAX_LAYER + 1], 1400, 900);
    hdc_cls();
    draw_three_columns();
    draw_init_disk(layer, src);
    hanoi(layer, src, tmp, dst, 8, layer);
    hdc_release();
}

// 获取源柱顶部的盘子号（如果为空返回-1）
int get_top_plate(char col)
{
    if (col == 'A')
    {
        if (top_A == 0)
            return -1;
        return arr_A[top_A - 1];
    }
    else if (col == 'B')
    {
        if (top_B == 0)
            return -1;
        return arr_B[top_B - 1];
    }
    else
    {
        if (top_C == 0)
            return -1;
        return arr_C[top_C - 1];
    }
}

// 检查游戏是否结束
bool is_game_over(char dst, int layer)
{
    if (dst == 'A')
        return top_A == layer;
    else if (dst == 'B')
        return top_B == layer;
    else
        return top_C == layer;
}

// 检查移动是否合法（返回true/false）
bool is_valid_move(char src, char dst)
{
    // 获取源柱和目标柱顶部的盘子
    int src_plate = get_top_plate(src);
    int dst_plate = get_top_plate(dst);

    // 检查源柱是否为空
    if (src_plate == -1)
    {
        cct_gotoxy(0, MenuItem9_Start_Y + 4);
        cout << "源柱为空！                                              ";
        Sleep(1000);
        cct_gotoxy(0, MenuItem9_Start_Y + 4);
        cout << "                                                        ";
        return false;
    }

    // 检查是否违反"大盘不能压小盘"规则
    if (dst_plate != -1 && src_plate > dst_plate)
    {
        cct_gotoxy(0, MenuItem9_Start_Y + 4);
        cout << "大盘(" << src_plate << ")不能压在小盘(" << dst_plate << ")上！        ";
        Sleep(1000);
        cct_gotoxy(0, MenuItem9_Start_Y + 4);
        cout << "                                                        ";
        return false;
    }
    return true;
}
void fun9()
{
    int layer;
    char src, dst, tmp;
    reset_state();
    layer = input(&src, &dst, &tmp);
    init_state(src, layer);
    count_step = 0;
    set_delay(9);
    cct_cls();
    cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y);
    cout << "初始: ";
    print_state_row();
    draw_hanoi(8, src);
    hdc_init(HDC_COLOR[0], HDC_COLOR[MAX_LAYER + 1], 1400, 900);
    hdc_cls();
    draw_three_columns(); 
    draw_init_disk(layer, src);
    // 游戏主循环
    while (true)
    {
        char move_src, move_dst;
        // 清除提示区域
        cct_gotoxy(0, MenuItem9_Start_Y + 3);
        cout << "                                                                    ";
        cct_gotoxy(0, MenuItem9_Start_Y + 4);
        cout << "                                                                    ";
        // 显示输入提示
        cct_gotoxy(0, MenuItem9_Start_Y + 3);
        cout << "请输入移动(格式:AC表示A->C, Q-退出): ";
        // 读取输入
        char input[100];
        cin.getline(input, 100);
        // 处理退出
        if (cin.good() == 0)
        {
            cin.clear();
            continue;
        }
        if ((input[0] == 'Q' || input[0] == 'q') && input[1] == '\0')
        {
            cct_gotoxy(0, MenuItem9_Start_Y + 4);
            cout << "游戏退出。共移动了 " << count_step << " 步              ";
            Sleep(2000);
            break;
        }
        // 提取有效字符（忽略空格）
        int idx = 0;
        char chars[2] = { 0, 0 };
        for (int i = 0; input[i] != '\0' && idx < 2; i++)
        {
            if (input[i] != ' ' && input[i] != '\t')
            {
                chars[idx++] = input[i];
            }
        }
        // 检查输入长度
        if (idx < 2)
        {
            cct_gotoxy(0, MenuItem9_Start_Y + 4);
            cout << "输入格式错误！请输入两个字母，如: AC                      ";
            Sleep(1500);
            continue;
        }
        // 转换为大写
        move_src = (chars[0] >= 'a' && chars[0] <= 'z') ? chars[0] - 'a' + 'A' : chars[0];
        move_dst = (chars[1] >= 'a' && chars[1] <= 'z') ? chars[1] - 'a' + 'A' : chars[1];
        // 检查字母是否合法
        if (move_src < 'A' || move_src > 'C' || move_dst < 'A' || move_dst > 'C')
        {
            cct_gotoxy(0, MenuItem9_Start_Y + 4);
            cout << "输入的字母必须是A-C！                                   ";
            Sleep(1500);
            continue;
        }
        // 检查源柱和目标柱是否相同
        if (move_src == move_dst)
        {
            cct_gotoxy(0, MenuItem9_Start_Y + 4);
            cout << "源柱和目标柱不能相同！                                  ";
            Sleep(1500);
            continue;
        }
        // 检查移动是否合法
        if (!is_valid_move(move_src, move_dst))
        {
            continue;  // 非法移动，重新输入
        }
        // 获取要移动的盘子号
        int plate = get_top_plate(move_src);
        // 执行移动（图形动画 + 数组更新）
        move_disk_hdc(plate, move_src, move_dst, layer,9);
        move_plate(move_src, move_dst, 8);
        // 更新文字显示
        cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y);
        show_row(plate, move_src, move_dst);
        cout << "            ";
        draw_hanoi(8, src);
        // 检查是否完成
        if (is_game_over(dst, layer))
        {
            cct_gotoxy(0, MenuItem9_Start_Y + 3);
            cout << "                                                                ";
            cct_gotoxy(0, MenuItem9_Start_Y + 4);
            cout << "游戏完成！共 " << count_step << " 步";
            Sleep(3000);
            break;
        }
    }
    // 释放图形资源
    hdc_release();
}
