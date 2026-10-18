/* 2451951 大数据 于沛可 */
#include"mine_sweeper.h"
using namespace std;

/***************************************************************************
  函数名称：getCellSize
  功    能：根据棋盘大小返回格子的宽度和高度
***************************************************************************/ 
void getCellSize(int rows, int cols, int& cell_width, int& cell_height)
{
    if (rows <= 9 && cols <= 9)  // 初级 9x9
    {
        cell_width = 8;
        cell_height = 3;
    }
    else if (rows <= 16 && cols <= 16)  // 中级 16x16
    {
        cell_width = 8;
        cell_height = 3;
    }
    else  // 高级 16x30
    {
        cell_width = 6;
        cell_height = 2;
    }
}

/***************************************************************************
  函数名称：drawFrame
  功    能：画出伪图形的边框框架
  说    明：统一使用两个═的宽度作为格子宽度
***************************************************************************/
void drawFrame(int rows, int cols)
{
    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);

    const int START_X = 4;
    const int START_Y = 3;

    // 画列标
    for (int j = 1; j <= cols; j++)
    {
        int x = START_X + 2 + (j - 1) * CELL_WIDTH + CELL_WIDTH / 2;
        cct_gotoxy(x-1, START_Y - 1);
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        if (j <= 26)
            cout << char('a' + j - 1);
        else
            cout << j-1;
    }

    // 画行标
    for (int i = 1; i <= rows; i++)
    {
        int y = START_Y + 1 + (i - 1) * (CELL_HEIGHT + 1) + CELL_HEIGHT / 2;
        cct_gotoxy(START_X - 2, y);
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cout << (char)('A' + i - 1);
    }

    //  画顶部边框 
    cct_showstr(START_X, START_Y, "╔", COLOR_WHITE, COLOR_BLACK);

    for (int j = 0; j < cols; j++)
    {
        if (j == 0)
            cct_showstr(START_X + 2 + j * CELL_WIDTH, START_Y, "═", COLOR_WHITE, COLOR_BLACK, CELL_WIDTH / 2 - 1);
        else
            cct_showstr(START_X + 2 + j * CELL_WIDTH - 2, START_Y, "═", COLOR_WHITE, COLOR_BLACK, CELL_WIDTH / 2);
    }

    cct_showstr(START_X + 2 + cols * CELL_WIDTH - 2, START_Y, "╗", COLOR_WHITE, COLOR_BLACK);

    // 覆盖顶部交叉点
    for (int j = 1; j < cols; j++)
    {
        cct_showstr(START_X + 2 + j * CELL_WIDTH - 2, START_Y, "╦", COLOR_WHITE, COLOR_BLACK);
    }

    // 画每一行
    for (int i = 0; i < rows; i++)
    {
        int y_start = START_Y + 1 + i * (CELL_HEIGHT + 1);

        // 填充格子背景
        for (int j = 0; j < cols; j++)
        {
            int cell_x = START_X + 2 + j * CELL_WIDTH;

            for (int h = 0; h < CELL_HEIGHT; h++)
            {
                if (j == 0)
                {
                    // 第一列：从边框║位置开始填充，填充 CELL_WIDTH
                    cct_showch(cell_x, y_start + h, ' ', COLOR_HYELLOW, COLOR_HYELLOW, CELL_WIDTH);
                }
                else if (j == cols - 1)
                {
                    // 最后一列：从 cell_x - 2 开始，填充 CELL_WIDTH
                    cct_showch(cell_x - 2, y_start + h, ' ', COLOR_HYELLOW, COLOR_HYELLOW, CELL_WIDTH);
                }
                else
                {
                    // 中间列：从 cell_x - 2 开始，填充 CELL_WIDTH
                    cct_showch(cell_x - 2, y_start + h, ' ', COLOR_HYELLOW, COLOR_HYELLOW, CELL_WIDTH);
                }
            }
        }

        // 画竖线（覆盖在黄色背景上）
        for (int h = 0; h < CELL_HEIGHT; h++)
        {
            int y = y_start + h;

            // 左边框
            cct_showstr(START_X, y, "║", COLOR_WHITE, COLOR_BLACK);

            // 中间竖线
            for (int j = 1; j < cols; j++)
            {
                cct_showstr(START_X + 2 + j * CELL_WIDTH - 2, y, "║", COLOR_WHITE, COLOR_BLACK);
            }

            // 右边框
            cct_showstr(START_X + 2 + cols * CELL_WIDTH - 2, y, "║", COLOR_WHITE, COLOR_BLACK);
        }

        // 画横线分隔
        if (i < rows - 1)
        {
            int y_line = y_start + CELL_HEIGHT;

            cct_showstr(START_X, y_line, "╠", COLOR_WHITE, COLOR_BLACK);

            for (int j = 0; j < cols; j++)
            {
                if (j == 0)
                    cct_showstr(START_X + 2 + j * CELL_WIDTH, y_line, "═", COLOR_WHITE, COLOR_BLACK, CELL_WIDTH / 2 - 1);
                else
                    cct_showstr(START_X + 2 + j * CELL_WIDTH - 2, y_line, "═", COLOR_WHITE, COLOR_BLACK, CELL_WIDTH / 2);
            }

            cct_showstr(START_X + 2 + cols * CELL_WIDTH - 2, y_line, "╣", COLOR_WHITE, COLOR_BLACK);

            // 覆盖交叉点
            for (int j = 1; j < cols; j++)
            {
                cct_showstr(START_X + 2 + j * CELL_WIDTH - 2, y_line, "╬", COLOR_WHITE, COLOR_BLACK);
            }
        }
    }

    //画底部边框
    int bottom_y = START_Y + 1 + rows * (CELL_HEIGHT + 1) - 1;

    cct_showstr(START_X, bottom_y, "╚", COLOR_WHITE, COLOR_BLACK);

    for (int j = 0; j < cols; j++)
    {
        if (j == 0)
            cct_showstr(START_X + 2 + j * CELL_WIDTH, bottom_y, "═", COLOR_WHITE, COLOR_BLACK, CELL_WIDTH / 2 - 1);
        else
            cct_showstr(START_X + 2 + j * CELL_WIDTH - 2, bottom_y, "═", COLOR_WHITE, COLOR_BLACK, CELL_WIDTH / 2);
    }

    cct_showstr(START_X + 2 + cols * CELL_WIDTH - 2, bottom_y, "╝", COLOR_WHITE, COLOR_BLACK);

    // 覆盖底部交叉点
    for (int j = 1; j < cols; j++)
    {
        cct_showstr(START_X + 2 + j * CELL_WIDTH - 2, bottom_y, "╩", COLOR_WHITE, COLOR_BLACK);
    }
}

