/* 2451951 大数据 于沛可 */
  
/* 加入必要的头文件、命名空间、你觉得应该属于工具类的其它函数 */
#include"mine_sweeper.h"
using namespace std;
/***************************************************************************
  函数名称：
  功    能：显示提示信息
  输入参数：
  返 回 值：
  说    明：如果读不懂，暂时放着，等指针和引用学习完成后再阅读
***************************************************************************/
void to_be_continued(const char* prompt)
{
	cct_setcolor(); //恢复缺省颜色
	/*cct_gotoxy(X, Y);*/

	if (prompt)
		cout << prompt << "，按回车键继续...";
	else
		cout << "按回车键继续...";

	/* 忽略除回车键外的所有输入（注意：_getch的回车是\r，而getchar是\n）*/
	while (_getch() != '\r')
		;
	cout << endl;
	cct_cls();

	return;
}

// 转换函数：接收 long 类型的开始时间
struct GameTime convertTime(long start_time)
{
    struct GameTime t;

    // 获取当前时间，并立刻强制转换为 long
    long current_time = (long)clock();

    // 计算总毫秒数
    long total_ms = (long)((current_time - start_time) * 1000 / CLOCKS_PER_SEC);

    t.seconds = (int)(total_ms / 1000);
    t.milliseconds = (int)(total_ms % 1000);

    return t;
}

// 输出函数：保持不变
void printTime(const struct GameTime t)
{
    cout << t.seconds << ".";
    if (t.milliseconds < 10)
        cout << "00";
    else if (t.milliseconds < 100)
        cout << "0";
    cout << t.milliseconds;
}   