/* 2451951 大数据 于沛可 */
#include<iostream>
#include<cmath>
using namespace std;
void fun3(double a, double b, double c)
{
	if (a != 0 && fabs(b * b - 4 * a * c) < 1e-6)
	{
		double res = (-b / (2.0 * a));
		if (fabs(res) < 1e-6)
			res = 0;
		cout << "有两个相等实根：\n";
		cout << "x1=x2=" << res << endl;
	}
	return;
}