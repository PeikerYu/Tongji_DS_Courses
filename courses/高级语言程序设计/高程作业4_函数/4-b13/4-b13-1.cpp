/* 2451951 大数据 于沛可 */
#include <iostream>
#include <iomanip>
using namespace std;

/* ----具体要求----
   1、不允许添加其它头文件
   2、不允许定义全局变量、仅允许hanoi中定义一个静态局部变量
   3、不允许添加其它函数
   4、main函数处理输入，允许循环
   --------------------------------------------------------------------- */

   /***************************************************************************
     函数名称：
     功    能：打印n层汉诺塔的移动顺序
     输入参数：int n：层数
               char src：起始柱
               char tmp：中间柱
               char dst：目标柱
     返 回 值：
     说    明：1、函数名、形参、返回类型均不准动
               2、本函数不允许出现任何形式的循环
               3、允许定义一个静态局部变量
   ***************************************************************************/
void hanoi(int n, char src, char tmp, char dst)
{
	static int count = 0;
    if (n == 1)
    {
        count++;
		cout << setw(5) << count << ":" << setw(3) << "1" << "# " << src << "-->" << dst << endl;
        return;
    }
    else if (n == 2)
    {
        count++;
		cout << setw(5) << count << ":" << setw(3) << "1" << "# " << src << "-->" << tmp << endl;
        count++;
		cout << setw(5) << count << ":" << setw(3) << "2" << "# " << src << "-->" << dst << endl;
        count++;
		cout << setw(5) << count << ":" << setw(3) << "1" << "# " << tmp << "-->" << dst << endl;
        return;
    }
    else
    {
        hanoi(n - 1, src, dst, tmp); //先将上面的n-1个从起始柱移动到中间柱
        count++;
		cout << setw(5) << count << ":" << setw(3) << n << "# " << src << "-->" << dst << endl; //将最下面的从起始柱移动到目标柱
        hanoi(n - 1, tmp, src, dst); //最后将上面的n-1个从中间柱移动到目标柱
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：1、完成输入、调用递归函数
            2、处理输入错误时，允许使用循环
            3、为了统一检查，不再允许添加其它函数（输入起始/目标柱的代码不要求统一函数处理，均直接放在main中）
***************************************************************************/
int main()
{
    int layer;
    while (1) //输入层数的循环判断
    {
        cout << "请输入汉诺塔的层数(1-16)\n";
        cin >> layer;
        if (!cin.good() || (cin.good() && (layer < 1 || layer>16)))
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
    while (1) //处理输入src循环
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
    if (src <= 'c' && src >= 'a') //将src转换成大写，方便后续处理
    {
        src = src + 'A' - 'a';
    }
    while (1) //处理输入dst循环
    {
        cout << "请输入目标柱(A-C)\n";
        cin >> dst;
        if (cin.good() && (dst <= 'c' && dst >= 'a')) //将dst转换成大写，方便后续处理
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
    char tmp; //判断tmp
    if (src == 'A')
    {
        if (dst == 'B')
            tmp = 'C';
        else
            tmp = 'B';
    }
    else if (src == 'B')
    {
        if (dst == 'A')
            tmp = 'C';
        else
            tmp = 'A';
    }
    else
    {
        if (dst == 'A')
            tmp = 'B';
        else
            tmp = 'A';
    }
    cout << "移动步骤为:\n";
    hanoi(layer, src, tmp, dst);
    return 0;
}