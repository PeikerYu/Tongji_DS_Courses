/* 2451951 大数据 于沛可 */
#include<iostream>
using namespace std;
int main()
{
	char str[3][128];
	for (int i = 0; i < 3; i++)
	{
		cout << "请输入第" << i + 1 << "行\n";
		cin.getline(str[i], 128); //cin.getline()可以读取整行包括空格，直到遇见换行符或者读取了127个字符，会自动在末尾添加'\0'
	}
	int count_num=0, count_ual=0, count_lal=0, count_tap=0,count_other=0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; str[i][j] != '\0'; j++)
		{
			if (str[i][j] <= '9' && str[i][j] >= '0')
				count_num++;
			else if (str[i][j] < 'z' && str[i][j] >= 'a')
				count_lal++;
			else if (str[i][j] <= 'Z' && str[i][j] >= 'A')
				count_ual++;
			else if (str[i][j] == ' ')
				count_tap++;
			else
				count_other++;
		}
	}
	cout << "大写 : " << count_ual << endl;
	cout << "小写 : " << count_lal << endl;
	cout << "数字 : " << count_num << endl;
	cout << "空格 : " << count_tap << endl;
	cout << "其它 : " << count_other << endl;
	return 0;
}