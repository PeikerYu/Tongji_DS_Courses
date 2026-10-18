/* 2451951 大数据 于沛可 */
#include<iostream>
#include<cmath>
using namespace std;
extern double a, b, c; //扩展

void fun1()
{
	if (a == 0)
		cout << "不是一元二次方程\n";
	return;
}

void fun2()
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

void fun3()
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

void fun4()
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
