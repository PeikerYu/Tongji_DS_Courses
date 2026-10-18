/* 2451951 大数据 于沛可 */
#include <stdio.h>
int main()
{
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			printf("%dx%d=%d", j, i, j * i);
			int res = i * j;
			if (res < 10)
			{
				printf("   ");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}