/***************************************************************************
  函数名称：showDataInFrame
  功    能：在框架中显示内部数据
***************************************************************************/
void showDataInFrame(char board[][32], int rows, int cols)
{
    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);

    const int START_X = 4;
    const int START_Y = 3;

    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= cols; j++)
        {
            if (board[i][j] == '0')
                continue;

            int x = START_X + 2 + (j - 1) * CELL_WIDTH + CELL_WIDTH / 2;
            int y = START_Y + 1 + (i - 1) * (CELL_HEIGHT + 1) + CELL_HEIGHT / 2;

            char value = board[i][j];
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
                fg_color = COLOR_BLACK;

            cct_showch(x, y, value, COLOR_HWHITE, fg_color);
        }
    }
}

/***************************************************************************
  函数名称：fun5
  功    能：子题目5 - 画框架并显示内部数据
***************************************************************************/
void fun5()
{
    int rows, cols, mines;
    char display[MAX_ROWS + 2][MAX_COLS + 2];
    int level = gameInit(rows, cols, mines, display, false);

    cct_cls();
    cout << "等级为" << level << "：" << endl;
    char board[18][32];
    initBoard(board, rows, cols);
    addMines(board, rows, cols, mines, -1, -1);
    calcNumbers(board, rows, cols);
    drawFrame(rows, cols);
    showDataInFrame(board, rows, cols);

    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);
    const int START_Y = 3;
    int bottom_y = START_Y + 1 + rows * (CELL_HEIGHT + 1) + 2;

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_gotoxy(0, bottom_y);
    to_be_continued(NULL);
}

