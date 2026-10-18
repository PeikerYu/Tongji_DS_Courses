/* 2451951 大数据 于沛可 */
#include"mine_sweeper.h"
using namespace std;
 
/***************************************************************************
  函数名称：initBoard
  功    能：初始化棋盘
  输入参数：char board[][MAX_COLS + 2] - 棋盘数组
           int rows, cols - 实际行列数
***************************************************************************/
void initBoard(char board[][MAX_COLS + 2], int rows, int cols)
{
    for (int i = 0; i <= rows + 1; i++)
        for (int j = 0; j <= cols + 1; j++)
            board[i][j] = '0';
}

/***************************************************************************
  函数名称：gameInit
  功    能：游戏初始化（选择等级、初始化棋盘）
  输入参数：rows, cols, mines - 通过引用返回等级参数
           display - 显示数组
           need_display_init - 是否需要初始化display为全X（默认true）
  返 回 值：选择的等级（1-3），0表示用户取消
***************************************************************************/
int gameInit(int& rows, int& cols, int& mines, char display[][MAX_COLS + 2], bool need_display_init = true)
{
    cct_cls();
    cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级（1\\2\\3）";
    char ch;
    int level;
    while (1)
    {
        ch = _getch();
        if (ch >= '1' && ch <= '3')
        {
            level = ch - '0';
            break;
        }
    }
    // 根据等级设置参数
    switch (level)
    {
    case 1:
        rows = LEVEL1_ROWS;
        cols = LEVEL1_COLS;
        mines = LEVEL1_MINES;
        break;
    case 2:
        rows = LEVEL2_ROWS;
        cols = LEVEL2_COLS;
        mines = LEVEL2_MINES;
        break;
    case 3:
        rows = LEVEL3_ROWS;
        cols = LEVEL3_COLS;
        mines = LEVEL3_MINES;
        break;
    }
    // 初始化显示数组为全X（如果需要）
    if (need_display_init)
    {
        for (int i = 0; i <= MAX_ROWS + 1; i++)
            for (int j = 0; j <= MAX_COLS + 1; j++)
                display[i][j] = 'X';
    }
    return level;
}

/***************************************************************************
  函数名称：inputCoordinate
  功    能：输入坐标（带回显和合法性检查）
  输入参数：rows, cols - 棋盘大小
           row_num, col_num - 通过引用返回坐标
           prompt - 提示信息
  返 回 值：true-输入成功，false-用户按q退出
***************************************************************************/
bool inputCoordinate(int rows, int cols, int& row_num, int& col_num, const char* prompt = "输入纵横坐标（如Gf、A1，按q退出）: ")
{
    // 只在有prompt时显示
    if (prompt && prompt[0] != '\0')
        cout << prompt;
    char row_ch, col_ch;
    bool row_set = false;  // 标记第一个字符是否已设置
    while (1)
    {
        row_ch = _getch();
        // 按q退出 - 清屏后返回
        if (row_ch == 'q' || row_ch == 'Q')
        {
            cout << endl;
            return false;
        }
        // 检查行号（必须大写A-P）
        if (row_ch < 'A' || row_ch > 'A' + rows - 1)
            continue;  // 不合法，直接忽略，不显示
        // 合法，回显并记录
        cout << row_ch;
        row_num = row_ch - 'A' + 1;
        row_set = true;
        break;  // 跳出循环，等待第二个字符
    }
    // 输入第二个字符
    while (1)
    {
        col_ch = _getch();
        // 检查列号
        bool valid = false;
        if (col_ch >= '1' && col_ch <= '9')
        {
            col_num = col_ch - '0';
            valid = (col_num <= cols);
        }
        else if (col_ch >= 'a' && col_ch <= 'z')
        {
            col_num = col_ch - 'a' + 10;
            valid = (col_num <= cols);
        }
        if (!valid)
            continue;  // 不合法，直接忽略，不需要删除第一个字符
        // 合法，回显
        cout << col_ch;
        return true;
    }
}

