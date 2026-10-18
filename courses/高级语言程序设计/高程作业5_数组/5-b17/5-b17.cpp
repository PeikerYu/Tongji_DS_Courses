/* 2451951 大数据 于沛可 */
#include<iostream>
#include<ctime>
#include <cstdlib>
using namespace std;
int main()
{
	int key_len, upper_count, lower_count, num_count, other_count;
	cout << "请输入密码长度(12-16)， 大写字母个数(≥2)， 小写字母个数(≥2)， 数字个数(≥2)， 其它符号个数(≥2)\n";
	cin >> key_len >> upper_count >> lower_count >> num_count >> other_count;
	if (!cin.good())
	{
		cout << "输入非法\n";
		return 0;
	}
	if (key_len > 16 || key_len < 12)
	{
		cout << "密码长度[" << key_len << "]不正确\n";
		return 0;
	}
	if (upper_count<2 || upper_count>key_len)
	{
		cout << "大写字母个数[" << upper_count << "]不正确\n";
		return 0;
	}
	if(lower_count<2 || lower_count>key_len)
	{
		cout << "小写字母个数[" << lower_count << "]不正确\n";
		return 0;
	}
	if (num_count<2 || num_count>key_len)
	{
		cout << "数字个数[" << num_count << "]不正确\n";
		return 0;
	}
	if (other_count<2 || other_count>key_len)
	{
		cout << "其它符号个数[" << other_count << "]不正确\n";
		return 0;
	}
	if (upper_count + lower_count + num_count + other_count > key_len)
	{
		cout << "所有字符类型之和[" << upper_count << "+" << lower_count << "+" << num_count << "+" << other_count << "]大于总密码长度[" << key_len << "]\n";
		return 0;
	}
	cout << key_len << " " << upper_count << " " << lower_count << " " << num_count << " " << other_count << endl;
	srand((unsigned)time(NULL));
	const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char lower[] = "abcdefghijklmnopqrstuvwxyz";
	const char num[] = "0123456789";
	const char other[] = "!@#$%^&*-_=+,.?";
	char key[10][17];
	for (int i = 0; i < 10; i++)
	{
		int pos = 0;
		for (int j = 0; j < upper_count; j++)
		{
			key[i][pos] = upper[rand() % 26];
			pos++;
		}
		for (int j = 0; j < lower_count; j++)
		{
			key[i][pos] = lower[rand() % 26];
			pos++;
		}
		for (int j = 0; j < num_count; j++)
		{
			key[i][pos] = num[rand() % 10];
			pos++;
		}
		for (int j = 0; j < other_count; j++)
		{
			key[i][pos] = other[rand() % 15];
			pos++;
		}
		while (pos < key_len) //若还剩的有字符，则随机补齐
		{
			int t = rand() % 4;
			if (t == 0) 
				key[i][pos] = upper[rand() % 26];
			else if (t == 1) 
				key[i][pos] = lower[rand() % 26];
			else if (t == 2) 
				key[i][pos] = num[rand() % 10];
			else 
				key[i][pos] = other[rand() % 15];		
			pos++;
		}
		//打乱顺序！
		for (int j = 0; j < key_len; j++)
		{
			int k = rand() % key_len;
			char tmp = key[i][j];
			key[i][j] = key[i][k];
			key[i][k] = tmp;
		}
		key[i][key_len] = '\0';
		cout << key[i] << endl;
	}
	return 0;
}