/***************************************************************************
  函数名称：screenToGrid
  功    能：将屏幕坐标转换为棋盘坐标
***************************************************************************/
bool screenToGrid(int mx, int my, int rows, int cols, int& row, int& col)
{
    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);

    const int START_X = 4;
    const int START_Y = 3;

    int offset_x = mx - (START_X + 2);
    int offset_y = my - (START_Y + 1);

    if (offset_x < 0 || offset_y < 0)
        return false;

    int grid_x = offset_x / CELL_WIDTH;
    int grid_y = offset_y / (CELL_HEIGHT + 1);

    if (grid_x >= cols || grid_y >= rows)
        return false;

    int in_cell_y = offset_y % (CELL_HEIGHT + 1);
    if (in_cell_y >= CELL_HEIGHT)
        return false;

    col = grid_x + 1;
    row = grid_y + 1;

    return true;
}

void printCoordLabel(int r, int c) 
{
    // 打印行标 
    cout << (char)('A' + r - 1) << "行";

    // 打印列标 
    if (c <= 26)
        cout << (char)('a' + c - 1);
    else 
        cout << c - 1; 
    cout << "列";
}

/***************************************************************************
  函数名称：showMouseInfo
  功    能：在框架下方显示鼠标位置信息
***************************************************************************/
void showMouseInfo(int row, int col, bool valid, int rows, int cols)
{
    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);

    const int START_Y = 3;
    int info_y = START_Y + 1 + rows * (CELL_HEIGHT + 1) + 2;

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_gotoxy(0, info_y);

    if (valid)
    {
        cout << "[当前鼠标] ";
        cout << (char)('A' + row - 1) << "行";

        if (col <= 26)
            cout << (char)('a' + col - 1);
        else
            cout << (col - 1);

        cout << "列                              ";
    }
    else
    {
        cout << "[当前鼠标] 位置非法                              ";
    }
}

void prepareConsoleForBoard(int rows, int cols)
{
    cct_setfontsize("新宋体", 16, 8);
    const int FIXED_WIDTH = 200;  // 足够宽，防止高级模式下右侧被切断
    const int FIXED_HEIGHT = 80;  // 足够高，防止底部提示信息看不见
    cct_setconsoleborder(FIXED_WIDTH, FIXED_HEIGHT, FIXED_WIDTH, FIXED_HEIGHT);
}

/***************************************************************************
  函数名称：fun6
  功    能：子题目6 - 检测鼠标位置和左键点击
***************************************************************************/
void fun6()
{
    int rows, cols, mines;
    char display[MAX_ROWS + 2][MAX_COLS + 2];
    int level = gameInit(rows, cols, mines, display, false);
    prepareConsoleForBoard(rows, cols);
    cct_cls();

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "等级为" << level << "：" << endl;

    char board[18][32];
    initBoard(board, rows, cols);
    addMines(board, rows, cols, mines, -1, -1);
    calcNumbers(board, rows, cols);

    cct_setcursor(CCT_CURSOR_INVISIBLE);
    drawFrame(rows, cols);
    showDataInFrame(board, rows, cols);

    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);
    const int START_Y = 3;
    int info_y = START_Y + 1 + rows * (CELL_HEIGHT + 1) + 2;

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_gotoxy(0, info_y);
    cout << "[当前鼠标] 未移动";

    cct_gotoxy(0, info_y + 1);
    cout << "（提示：移动鼠标查看位置，单击左键结束）";

    cct_enable_mouse();

    int MX, MY, MAction, keycode1, keycode2;
    int last_row = -1, last_col = -1;

    while (1)
    {
        int ret = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);

        if (ret == CCT_MOUSE_EVENT)
        {
            if (MAction == MOUSE_LEFT_BUTTON_CLICK)
            {
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                cct_gotoxy(0, info_y + 2);
                cout << "检测到左键单击，结束";
                break;
            }
            else if (MAction == MOUSE_ONLY_MOVED)
            {
                int row, col;
                bool valid = screenToGrid(MX, MY, rows, cols, row, col);
                showMouseInfo(row, col, valid, rows, cols);
                last_row = row;
                last_col = col;
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT)
        {
            if (keycode1 == 27)
                break;
        }
    }

    cct_disable_mouse();
    cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);

    int bottom_y = info_y + 4;
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_gotoxy(0, bottom_y);

    to_be_continued(NULL);
}