/***************************************************************************
  函数名称：addMines
  功    能：随机放置地雷
  输入参数：char board[][MAX_COLS + 2] - 棋盘数组
           int rows, cols - 实际行列数
           int mines - 地雷数量
           safe_row, safe_col - 安全区中心（默认-1表示无安全区）
***************************************************************************/
void addMines(char board[][MAX_COLS + 2], int rows, int cols, int mines, int safe_row = -1, int safe_col = -1)
{
    srand((unsigned int)time(NULL));
    int added = 0;
    bool has_safe_zone = (safe_row != -1 && safe_col != -1);
    while (added < mines)
    {
        int r = rand() % rows + 1;
        int c = rand() % cols + 1;
        // 如果需要安全区，检查是否在安全区内
        if (has_safe_zone)
        {
            bool in_safe_zone = false;
            for (int kr = -1; kr <= 1; kr++)
            {
                for (int kc = -1; kc <= 1; kc++)
                {
                    if (r == safe_row + kr && c == safe_col + kc)
                    {
                        in_safe_zone = true;
                        break;
                    }
                }
                if (in_safe_zone)
                    break;
            }
            // 在安全区内，跳过此次循环
            if (in_safe_zone)
                continue;
        }
        // 不在安全区或无安全区且该位置空闲，则放雷
        if (board[r][c] == '0')
        {
            board[r][c] = '*';
            added++;
        }
    }
}

/***************************************************************************
  函数名称：calcNumbers
  功    能：计算每个非雷格子周围的雷数
  输入参数：char board[][MAX_COLS + 2] - 棋盘数组
           int rows, cols - 实际行列数
***************************************************************************/
void calcNumbers(char board[][MAX_COLS + 2], int rows, int cols)
{
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= cols; j++)
        {
            if (board[i][j] == '0')
            {
                int count = 0;
                for (int kr = -1; kr <= 1; kr++)
                {
                    for (int kc = -1; kc <= 1; kc++)
                    {
                        if (kr == 0 && kc == 0)
                            continue;
                        if (board[i + kr][j + kc] == '*')
                            count++;
                    }
                }
                board[i][j] = '0' + count;
            }
        }
    }
}

/***************************************************************************
  函数名称：printBoard
  功    能：打印棋盘（带行列标）
  输入参数：char display[][MAX_COLS + 2] - 棋盘数组
           int rows, cols - 实际行列数
           bool use_highlight - 是否使用高亮
           char marked[][MAX_COLS + 2] - 标记数组（默认NULL）
  返 回 值：无
  说    明：标记的位置显示为红色的X
***************************************************************************/
void printBoard(char display[][MAX_COLS + 2], int rows, int cols, bool use_highlight = false, char marked[][MAX_COLS + 2] = NULL)
{
    // 打印列标题
    cout << "  |";
    for (int j = 1; j <= cols; j++)
    {
        if (j <= 9)
            cout << j << " ";
        else
            cout << (char)('a' + j - 10) << " ";
    }
    cout << endl;
    // 打印分隔线
    cout << "--+";
    for (int j = 1; j <= cols; j++)
        cout << "--";
    cout << endl;
    // 打印棋盘内容
    for (int i = 1; i <= rows; i++)
    {
        cout << (char)('A' + i - 1) << " |";
        for (int j = 1; j <= cols; j++)
        {
            char value = display[i][j];
            // 如果有标记且被标记
            if (marked != NULL && marked[i][j] == '1' && value == 'X')
            {
                cct_setcolor(COLOR_BLACK, COLOR_HRED);
                cout << "F";  // 标记显示为F
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                cout << " ";
            }
            // 如果需要高亮且已打开
            else if (use_highlight && value != 'X')
            {
                // 根据数字显示不同颜色
                int fg_color;
                if (value == '*')
                    fg_color = COLOR_RED;
                else if (value == '1')
                    fg_color = COLOR_BLUE;
                else if (value == '2')
                    fg_color = COLOR_GREEN;
                else if (value == '3')
                    fg_color = COLOR_CYAN;
                else if (value == '4')
                    fg_color = COLOR_HBLUE;
                else if (value == '5')
                    fg_color = COLOR_HRED;
                else if (value == '6')
                    fg_color = COLOR_HCYAN;
                else if (value == '7')
                    fg_color = COLOR_BLACK;
                else if (value == '8')
                    fg_color = COLOR_HWHITE;
                else
                    fg_color = COLOR_WHITE;
                cct_setcolor(COLOR_HYELLOW, fg_color);  // 黄底，彩色数字
                cout << value;
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                cout << " ";
            }
            else
            {
                cout << value << " ";
            }
        }
        cout << endl;
    }
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);  // 确保恢复
}

