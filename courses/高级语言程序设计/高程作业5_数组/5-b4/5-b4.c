/* 2451951 大数据 于沛可 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	printf("请输入成绩（最多1000个），负数结束输入\n");
	int arr[1000];
	int temp, count = 0;
	while (1)
	{
		scanf("%d", &temp);
		count++;
		if (temp < 0)
		{
			count--;
			break;
		}
		else if (count == 1000)
		{
			arr[count - 1] = temp;
			break;
		}
		else
			arr[count - 1] = temp;
	}
	if (count == 0)
		printf("无有效输入\n");
	else
	{
		printf("输入的数组为:\n");
		for (int i = 0; i < count; i++)
		{
			printf("%d ", arr[i]);
			if ((i + 1) % 10 == 0)
				printf("\n");
		}
		if (count % 10 != 0)
			printf("\n");
	}
	int arr_score[101] = { 0 };
	for (int i = 0; i < count; i++)
	{
		arr_score[arr[i]]++;
	}
	printf("分数与人数的对应关系为:\n");
	for (int i = 100; i >= 0; i--)
	{
		if (arr_score[i] != 0)
			printf("%d %d\n", i, arr_score[i]);
	}
	return 0;
}