void highlightCell(int row, int col, int rows, int cols, int bg_color)
{
    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);

    const int START_X = 4;
    const int START_Y = 3;

    int x_line = START_X + (col - 1) * CELL_WIDTH;
    int y_line = START_Y + (row - 1) * (CELL_HEIGHT + 1);

    int content_x = x_line + 2;      
    int content_y = y_line + 1;     
    int content_width = CELL_WIDTH - 2;

    for (int h = 0; h < CELL_HEIGHT; h++)
    {
        cct_showch(content_x, content_y + h, ' ', bg_color, bg_color, content_width);
    }
}
/***************************************************************************
  函数名称：showCellValue
  功    能：在格子中显示值
***************************************************************************/
void showCellValue(int row, int col, char value, int rows, int cols)
{
    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);

    const int START_X = 4;
    const int START_Y = 3;

    int x = START_X + 2 + (col - 1) * CELL_WIDTH + CELL_WIDTH / 2;
    int y = START_Y + 1 + (row - 1) * (CELL_HEIGHT + 1) + CELL_HEIGHT / 2;

    if (value == '0')
        return;

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
    else if (value == 'F')
        fg_color = COLOR_HRED;
    else
        fg_color = COLOR_BLACK;

    cct_showch(x, y, value, COLOR_HWHITE, fg_color);
}
 
/***************************************************************************
  函数名称：openAreaInFrame
  功    能：在伪图形界面中展开区域（递归）
***************************************************************************/
void openAreaInFrame(char board[][32], char display[][32], int row, int col, int rows, int cols)
{
    if (row < 1 || row > rows || col < 1 || col > cols)
        return;

    if (display[row][col] != 'X')
        return;

    if (board[row][col] == '*')
        return;

    display[row][col] = board[row][col];

    highlightCell(row, col, rows, cols, COLOR_HWHITE);
    showCellValue(row, col, board[row][col], rows, cols);

    if (board[row][col] == '0')
    {
        for (int kr = -1; kr <= 1; kr++)
        {
            for (int kc = -1; kc <= 1; kc++)
            {
                if (kr == 0 && kc == 0)
                    continue;
                openAreaInFrame(board, display, row + kr, col + kc, rows, cols);
            }
        }
    }
}


/***************************************************************************
  函数名称：fun7
  功    能：子题目7 - 鼠标点击一次，显示打开区域
***************************************************************************/
void fun7()
{
    int rows, cols, mines;
    char display[MAX_ROWS + 2][MAX_COLS + 2];
    int level = gameInit(rows, cols, mines, display, false);
    prepareConsoleForBoard(rows, cols);
    cct_cls();

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "等级为" << level << "：" << endl;

    for (int i = 0; i <= 17; i++)
        for (int j = 0; j <= 31; j++)
            display[i][j] = 'X';

    cct_setcursor(CCT_CURSOR_INVISIBLE);
    drawFrame(rows, cols);

    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);
    const int START_Y = 3;
    int info_y = START_Y + 1 + rows * (CELL_HEIGHT + 1) + 2;

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_gotoxy(0, info_y);
    cout << "请用鼠标左键选择一个位置作为起始位置";

    cct_enable_mouse();

    int MX, MY, MAction, keycode1, keycode2;
    int row_num = -1, col_num = -1;

    while (1)
    {
        int ret = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);

        if (ret == CCT_MOUSE_EVENT)
        {
            if (MAction == MOUSE_ONLY_MOVED)
            {
                int row, col;
                bool valid = screenToGrid(MX, MY, rows, cols, row, col);
                showMouseInfo(row, col, valid, rows, cols);
            }
            else if (MAction == MOUSE_LEFT_BUTTON_CLICK)
            {
                int row, col;
                bool valid = screenToGrid(MX, MY, rows, cols, row, col);

                if (valid)
                {
                    row_num = row;
                    col_num = col;
                    break;
                }
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT)
        {
            if (keycode1 == 27)
            {
                cct_disable_mouse();
                cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                cct_gotoxy(0, info_y + 4);
                to_be_continued(NULL);
                return;
            }
        }
    }

    char board[18][32];
    initBoard(board, rows, cols);
    addMines(board, rows, cols, mines, row_num, col_num);
    calcNumbers(board, rows, cols);

    openAreaInFrame(board, display, row_num, col_num, rows, cols);

    cct_disable_mouse();
    cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_gotoxy(0, info_y + 4);
    to_be_continued(NULL);
}