/***************************************************************************
  函数名称：openArea
  功    能：从指定位置展开所有相连的0区域（递归实现）
  输入参数：board - 内部真实数组
           display - 显示数组
           row, col - 当前位置
           rows, cols - 棋盘大小
  说    明：展开规则：
           如果当前位置是0，继续向8个方向递归
           如果当前位置是1-8，停止递归但要显示这个数字
           如果是雷或已打开，不处理
***************************************************************************/
void openArea(char board[][MAX_COLS + 2], char display[][MAX_COLS + 2], int row, int col, int rows, int cols)
{
    // 边界检查
    if (row < 1 || row > rows || col < 1 || col > cols)
        return;
    // 如果已经打开过了，直接返回
    if (display[row][col] != 'X')
        return;
    // 如果是雷，不处理
    if (board[row][col] == '*')
        return;
    // 打开当前位置（显示真实值）
    display[row][col] = board[row][col];
    // 如果当前位置是0，继续向8个方向展开
    if (board[row][col] == '0')
    {
        for (int kr = -1; kr <= 1; kr++)
        {
            for (int kc = -1; kc <= 1; kc++)
            {
                if (kr == 0 && kc == 0)  // 跳过自己
                    continue;
                // 递归展开
                openArea(board, display, row + kr, col + kc, rows, cols);
            }
        }
    }
}

/***************************************************************************
  函数名称：checkWin
  功    能：检查是否获胜（所有非雷格子都被打开）
  输入参数：board - 真实棋盘
           display - 显示棋盘
           rows, cols - 棋盘大小
  返 回 值：true-获胜，false-未获胜
***************************************************************************/
bool checkWin(char board[][MAX_COLS + 2], char display[][MAX_COLS + 2], int rows, int cols)
{
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= cols; j++)
        {
            // 如果是非雷格子但还没打开，则未获胜
            if (board[i][j] != '*' && display[i][j] == 'X')
                return false;
        }
    }
    return true;  // 所有非雷格子都打开了
}
 
void fun1()
{
    int rows, cols, mines;
    char display[MAX_ROWS + 2][MAX_COLS + 2];
    int level = gameInit(rows, cols, mines, display, false);
    cct_cls();
    cout << "等级为" << level << "：" << endl;
    cout << "内部数组：" << endl;
    char board[MAX_ROWS + 2][MAX_COLS + 2];
    initBoard(board, rows, cols);
    addMines(board, rows, cols, mines);
    calcNumbers(board, rows, cols);
    printBoard(board, rows, cols);
    cout << endl;
    to_be_continued(NULL);
}

void fun2()
{
    int rows, cols, mines;
    char display[MAX_ROWS + 2][MAX_COLS + 2];
    gameInit(rows, cols, mines, display);
    cct_cls();
    cout << "内部数组：" << endl;
    printBoard(display, rows, cols);
    cout << endl;
    int row_num, col_num;
    if (!inputCoordinate(rows, cols, row_num, col_num))
    {
        cct_cls();  // 退出前清屏
        return;
    }
    // 生成棋盘
    char board[MAX_ROWS + 2][MAX_COLS + 2];
    initBoard(board, rows, cols);
    addMines(board, rows, cols, mines, row_num, col_num);
    calcNumbers(board, rows, cols);
    // 展开区域
    openArea(board, display, row_num, col_num, rows, cols);
    cout << endl << endl;
    cout << "点开后的数组：" << endl;
    printBoard(display, rows, cols, true);
    cout << endl;
    to_be_continued(NULL);
}

