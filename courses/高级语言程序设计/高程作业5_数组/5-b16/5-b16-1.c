/* 2451951 大数据 于沛可 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
void input(char name[][9], char id[][8], int score[])
{
	for (int i = 0; i < 10; i++)
	{
		printf("请输入第%d个人的学号、姓名、成绩\n", i + 1);
		scanf("%s %s %d", id[i], name[i], &score[i]);
	}
}
void sort(char name[][9], char id[][8], int score[])
{
	for (int i = 0; i < 10 - 1; i++)
	{
		for (int j = 0; j < 10 - 1 - i; j++)
		{
			if (strcmp(id[j], id[j + 1]) < 0)
			{
				//交换学号
				char tmp_id[8];
				strcpy(tmp_id, id[j]);
				strcpy(id[j], id[j + 1]);
				strcpy(id[j + 1], tmp_id);
				//交换姓名
				char tmp_name[9];
				strcpy(tmp_name, name[j]);
				strcpy(name[j], name[j + 1]);
				strcpy(name[j + 1], tmp_name);
				//交换分数
				int tmp_score;
				tmp_score = score[j];
				score[j] = score[j + 1];
				score[j + 1] = tmp_score;
			}
		}
	}
}

void print(char name[][9], char id[][8], int score[])
{
	printf("及格名单(学号降序):\n");
	for (int i = 0; i < 10; i++)
	{
		if (score[i] >= 60)
		{
			printf("%s %s %d\n", name[i], id[i], score[i]);
		}
	}
}

int main()
{
	char name[10][9];
	char id[10][8];
	int score[10];
	input(name, id, score);
	sort(name, id, score);
	printf("\n");
	print(name, id, score);
	return 0;
}