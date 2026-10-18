/* 2451951 大数据 于沛可 */
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
const int ROWS = 10;
const int COLS = 26;
const int MINES = 50;
void initBoard(char board[ROWS + 2][COLS + 2])
{
	for (int i = 0; i < ROWS + 2; i++)
		for (int j = 0; j < COLS + 2; j++)
			board[i][j] = '0';
}

void addMines(char board[ROWS + 2][COLS + 2])
{
	srand((unsigned int)time(NULL));
	int added = 0;
	while (added < MINES)
	{
		int r = rand() % ROWS + 1;
		int c = rand() % COLS + 1;
		if (board[r][c] == '0')
		{
			board[r][c] = '*';
			added++;
		}
	}
}

void Calc(char board[ROWS + 2][COLS + 2])
{
	for(int i=1;i<=ROWS;i++)
		for (int j = 1; j <= COLS; j++)
		{
			if (board[i][j] == '0')
			{
				int count = 0;
				for (int kr = -1; kr <= 1; kr++)
					for (int kc = -1; kc <= 1; kc++)
					{
						if (kr == 0 && kc == 0)
							continue;
						if (board[i + kr][j + kc] == '*')
							count++;
					}
				board[i][j] = '0' + count;
			}
		}
}

void Print(char board[ROWS + 2][COLS + 2])
{
	for (int i = 1; i <= ROWS; i++)
	{
		for (int j = 1; j <= COLS; j++)
			cout << board[i][j] << " ";
		cout << endl;
	}


}

int main()
{
	char board[ROWS + 2][COLS + 2];
	initBoard(board);
	addMines(board);
	Calc(board);
	Print(board);
}