void fun3()
{
    int rows, cols, mines;
    char display[MAX_ROWS + 2][MAX_COLS + 2];
    gameInit(rows, cols, mines, display);
    cct_cls();
    cout << "内部数组：" << endl;
    printBoard(display, rows, cols);
    cout << endl;
    // 输入初始位置 
    int row_num, col_num;
    if (!inputCoordinate(rows, cols, row_num, col_num))
    {
        cct_cls();  // 退出前清屏
        return;
    }
    // 生成棋盘
    char board[MAX_ROWS + 2][MAX_COLS + 2];
    initBoard(board, rows, cols);
    addMines(board, rows, cols, mines, row_num, col_num);
    calcNumbers(board, rows, cols);
    // 打开初始区域
    openArea(board, display, row_num, col_num, rows, cols);
    // 显示初始状态
    cout << endl;
    cout << "当前数组：" << endl;
    printBoard(display, rows, cols, true);
    cout << endl;
    // 循环游戏 
    while (1)
    {
        // 检查是否获胜
        if (checkWin(board, display, rows, cols))
        {
            cout << "当前数组：" << endl;
            printBoard(display, rows, cols, true);
            cout << endl;
            cout << "游戏成功" << endl;
            to_be_continued(NULL);
            return;
        }
        // 输入坐标
        if (!inputCoordinate(rows, cols, row_num, col_num))
        {
            cct_cls();  // 退出前清屏
            return;
        }
        cout << endl;  // 输入坐标后换行
        // 检查是否已打开
        if (display[row_num][col_num] != 'X')
        {
            cout << "该位置已打开，请重新输入" << endl;
            continue;
        }
        // 检查是否是雷
        if (board[row_num][col_num] == '*')
        {
            display[row_num][col_num] = '*';
            cout << "当前数组" << endl;
            printBoard(display, rows, cols, true);
            cout << endl;
            cout << "你输了，游戏结束" << endl;
            to_be_continued(NULL);
            return;
        }
        // 打开位置
        if (board[row_num][col_num] == '0')
        {
            openArea(board, display, row_num, col_num, rows, cols);
        }
        else
        {
            display[row_num][col_num] = board[row_num][col_num];
        }
        // 刷新显示
        cout << "当前数组：" << endl;
        printBoard(display, rows, cols, true);
        cout << endl;
    }
}