/***************************************************************************
  函数名称：fun8
  功    能：子题目8 - 伪图形化游戏基础版
***************************************************************************/
void fun8()
{
    int rows, cols, mines;
    char display[MAX_ROWS + 2][MAX_COLS + 2];
    char marked[MAX_ROWS + 2][MAX_COLS + 2];

    int level = gameInit(rows, cols, mines, display, true);
    prepareConsoleForBoard(rows, cols);
    cct_cls();

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "等级为" << level << "（左键打开，右键标记，ESC退出）" << endl;

    for (int i = 0; i <= MAX_ROWS + 1; i++)
    {
        for (int j = 0; j <= MAX_COLS + 1; j++)
        {
            display[i][j] = 'X';
            marked[i][j] = '0';
        }
    }

    drawFrame(rows, cols);
    cct_setcursor(CCT_CURSOR_INVISIBLE);
    cct_enable_mouse();

    int MX, MY, MAction, key1, key2;
    int first_row = -1, first_col = -1;
    int last_highlight_row = -1, last_highlight_col = -1;

    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);
    const int START_Y = 3;
    int info_y = START_Y + 1 + rows * (CELL_HEIGHT + 1) + 2;

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_gotoxy(0, info_y);
    cout << "（提示：左键打开格子，右键标记/取消，ESC退出）";

    // 等待首次点击
    while (1)
    {
        int ret = cct_read_keyboard_and_mouse(MX, MY, MAction, key1, key2);

        if (ret == CCT_MOUSE_EVENT)
        {
            if (MAction == MOUSE_ONLY_MOVED)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c))
                {
                    if (r != last_highlight_row || c != last_highlight_col)
                    {
                        if (last_highlight_row > 0 && last_highlight_col > 0)
                        {
                            if (display[last_highlight_row][last_highlight_col] == 'X')
                            {
                                if (marked[last_highlight_row][last_highlight_col] == '1')
                                {
                                    highlightCell(last_highlight_row, last_highlight_col,rows, cols, COLOR_HRED);
                                    showCellValue(last_highlight_row, last_highlight_col,'F', rows, cols);
                                }
                                else
                                    highlightCell(last_highlight_row, last_highlight_col,rows, cols, COLOR_HYELLOW);
                            }
                        }

                        if (display[r][c] == 'X')
                        {
                            if (marked[r][c] == '1')
                            {
                                highlightCell(r, c, rows, cols, COLOR_RED);
                                showCellValue(r, c, 'F', rows, cols);
                            }
                            else
                                highlightCell(r, c, rows, cols, COLOR_YELLOW);
                        }

                        last_highlight_row = r;
                        last_highlight_col = c;
                    }

                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                    cct_gotoxy(0, info_y + 1);
                    cout << "[当前鼠标] " << (char)('A' + r - 1) << "行";
                    if (c <= 9)
                        cout << c;
                    else
                        cout << (char)('a' + c - 10);
                    cout << "列          ";
                }
                else
                {
                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                    cct_gotoxy(0, info_y + 1);
                    cout << "[当前鼠标] 位置非法                              ";
                }
            }
            else if (MAction == MOUSE_LEFT_BUTTON_CLICK)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c))
                {
                    if (marked[r][c] == '1')
                        continue;

                    first_row = r;
                    first_col = c;
                    break;
                }
            }
            else if (MAction == MOUSE_RIGHT_BUTTON_CLICK)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c))
                {
                    if (display[r][c] == 'X')
                    {
                        if (marked[r][c] == '0')
                        {
                            marked[r][c] = '1';
                            highlightCell(r, c, rows, cols, COLOR_HRED);
                            showCellValue(r, c, 'F', rows, cols);
                        }
                        else
                        {
                            marked[r][c] = '0';
                            highlightCell(r, c, rows, cols, COLOR_HYELLOW);
                        }
                    }
                }
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT && key1 == 27)
        {
            cct_disable_mouse();
            cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            cct_gotoxy(0, info_y + 3);
            to_be_continued(NULL);
            return;
        }
    }

    char board[MAX_ROWS + 2][MAX_COLS + 2];
    initBoard(board, rows, cols);
    addMines(board, rows, cols, mines, first_row, first_col);
    calcNumbers(board, rows, cols);

    openAreaInFrame(board, display, first_row, first_col, rows, cols);

    // 游戏主循环
    while (1)
    {
        if (checkWin(board, display, rows, cols))
        {
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            cct_gotoxy(0, info_y + 2);
            cout << "恭喜你，扫雷成功！          ";
            break;
        }

        int ret = cct_read_keyboard_and_mouse(MX, MY, MAction, key1, key2);

        if (ret == CCT_MOUSE_EVENT)
        {
            if (MAction == MOUSE_ONLY_MOVED)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c))
                {
                    if (r != last_highlight_row || c != last_highlight_col)
                    {
                        if (last_highlight_row > 0 && last_highlight_col > 0)
                        {
                            if (display[last_highlight_row][last_highlight_col] == 'X')
                            {
                                if (marked[last_highlight_row][last_highlight_col] == '1')
                                {
                                    highlightCell(last_highlight_row, last_highlight_col,rows, cols, COLOR_HRED);
                                    showCellValue(last_highlight_row, last_highlight_col,'F', rows, cols);
                                }
                                else
                                    highlightCell(last_highlight_row, last_highlight_col,rows, cols, COLOR_HYELLOW);
                            }
                            else
                            {
                                highlightCell(last_highlight_row, last_highlight_col,rows, cols, COLOR_HWHITE);
                                showCellValue(last_highlight_row, last_highlight_col,display[last_highlight_row][last_highlight_col],rows, cols);
                            }
                        }

                        if (display[r][c] == 'X')
                        {
                            if (marked[r][c] == '1')
                            {
                                highlightCell(r, c, rows, cols, COLOR_RED);
                                showCellValue(r, c, 'F', rows, cols);
                            }
                            else
                                highlightCell(r, c, rows, cols, COLOR_YELLOW);
                        }

                        last_highlight_row = r;
                        last_highlight_col = c;
                    }

                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                    cct_gotoxy(0, info_y + 1);
                    cout << "[当前鼠标] ";
                    printCoordLabel(r, c);  
                    cout << "          ";
                }
                else
                {
                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                    cct_gotoxy(0, info_y + 1);
                    cout << "[当前鼠标] 位置非法                              ";
                }
            }
            else if (MAction == MOUSE_LEFT_BUTTON_CLICK)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c) && display[r][c] == 'X' && marked[r][c] != '1')
                {
                    if (board[r][c] == '*')
                    {
                        highlightCell(r, c, rows, cols, COLOR_HRED);
                        showCellValue(r, c, '*', rows, cols);
                        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                        cct_gotoxy(0, info_y + 2);
                        cout << "你踩到雷了，游戏失败！          ";
                        break;
                    }
                    openAreaInFrame(board, display, r, c, rows, cols);
                }
            }
            else if (MAction == MOUSE_RIGHT_BUTTON_CLICK)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c) && display[r][c] == 'X')
                {
                    if (marked[r][c] == '0')
                    {
                        marked[r][c] = '1';
                        highlightCell(r, c, rows, cols, COLOR_HRED);
                        showCellValue(r, c, 'F', rows, cols);
                    }
                    else
                    {
                        marked[r][c] = '0';
                        highlightCell(r, c, rows, cols, COLOR_HYELLOW);
                    }
                }
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT && key1 == 27)
        {
            break;
        }
    }

    cct_disable_mouse();
    cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_gotoxy(0, info_y + 4);
    to_be_continued(NULL);
}

