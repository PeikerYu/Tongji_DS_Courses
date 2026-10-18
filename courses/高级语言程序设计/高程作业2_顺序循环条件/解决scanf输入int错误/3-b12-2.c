/* 2451951 大数据 于沛可 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int ret, x,c;

	while (1) {
		printf("请输入x的值[0-100] : ");
		ret = scanf("%d", &x); //读入x的方式必须是scanf且格式符为%d，不准用非scanf
		if (ret == 1 && (x >= 0 && x <= 100))
			break;
		if (ret == 1 && (x < 0 || x>100))
		{
			printf("输入有错[ret=%d x=%d],请重新输入\n", ret, x);
			continue;
		}
		if (ret != 1)
		{
			printf("输入有错[ret=%d x=%d],请重新输入\n", ret, x);
			while ((c = getchar()) != '\n'); //清除输入缓冲区
		}
	}
	printf("ret=%d x=%d\n", ret, x);

	return 0;
}
