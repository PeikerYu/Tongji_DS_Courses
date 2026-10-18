/* 2451951 大数据 于沛可 */
#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

/* -----------------------------------------------------------------------------------
		允许   ：1、按需增加一个或多个函数（包括递归函数），但是所有增加的函数中不允许任何形式的循环
				 2、定义符号常量
				 3、定义const型变量

		不允许 ：1、定义全局变量
				 2、除print_tower之外的其他函数中不允许定义静态局部变量
   ----------------------------------------------------------------------------------- */
/*题目分析：
* 每行由三部分组成：前导空格+左半部分字母+右半部分字母
* 
* 
* 
* 
*/
void before_print(int count) //缩进函数：根据空格数打印空格
{
	if (count == 0)
		return; 
	else
	{
		cout << ' ';
		before_print(count - 1);
	}
}

void row_print(char curr_ch) //打印当前行
{
	if (curr_ch == 'A')
	{
		cout << 'A';
		return;
	}
	cout << curr_ch;
	row_print(curr_ch - 1);
	cout << curr_ch;
}
   /***************************************************************************
	 函数名称：
	 功    能：打印字母塔
	 输入参数：
	 返 回 值：
	 说    明：形参按需设置
			   提示：有一个参数order，指定正序/倒序
   ***************************************************************************/
void print_tower(bool order,char ch_end,char ch_current)
{
	if (ch_current < 'A')  // 已经递归到A以下，就结束
		return;
	/* 允许按需定义最多一个静态局部变量（也可以不定义） */
	/* 按需实现，函数中不允许任何形式的循环，函数允许调用其它函数 */
	if (order == false)
	{
		/*if (ch_current < 'A')  
			return;*/
		before_print(ch_end - ch_current);
		row_print(ch_current);
		cout << endl;
		//if(ch_current>'A')
			print_tower(order, ch_end, ch_current - 1);
	}
	else
	{
		print_tower(order, ch_end, ch_current - 1);
		before_print(ch_end - ch_current);
		row_print(ch_current);
		cout << endl;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数中的...允许修改，其余位置不准修改
***************************************************************************/
int main()
{
	char end_ch;

	/* 键盘输入结束字符(仅大写有效，为避免循环出现，不处理输入错误) */
	cout << "请输入结束字符(A~Z)" << endl;
	end_ch = getchar();			//读缓冲区第一个字符
	if (end_ch < 'A' || end_ch > 'Z') {
		cout << "结束字符不是大写字母" << endl;
		return -1;
	}
	int total_len = (end_ch - 'A') * 2 + 1;
	/* 正三角字母塔(中间为A) */
	cout << setw(total_len) << setfill('=') << "=" << setfill(' ') << endl;
	cout << "正三角字母塔(" << end_ch << "->A)" << endl;
	cout << setw(total_len) << setfill('=') << "=" << setfill(' ') << endl;
	print_tower(true,end_ch, end_ch); //正序打印 A~结束字符 
	cout << endl;

	/* 倒三角字母塔(中间为A) */
	cout << setw(total_len) << setfill('=') << "=" << setfill(' ') << endl;
	cout << "倒三角字母塔(" << end_ch << "->A)" << endl;
	cout << setw(total_len) << setfill('=') << "=" << setfill(' ') << endl;
	print_tower(false,end_ch, end_ch); //逆序打印 A~结束字符 
	cout << endl;

	/* 合起来就是漂亮的菱形（中间为A） */
	cout << setw(total_len) << setfill('=') << "=" << setfill(' ') << endl;
	cout << "菱形(" << end_ch << "->A)" << endl;
	cout << setw(total_len) << setfill('=') << "=" << setfill(' ') << endl;
	print_tower(true, end_ch, end_ch);   //打印 A~结束字符的正三角 
	print_tower(false, end_ch, end_ch-1);   //打印 A~结束字符-1的倒三角 
	cout << endl;

	return 0;
}


