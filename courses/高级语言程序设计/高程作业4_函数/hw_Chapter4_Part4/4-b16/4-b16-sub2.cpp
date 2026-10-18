/* 2451951 大数据 于沛可 */
#include<iostream>
#include<cmath>
using namespace std;
void fun2(double a, double b, double c)
{
	if (a != 0 && (b * b - 4 * a * c) >= 1e-6)
	{
		double x1, x2;
		x1 = (-b + sqrt(b * b - 4 * a * c)) / (2.0 * a);
		x2 = (-b - sqrt(b * b - 4 * a * c)) / (2.0 * a);
		cout << "有两个不等实根：\n";
		if (fabs(x1) < 1e-6)
			x1 = 0;
		if (fabs(x2) < 1e-6)
			x2 = 0;
		if (x1 < x2)
		{
			double t = x1;
			x1 = x2;
			x2 = t;
		}
		cout << "x1=" << x1 << endl;
		cout << "x2=" << x2 << endl;
	}
	return;
}
