/* 2451951 大数据 于沛可 */
#include<iostream>
#include<cmath>
#include "4-b16.h"
using namespace std;
int main()
{
	cout << "请输入一元二次方程的三个系数a,b,c:\n";
	double a, b, c;
	cin >> a >> b >> c;
	if (fabs(a) < 1e-6)
		a = 0;
	if (fabs(b) < 1e-6)
		b = 0;
	if (fabs(c) < 1e-6)
		c = 0;
	fun1(a);
	fun2(a, b, c);
	fun3(a, b, c);
	fun4(a, b, c);
	return 0;
}