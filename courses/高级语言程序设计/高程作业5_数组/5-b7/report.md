```cpp

hanoi(n, src, tmp, dst,mode):
    if n == 1:
        移动盘子从src到dst（并进行图形/文字的显示）
        return
    hanoi(n-1, src, dst, tmp)  // 将n-1个盘子从src借助dst移到tmp
    移动第n个盘子从src到dst（并进行图形/文字的显示）
    hanoi(n-1, tmp, src, dst)  // 将n-1个盘子从tmp借助src移到dst


move_disk_hdc(int plate, char src, char dst, int layer)
    1.计算盘子、src/dst 柱子的位置参数
    2.移动阶段：
        a. 向上移动阶段
        While (cur_y 盘子当前纵坐标 > HDC_Top_Y):
            擦除下方strip
            向上移动 HDC_Step_Y
            画出上方strip
            如在立柱范围内，恢复立柱
            同时执行延时，同步更新盘子坐标

        b. 水平移动阶段
        While (cur_x != dst_x):
            擦除移动方向相反一侧的strip
            水平移动 HDC_Step_X
            画出移动方向一侧的strip
            同时执行延时，同步更新盘子坐标

        c. 向下移动阶段
       （类似向上，方向相反）


int move_plate(char src, char dst, int mode)  //返回移动的盘子号
    根据模式（主要是4/8）来计算A/B/C三个柱子的底座坐标
    if mode=4/8:
        进行清除操作：用空格覆盖src最上面一个盘子，用来显示纵向打印动态变化效果
    定义 int plate
    //从src出栈
    if (src == 'A')
        plate = arr_A[--top_A];
    else if (src == 'B')
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

    count_step++;
    return plate;
    
    
//根据模式选择，移动并打印，是hanoi递归函数的主体调用部分
move_and_show(char src, char dst, int plate, int mode, int layer) 
    if mode=8:
        move_disk_hdc; //显示图形移动
        move_plate; //更新内部数组状态
        同步显示文字部分：
        cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y);
        show_row; //横向显示每一步的移动
        draw_hanoi; //纵向显示每一步的移动
    else if mode = 1/2/3/4:
        各自调用函数，实现各自功能
        
        
        
        
        
        
        
        



```

