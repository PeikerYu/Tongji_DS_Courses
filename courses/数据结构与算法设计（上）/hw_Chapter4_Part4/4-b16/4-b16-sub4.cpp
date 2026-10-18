/* 2451951 大数据 于沛可 */
#include<iostream>
#include<cmath>
using namespace std;
void fun4(double a, double b, double c)
{
	if (a != 0 && (b * b - 4 * a * c) <= -1e-6)
	{
		double real_part = -b / (2.0 * a);
		double imag_part = fabs(sqrt(4.0 * a * c - b * b) / (2.0 * a));
		if (fabs(real_part) < 1e-6)
			real_part = 0;
		if (fabs(imag_part) < 1e-6)
			imag_part = 0;
		bool tag = 0;
		if (fabs(imag_part - 1) < 1e-6)
			tag = 1;
		if (real_part == 0) //实部为0
		{
			if (tag == 1) //虚部为1
			{
				cout << "有两个虚根：\n";
				cout << "x1=" << "i\n";
				cout << "x2=" << "-i\n";
			}
			else
			{
				cout << "有两个虚根：\n";
				cout << "x1=" << imag_part << "i\n";
				cout << "x2=" << -imag_part << "i\n";
			}
		}
		else //实部不为0
		{
			if (tag == 1)
			{
				cout << "有两个虚根：\n";
				cout << "x1=" << real_part << "i\n";
				cout << "x2=" << real_part << "-i\n";
			}
			else
			{
				cout << "有两个虚根：\n";
				cout << "x1=" << real_part << "+" << imag_part << "i\n";
				cout << "x2=" << real_part << "-" << imag_part << "i\n";
			}

		}
	}
	return;
}