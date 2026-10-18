/* 2451951 大数据 于沛可 */
#include <iostream>
#include<math.h>
using namespace std;
int main()
{
	char str[33];
	cout << "请输入一个0/1组成的字符串，长度不超过32\n";
	cin >> str;
	unsigned int res = 0;
	char* p = str;
	while (*p != '\0')
	{
		p++;
	}
	p--;
	int pow_num = 0;
	for (; p >= str; p--,pow_num++)
	{
		res += int(pow(2, pow_num)) * int(*p - '0');
		if (p == str)
			break;
	} 
	cout << res << endl;
	return 0;
}