void fun4()
{
    int rows, cols, mines;
    char display[MAX_ROWS + 2][MAX_COLS + 2];
    char marked[MAX_ROWS + 2][MAX_COLS + 2];
    gameInit(rows, cols, mines, display);
    // 初始化标记数组
    for (int i = 0; i <= MAX_ROWS + 1; i++)
        for (int j = 0; j <= MAX_COLS + 1; j++)
            marked[i][j] = '0';
    cct_cls();
    cout << "内部数组：" << endl;
    printBoard(display, rows, cols, false, marked);
    cout << endl;
    int row_num, col_num;
    if (!inputCoordinate(rows, cols, row_num, col_num))
    {
        cct_cls();
        return;
    }
    long start_tick = (long)clock();
    char board[MAX_ROWS + 2][MAX_COLS + 2];
    initBoard(board, rows, cols);
    addMines(board, rows, cols, mines, row_num, col_num);
    calcNumbers(board, rows, cols);
    openArea(board, display, row_num, col_num, rows, cols);
    cout << endl;
    cout << "当前数组：" << endl;
    printBoard(display, rows, cols, true, marked);
    cout << endl;
    while (1)
    {
        // 检查获胜
        bool win = true;
        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= cols; j++)
            {
                if (board[i][j] != '*' && display[i][j] == 'X')
                {
                    win = false;
                    break;
                }
            }
            if (!win) break;
        }
        if (win)
        {
            struct GameTime gt = convertTime(start_tick);
            cout << "当前数组：" << endl;
            printBoard(display, rows, cols, true, marked);
            cout << endl;
            cout << "游戏成功，一共用时 ";
            printTime(gt);
            cout << "秒" << endl;
            to_be_continued(NULL);
            return;
        }
        cout << "输入纵横坐标（如Gf、A1，按q退出，&显示时间，@A3表示标记A3为雷，#A3表示取消A3标记）: ";
        char first_ch;
        // 内层循环：一直读取，直到是合法的第一个字符
        while (1)
        {
            first_ch = _getch();
            // q 退出
            if (first_ch == 'q' || first_ch == 'Q')
            {
                cout << endl;
                cct_cls();
                return;
            }
            if (first_ch == '&')
            {
                cout << "&" << endl;

                //查看时间
                struct GameTime gt = convertTime(start_tick);

                cout << "已用时：";
                printTime(gt);
                cout << " 秒" << endl;

                cout << "输入纵横坐标（如Gf、A1，按q退出，&显示时间，@A3表示标记A3为雷，#A3表示取消A3标记）: "; 
                continue;
            }
            // @ 标记
            if (first_ch == '@')
            {
                cout << "@";
                if (!inputCoordinate(rows, cols, row_num, col_num, ""))
                {
                    cct_cls();
                    return;
                }
                cout << endl;
                if (display[row_num][col_num] == 'X')
                {
                    marked[row_num][col_num] = '1';
                    cout << "当前数组：" << endl;
                    printBoard(display, rows, cols, true, marked);
                    cout << endl;
                }
                else
                {
                    cout << "该位置已打开，无法标记" << endl;
                }
                cout << "输入纵横坐标（如Gf、A1，按q退出，&显示时间，@A3表示标记A3为雷，#A3表示取消A3标记）: ";
                continue;  // 继续读取
            }
            // # 取消标记
            if (first_ch == '#')
            {
                cout << "#";
                if (!inputCoordinate(rows, cols, row_num, col_num, ""))
                {
                    cct_cls();
                    return;
                }
                cout << endl;
                if (marked[row_num][col_num] == '1')
                {
                    marked[row_num][col_num] = '0';
                    cout << "当前数组：" << endl;
                    printBoard(display, rows, cols, true, marked);
                    cout << endl;
                }
                else
                {
                    cout << "该位置未被标记" << endl;
                }
                cout << "输入纵横坐标（如Gf、A1，按q退出，&显示时间，@A3表示标记A3为雷，#A3表示取消A3标记）: ";
                continue;  // 继续读取
            }
            // 普通坐标输入
            if (first_ch >= 'A' && first_ch <= 'A' + rows - 1)
            {
                cout << first_ch;
                row_num = first_ch - 'A' + 1;
                break;  // 跳出内层循环，继续读取第二个字符
            }
        }
        // 读取第二个字符（列号）
        while (1)
        {
            char col_ch = _getch();
            bool valid = false;
            if (col_ch >= '1' && col_ch <= '9')
            {
                col_num = col_ch - '0';
                valid = (col_num <= cols);
            }
            else if (col_ch >= 'a' && col_ch <= 'z')
            {
                col_num = col_ch - 'a' + 10;
                valid = (col_num <= cols);
            }
            if (!valid)
                continue;
            cout << col_ch << endl;
            break;
        }
        // 检查是否已打开或被标记
        if (display[row_num][col_num] != 'X')
        {
            cout << "该位置已打开，请重新输入" << endl;
            continue;  // 回到外层循环，重新显示提示
        }
        if (marked[row_num][col_num] == '1')
        {
            cout << "该位置已被标记，请先取消标记" << endl;
            continue;  // 回到外层循环，重新显示提示
        }
        // 检查是否是雷
        if (board[row_num][col_num] == '*')
        {
            struct GameTime gt = convertTime(start_tick);
            display[row_num][col_num] = '*';
            cout << "当前数组：" << endl;
            printBoard(display, rows, cols, true, marked);
            cout << endl;
            cout << "你输了，游戏结束，一共用时 ";
            printTime(gt);
            cout << " 秒" << endl;
            to_be_continued(NULL);
            return;
        }
        // 打开位置
        if (board[row_num][col_num] == '0')
        {
            openArea(board, display, row_num, col_num, rows, cols);
        }
        else
        {
            display[row_num][col_num] = board[row_num][col_num];
        }
        cout << "当前数组：" << endl;
        printBoard(display, rows, cols, true, marked);
        cout << endl;
    }
} 