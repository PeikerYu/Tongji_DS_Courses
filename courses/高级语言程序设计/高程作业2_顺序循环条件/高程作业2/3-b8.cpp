/* 2451951 大数据 于沛可 */
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main()
{
	double res = 0;
	int x;
	int i = 1;
	double t = 1; //每一项
	cout << "请输入x的值[-10 ~ +65]" << endl;
	cin >> x;
	while (x > 65 || x < -10)
	{
		cout << "输入非法，请重新输入" << endl;
		cout << "请输入x的值[-10 ~ +65]" << endl;
		cin >> x;
	}
	while (fabs(t) >= 1e-6)
	{
		res += t;
		t = t * x / i;
		++i;
	}
	cout << setprecision(10);
	cout << "e^" << x << "=" << res << endl;
	return 0;
}