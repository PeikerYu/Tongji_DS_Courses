/* 2451951 大数据 于沛可 */

#include"mine_sweeper.h" 
using namespace std;

int main()
{
	  
	/* 这是一段用于验证cmd_console_tools.cpp版本是否正确的代码，判断正确的具体标准在作业文档中 */
	cct_showstr(10, 2, "请输出雪花的大小", COLOR_BLACK, COLOR_WHITE, 2); 
	cout << endl << endl;
	cct_showstr(10, 4, "╔═══汉诺塔═══╗", COLOR_BLACK, COLOR_WHITE, 1);
	cct_showstr(10, 5, "╔═══汉诺塔 ═══╗", COLOR_WHITE, COLOR_BLACK, 1);
	cct_showstr(10, 6, "╔═══H汉诺塔 ═══╗", COLOR_RED, COLOR_HYELLOW, 1);

	cct_showstr(10, 8, "**╔═╦═╗中", COLOR_CYAN, COLOR_YELLOW, 1);
	cct_showstr(10, 9, "中║测║试║**", COLOR_HBLUE, COLOR_HPINK, 1);
	cct_showstr(10, 10, "**╠═╬═╣**", COLOR_YELLOW, COLOR_HGREEN, 1);
	cct_showstr(10, 11, "中║ab║12║中", COLOR_HPINK, COLOR_HCYAN, 1);
	cct_showstr(10, 12, "**╚═╩═╝中", COLOR_GREEN, COLOR_HBLUE, 1);

	/* 本函数位于 mine_sweeper_tools.cpp 中 */
	to_be_continued("请确认上面的输出没有乱码/字符相互重叠现象，如果有，说明cmd_console_tools.cpp不对");

	//给出后续的正常内容
	while (1)
	{
		int choice = menu();
		if (choice == 0)
			break;
		else if (choice == 1)
		{
			fun1();
		}
		else if (choice == 2)
		{
			fun2();
		}
		else if (choice == 3)
		{
			fun3();
		}
		else if (choice == 4)
		{
			fun4();
		}
		else if (choice == 5)
		{
			fun5();
		}
		else if (choice == 6)
		{
			fun6();
		}
		else if (choice == 7)
		{
			fun7();
		}
		else if (choice == 8)
		{
			fun8();
		}
		else
			fun9();
	}
	return 0;
} 