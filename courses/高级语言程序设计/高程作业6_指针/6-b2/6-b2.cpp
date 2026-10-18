/* 2451951 大数据 于沛可 */
#include <iostream>
#include<cstdio>
using namespace std;
bool is_huiwen(char* str)
{
	if (*str == '\0')
		return true;  //空串
	char* p_start = str;
	char* p_end = str;
	while (*p_end != '\0')
		p_end++;
	p_end--;  
	if (*p_end == '\n')
	{
		*p_end = '\0';
		p_end--; //处理掉最后一个回车
	}
	if (p_start == p_end)
		return true; //长度为1
	while (p_start < p_end)
	{
		if (*p_start != *p_end)
		{
			return false;
		}
		p_start++;
		p_end--;
	}
	return true;
}

int main()
{
	cout << "请输入一个长度小于80的字符串（回文串）\n";
	char str[81];
	fgets(str, 81, stdin);
	cout << ((is_huiwen(str)) ? "yes" : "no") << endl;
	return 0;
}