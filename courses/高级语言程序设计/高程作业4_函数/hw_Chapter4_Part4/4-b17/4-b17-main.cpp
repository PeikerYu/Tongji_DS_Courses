/* 2451951 大数据 于沛可 */
#include<iostream>
#include<cmath>
using namespace std;
double a, b, c; //定义全局变量

void fun1();
void fun2();
void fun3();
void fun4();

int main()
{
	cout << "请输入一元二次方程的三个系数a,b,c:\n";
	cin >> a >> b >> c;
	if (fabs(a) < 1e-6)
		a = 0;
	if (fabs(b) < 1e-6)
		b = 0;
	if (fabs(c) < 1e-6)
		c = 0;
	fun1();
	fun2();
	fun3();
	fun4();
	return 0;
}