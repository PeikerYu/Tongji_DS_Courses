/* 2451951 大数据 于沛可 */
#include <iostream>
#include <iomanip>
using namespace std;
int step_count = 0;
int arr_top[3] = { 0 };
int arr_plate[3][10];

void print_state() //打印三个柱子的状态
{
    int i;
    printf("A:"); //打印A柱
    for (i = 0; i < arr_top[0]; i++)
        printf("%2d", arr_plate[0][i]);
    for (i = arr_top[0]; i < 10; i++)
        printf("  ");
    printf(" B:"); //打印B柱
    for (i = 0; i < arr_top[1]; i++)
        printf("%2d", arr_plate[1][i]);
    for (i = arr_top[1]; i < 10; i++)
        printf("  ");
    printf(" C:"); //打印C柱
    for (i = 0; i < arr_top[2]; i++)
        printf("%2d", arr_plate[2][i]);
    for (i = arr_top[2]; i < 10; i++)
        printf("  ");
}

void move_plate(char src, char dst)
{
    int plate;
    //从src出栈
    if (src == 'A')
        plate = arr_plate[0][--arr_top[0]];
    else if (src == 'B')
        plate = arr_plate[1][--arr_top[1]];
    else
        plate = arr_plate[2][--arr_top[2]];
    // 入栈到dst
    if (dst == 'A')
        arr_plate[0][arr_top[0]++] = plate;
    else if (dst == 'B')
        arr_plate[1][arr_top[1]++] = plate;
    else
        arr_plate[2][arr_top[2]++] = plate;
    step_count++;
    printf("第%4d 步(%2d): %c-->%c ", step_count, plate, src, dst);
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

void init_state(char src, int layer) //初始化栈
{
    int i;
    if (src == 'A')
    {
        for (i = layer; i >= 1; i--)
            arr_plate[0][arr_top[0]++] = i;
    }
    else if (src == 'B')
    {
        for (i = layer; i >= 1; i--)
            arr_plate[1][arr_top[1]++] = i;
    }
    else
    {
        for (i = layer; i >= 1; i--)
            arr_plate[2][arr_top[2]++] = i;
    }
}


int main()
{
    int layer;
    while (1) //输入层数的循环判断
    {
        cout << "请输入汉诺塔的层数(1-10)\n";
        cin >> layer;
        if (!cin.good() || (cin.good() && (layer < 1 || layer>10)))
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
            break;
        }
    }
    char src, dst;
    while (1) //处理输入src循环
    {
        cout << "请输入起始柱(A-C)\n";
        cin >> src;
        if (cin.good() && ((src <= 'c' && src >= 'a') || (src <= 'C' && src >= 'A')))
        {
            cin.clear();
            cin.ignore(65536, '\n');
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
    }
    if (src <= 'c' && src >= 'a') //将src转换成大写，方便后续处理
    {
        src = src + 'A' - 'a';
    }
    while (1) //处理输入dst循环
    {
        cout << "请输入目标柱(A-C)\n";
        cin >> dst;
        if (cin.good() && (dst <= 'c' && dst >= 'a')) //将dst转换成大写，方便后续处理
        {
            dst = dst + 'A' - 'a';
        }
        if (cin.good() && (dst <= 'C' && dst >= 'A') && (dst != src))
        {
            cin.clear();
            cin.ignore(65536, '\n');
            break;
        }
        else if (dst == src)
        {
            cout << "目标柱(A)不能与起始柱(A)相同\n";
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        else
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
    }
    char tmp = 'A' + 'B' + 'C' - src - dst;
    init_state(src, layer);

    printf("初始:                ");
    print_state();
    printf("\n");
    hanoi(layer, src, tmp, dst);
    return 0;
}