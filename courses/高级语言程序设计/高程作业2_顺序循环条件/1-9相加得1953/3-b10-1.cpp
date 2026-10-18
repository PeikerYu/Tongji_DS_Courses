/* 2451951 大数据 于沛可 */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <windows.h> //取系统时间
using namespace std;

int main()
{
	LARGE_INTEGER tick, begin, end;

	QueryPerformanceFrequency(&tick);	//获得计数器频率
	QueryPerformanceCounter(&begin);	//获得初始硬件计数器计数

	/* 此处是你的程序开始 */
	int count = 0;
	for (int a = 1; a <= 9; a++) //1
		for (int b = 1; b <= 9; b++) //2
			if (b != a)
				for (int c = 1; c <= 9; c++) //3
					if (c != a && c != b)
						for (int d = 1; d <= 9; d++) //4
							if (d != a && d != b && d != c)
								for (int e = 1; e <= 9; e++) //5
									if (e != a && e != b && e != c && e != d)
										for (int f = 1; f <= 9; f++) //6
											if (f != a && f != b && f != c && f != d && f != e)
												for (int g = 1; g <= 9; g++) //7
													if (g != a && g != b && g != c && g != d && g != e && g != f)
														for (int h = 1; h <= 9; h++) //8
															if (h != a && h != b && h != c && h != d && h != e && h != f && h != g)
																for (int i = 1; i <= 9; i++) //9
																	if (i != a && i != b && i != c && i != d && i != e && i != f && i != g && i != h)
																	{
																		int n1 = 100 * a + 10 * b + c;
																		int n2 = 100 * d + 10 * e + f;
																		int n3 = 100 * g + 10 * h + i;
																		if (n1 + n2 + n3 == 1953 && n1 < n2 && n2 < n3)
																		{
																			++count;
																			cout << "No." << setw(3) << count << " : " << n1 << "+" << n2 << "+" << n3 << "=1953" << endl;
																		}
																	}
	cout << "total=" << count << endl;
	/* 此处是你的程序结束 */

	QueryPerformanceCounter(&end);		//获得终止硬件计数器计数

	cout << "计数器频率 : " << tick.QuadPart << "Hz" << endl;
	cout << "计数器计数 : " << end.QuadPart - begin.QuadPart << endl;
	cout << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒" << endl;

	return 0;
}