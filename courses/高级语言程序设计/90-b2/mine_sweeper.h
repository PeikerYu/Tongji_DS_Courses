/* 2451951 大数据 于沛可 */
#pragma once
#include<iostream>
#include"cmd_console_tools.h"
#include<conio.h>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;
// 定义等级常量
const int LEVEL1_ROWS = 9;
const int LEVEL1_COLS = 9;
const int LEVEL1_MINES = 10;

const int LEVEL2_ROWS = 16;
const int LEVEL2_COLS = 16;
const int LEVEL2_MINES = 40;

const int LEVEL3_ROWS = 16;
const int LEVEL3_COLS = 30;
const int LEVEL3_MINES = 99;
const int MAX_ROWS = 16;
const int MAX_COLS = 30;

void to_be_continued(const char* prompt);
int menu();
void fun1();
void fun2();
void fun3();
void fun4();
void fun5();
void fun6();
void fun7();
void fun8();
void fun9();

// base中基础函数
void initBoard(char board[][32], int rows, int cols);
int gameInit(int& rows, int& cols, int& mines, char display[][32], bool need_display_init);
bool inputCoordinate(int rows, int cols, int& row_num, int& col_num, const char* prompt);
void addMines(char board[][32], int rows, int cols, int mines, int safe_row, int safe_col);
void calcNumbers(char board[][32], int rows, int cols);
void printBoard(char display[][32], int rows, int cols, bool use_highlight, char marked[][32]);
void openArea(char board[][32], char display[][32], int row, int col, int rows, int cols);
bool checkWin(char board[][32], char display[][32], int rows, int cols);
 
// 图形函数
void drawFrame(int rows, int cols);
void showDataInFrame(char board[][32], int rows, int cols);
void getCellSize(int rows, int cols, int& cell_width, int& cell_height);
bool screenToGrid(int mx, int my, int rows, int cols, int& row, int& col);
void showMouseInfo(int row, int col, bool valid, int rows, int cols);
void highlightCell(int row, int col, int rows, int cols, int bg_color);
void showCellValue(int row, int col, char value, int rows, int cols);
void openAreaInFrame(char board[][32], char display[][32], int row, int col, int rows, int cols);
void prepareConsoleForBoard(int rows, int cols); 
 
// 定义时间结构体
struct GameTime
{
    int seconds;        // 整数秒
    int milliseconds;   // 毫秒部分
};

struct GameTime convertTime(long start_time);
void printTime(const struct GameTime t);
 
