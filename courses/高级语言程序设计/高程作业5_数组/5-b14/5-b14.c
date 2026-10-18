/* 2451951 大数据 于沛可 */
/* 2450368 仇智  2450388 蒲天蓝  2453816 温玳宁  2453748 雷志成  2451666 侯翔译 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ROWS 10
#define COLS 26

int main()
{
	char board[ROWS + 2][COLS + 2];
	int mine_count = 0;
	char ch;
	for (int i = 1; i <= ROWS; i++)
	{
		for (int j = 1; j <= COLS; j++)
		{
			scanf(" %c", &ch); //跳过前导空格
			board[i][j] = ch;
			if (ch == '*')
				mine_count++;
		}
	}
	if (mine_count != 50)
	{
		printf("错误1\n");
		return 0;
	}
	for (int i = 1; i <= ROWS; i++)
	{
		for (int j = 1; j <= COLS; j++)
		{
			if (board[i][j] != '*')
			{
				int count = 0;
				int kr, kc;
				for (kr = -1; kr <= 1; kr++)
				{
					for (kc = -1; kc <= 1; kc++)
					{
						if (kr == 0 && kc == 0)
							continue;
						if (board[i + kr][j + kc] == '*')
							count++;
					}
				}
				if (count + '0' != board[i][j])
				{
					printf("错误2\n");
					return 0;
				}
			}
		}
	}
	printf("正确\n");
	return 0;
}