/***************************************************************************
  函数名称：fun9
  功    能：子题目9 - 完整伪图形化扫雷游戏
***************************************************************************/
void fun9()
{
    int rows, cols, mines;
    char display[MAX_ROWS + 2][MAX_COLS + 2];
    char marked[MAX_ROWS + 2][MAX_COLS + 2]; 
    int marked_count = 0;
    long start_tick = 0;  
    bool game_started = false;
    int level = gameInit(rows, cols, mines, display, true);
    prepareConsoleForBoard(rows, cols);
    cct_cls();
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cout << "等级为" << level << "（左键打开，右键标记，空格显示时间，ESC退出）" << endl;
    for (int i = 0; i <= MAX_ROWS + 1; i++)
    {
        for (int j = 0; j <= MAX_COLS + 1; j++)
        {
            display[i][j] = 'X';
            marked[i][j] = '0';
        }
    }
    drawFrame(rows, cols);
    cct_setcursor(CCT_CURSOR_INVISIBLE);
    cct_enable_mouse();
    int MX, MY, MAction, key1, key2;
    int first_row = -1, first_col = -1;
    int last_highlight_row = -1, last_highlight_col = -1;
    int CELL_WIDTH, CELL_HEIGHT;
    getCellSize(rows, cols, CELL_WIDTH, CELL_HEIGHT);
    const int START_Y = 3;
    int info_y = START_Y + 1 + rows * (CELL_HEIGHT + 1) + 2;
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_gotoxy(0, info_y);
    cout << "剩余雷数：" << (mines - marked_count);
    cct_gotoxy(0, info_y + 1);
    cout << "[当前鼠标] 未移动";
    cct_gotoxy(0, info_y + 2);
    cout << "（提示：左键打开，右键标记，空格显示时间）";
    // 等待首次点击
    while (1)
    {
        int ret = cct_read_keyboard_and_mouse(MX, MY, MAction, key1, key2);
        if (ret == CCT_MOUSE_EVENT)
        {
            if (MAction == MOUSE_ONLY_MOVED)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c))
                {
                    if (r != last_highlight_row || c != last_highlight_col)
                    {
                        if (last_highlight_row > 0 && last_highlight_col > 0)
                        {
                            if (display[last_highlight_row][last_highlight_col] == 'X')
                            {
                                if (marked[last_highlight_row][last_highlight_col] == '1')
                                    highlightCell(last_highlight_row, last_highlight_col,rows, cols, COLOR_HRED);
                                else
                                    highlightCell(last_highlight_row, last_highlight_col,rows, cols, COLOR_HYELLOW);
                            }
                        }
                        if (display[r][c] == 'X')
                        {
                            if (marked[r][c] == '1')
                                highlightCell(r, c, rows, cols, COLOR_RED);
                            else
                                highlightCell(r, c, rows, cols, COLOR_YELLOW);
                        }
                        last_highlight_row = r;
                        last_highlight_col = c;
                    }
                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                    cct_gotoxy(0, info_y + 1);
                    cout << "[当前鼠标] ";
                    printCoordLabel(r, c);  
                    cout << "          ";
                }
                else
                {
                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                    cct_gotoxy(0, info_y + 1);
                    cout << "[当前鼠标] 位置非法                              ";
                }
            }
            else if (MAction == MOUSE_LEFT_BUTTON_CLICK)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c))
                {
                    first_row = r;
                    first_col = c;
                    start_tick = clock(); 
                    game_started = true;
                    break;
                }
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT && key1 == 27)
        {
            cct_disable_mouse();
            cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            cct_gotoxy(0, info_y + 4);
            to_be_continued(NULL);
            return;
        }
    }
    char board[MAX_ROWS + 2][MAX_COLS + 2];
    initBoard(board, rows, cols);
    addMines(board, rows, cols, mines, first_row, first_col);
    calcNumbers(board, rows, cols);
    openAreaInFrame(board, display, first_row, first_col, rows, cols);
    // 游戏主循环
    while (1)
    {
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
            if (!win)
                break;
        }
        if (win)
        {
            struct GameTime gt = convertTime(start_tick);     
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            cct_gotoxy(0, info_y + 3);
            cout << "游戏成功，一共用时 ";
            printTime(gt);
            cout << "秒" << endl;
            break;
        }
        int ret = cct_read_keyboard_and_mouse(MX, MY, MAction, key1, key2);
        if (ret == CCT_MOUSE_EVENT)
        {
            if (MAction == MOUSE_ONLY_MOVED)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c))
                {
                    if (r != last_highlight_row || c != last_highlight_col)
                    {
                        if (last_highlight_row > 0 && last_highlight_col > 0)
                        {
                            if (display[last_highlight_row][last_highlight_col] == 'X')
                            {
                                if (marked[last_highlight_row][last_highlight_col] == '1')
                                {
                                    highlightCell(last_highlight_row, last_highlight_col,rows, cols, COLOR_HRED);
                                    showCellValue(last_highlight_row, last_highlight_col,'F', rows, cols);
                                }
                                else
                                    highlightCell(last_highlight_row, last_highlight_col,rows, cols, COLOR_HYELLOW);
                            }
                            else
                            {
                                highlightCell(last_highlight_row, last_highlight_col,rows, cols, COLOR_HWHITE);
                                showCellValue(last_highlight_row, last_highlight_col,display[last_highlight_row][last_highlight_col],rows, cols);
                            }
                        }
                        if (display[r][c] == 'X')
                        {
                            if (marked[r][c] == '1')
                            {
                                highlightCell(r, c, rows, cols, COLOR_RED);
                                showCellValue(r, c, 'F', rows, cols);
                            }
                            else
                                highlightCell(r, c, rows, cols, COLOR_YELLOW);
                        }
                        last_highlight_row = r;
                        last_highlight_col = c;
                    }
                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                    cct_gotoxy(0, info_y + 1);
                    cout << "[当前鼠标] " << (char)('A' + r - 1) << "行";
                    if (c <= 9)
                        cout << c;
                    else
                        cout << (char)('a' + c - 10);
                    cout << "列          ";
                }
                else
                {
                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                    cct_gotoxy(0, info_y + 1);
                    cout << "[当前鼠标] 位置非法                              ";
                }
            }
            else if (MAction == MOUSE_LEFT_BUTTON_CLICK)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c) && display[r][c] == 'X' && marked[r][c] != '1')
                {
                    if (board[r][c] == '*')
                    {
                        struct GameTime gt = convertTime(start_tick);
                        highlightCell(r, c, rows, cols, COLOR_HRED);
                        showCellValue(r, c, '*', rows, cols);
                        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                        cct_gotoxy(0, info_y + 3);
                        cout << "你输了，游戏结束，一共用时 ";
                        printTime(gt);
                        cout << " 秒" << endl;
                        break;
                    }
                    openAreaInFrame(board, display, r, c, rows, cols);
                }
            }
            else if (MAction == MOUSE_RIGHT_BUTTON_CLICK)
            {
                int r, c;
                if (screenToGrid(MX, MY, rows, cols, r, c) && display[r][c] == 'X')
                {
                    if (marked[r][c] == '0')
                    {
                        marked[r][c] = '1';
                        marked_count++;
                        highlightCell(r, c, rows, cols, COLOR_HRED);
                        showCellValue(r, c, 'F', rows, cols);
                    }
                    else
                    {
                        marked[r][c] = '0';
                        marked_count--;
                        highlightCell(r, c, rows, cols, COLOR_HYELLOW);
                    }
                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                    cct_gotoxy(0, info_y);
                    cout << "剩余雷数：" << (mines - marked_count) << "  ";
                }
            }
        }
        else if (ret == CCT_KEYBOARD_EVENT)
        {
            if (key1 == ' ')
            {
                struct GameTime gt = convertTime(start_tick);
                cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                cct_gotoxy(0, info_y + 3);
                cout << "已用时：";
                printTime(gt);
                cout << " 秒" << endl;
            }
            else if (key1 == 27)
            {
                break;
            }
        }
    }
    cct_disable_mouse();
    cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    cct_gotoxy(0, info_y + 5);
    to_be_continued(NULL);
}