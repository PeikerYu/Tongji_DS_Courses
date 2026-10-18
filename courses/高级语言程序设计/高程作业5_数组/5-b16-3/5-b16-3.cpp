/* 2451951 大数据 于沛可 */
#include<iostream>
using namespace std;
#include<string>
#include<cstring>
void input(string name[], string id[], int score[])
{
	for (int i = 0; i < 10; i++)
	{
		cout << "请输入第" << i + 1 << "个人的学号、姓名、成绩\n";
		cin >> id[i] >> name[i] >> score[i];
	}
}
void sort(string name[], string id[], int score[])
{
	for (int i = 0; i < 10 - 1; i++)
	{
		for (int j = 0; j < 10 - 1 - i; j++)
		{
			if (id[j] > id[j + 1])
			{
				//交换学号
				string tmp;
				tmp = id[j];
				id[j] = id[j + 1];
				id[j + 1] = tmp;
				//交换姓名
				string tmp_name;
				tmp_name = name[j];
				name[j] = name[j + 1];
				name[j + 1] = tmp_name;
				//交换分数
				int tmp_score;
				tmp_score = score[j];
				score[j] = score[j + 1];
				score[j + 1] = tmp_score;
			}
		}
	}
}
void print(string name[], string id[], int score[])
{
	cout << "全部学生(学号升序):\n";
	for (int i = 0; i < 10; i++)
	{
		cout << name[i] << " " << id[i] << " " << score[i] << endl;;
	}
}
int main()
{
	string id[10];
	string name[10];
	int score[10];
	input(name, id, score);
	sort(name, id, score);
	cout << endl;
	print(name, id, score);
	return 0;
}