/* 2451951 大数据 于沛可 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int count = 0;
int arr_A[10], arr_B[10], arr_C[10];
int top_A = 0, top_B = 0, top_C = 0;  // 分别对应A B C柱

void print_state() //打印三个柱子的状态
{
    int i;
    printf("A:"); //打印A柱
    for (i = 0; i < top_A; i++)
        printf("%2d", arr_A[i]);
    for (i = top_A; i < 10; i++)
        printf("  ");
    printf(" B:"); //打印B柱
    for (i = 0; i < top_B; i++)
        printf("%2d", arr_B[i]);
    for (i = top_B; i < 10; i++)
        printf("  ");
    printf(" C:"); //打印C柱
    for (i = 0; i < top_C; i++)
        printf("%2d", arr_C[i]);
    for (i = top_C; i < 10; i++)
        printf("  ");
}

void move_plate(char src, char dst)
{
    int plate;
    //从src出栈
    if (src == 'A')
        plate = arr_A[--top_A];
    else if(src=='B')
        plate = arr_B[--top_B];
    else
        plate = arr_C[--top_C];
    // 入栈到dst
    if (dst == 'A')
        arr_A[top_A++] = plate;
    else if (dst == 'B')
        arr_B[top_B++] = plate;
    else
        arr_C[top_C++] = plate;
    count++;
    printf("第%4d 步(%2d): %c-->%c ", count, plate, src, dst);
    print_state();
    printf("\n");
}

// 汉诺塔递归函数
void hanoi(int n, char src, char tmp, char dst)
{
    if (n == 1)
    {
        move_plate(src, dst);
        return;
    }

    hanoi(n - 1, src, dst, tmp);  // 将上面n-1个从起始柱移到中间柱
    move_plate(src, dst);          // 将最大的盘子从起始柱移到目标柱
    hanoi(n - 1, tmp, src, dst);  // 将n-1个从中间柱移到目标柱
}

void init_state(char src,int layer) //初始化栈
{
    int i;
    if (src == 'A')
    {
        for (i = layer; i >= 1; i--)
            arr_A[top_A++] = i;
    }
    else if (src == 'B')
    {
        for (i = layer; i >= 1; i--)
            arr_B[top_B++] = i;
    }
    else
    {
        for (i = layer; i >= 1; i--)
            arr_C[top_C++] = i;
    }
}

int main() 
{
    int layer, ret, c;
    while (1) //输入层数的循环判断
    {
        printf("请输入汉诺塔的层数(1-10)\n");
        ret=scanf("%d",&layer);
    	if (ret != 1 || (ret == 1 && (layer < 1 || layer>10)))
        {
            while (c = getchar() != '\n');
            continue;
        }
        else
        {
            while (c = getchar() != '\n');
            break;
        }
    }
    char src, dst;
    while (1) //处理输入src循环
    {
        printf("请输入起始柱(A-C)\n");
        ret = scanf("%c", &src);
        if (ret==1 && ((src <= 'c' && src >= 'a') || (src <= 'C' && src >= 'A')))
        {
            while (c = getchar() != '\n');
            break;
        }
        else
        {
            while (c = getchar() != '\n');
            continue;
        }
    }
    if (src <= 'c' && src >= 'a') //将src转换成大写，方便后续处理
    {
        src = src + 'A' - 'a';
    }
    while (1) //处理输入dst循环
    {
        printf("请输入目标柱(A-C)\n");
        ret = scanf("%c", &dst);
        if (ret==1 && (dst <= 'c' && dst >= 'a')) //将dst转换成大写，方便后续处理
        {
            dst = dst + 'A' - 'a';
        }
        if (ret==1 && (dst <= 'C' && dst >= 'A') && (dst != src))
        {
            while (c = getchar() != '\n');
            break;
        }
        else if (dst == src)
        {
            printf("目标柱(A)不能与起始柱(A)相同\n");
            while (c = getchar() != '\n');
            continue;
        }
        else
        {
            while (c = getchar() != '\n');
            continue;
        }
    }
    char tmp; //判断tmp
    tmp = 'A' + 'B' + 'C' - dst - src;

    init_state(src, layer);

    printf("初始:                ");
    print_state();
    printf("\n");
    hanoi(layer, src, tmp, dst);

    return 0;
}