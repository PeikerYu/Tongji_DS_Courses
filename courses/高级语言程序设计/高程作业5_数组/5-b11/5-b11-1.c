/* 2451951 大数据 于沛可 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>

const char chnstr[] = "零壹贰叁肆伍陆柒捌玖";

char result[256];

/* 追加字符串到 result (用于 拾佰仟圆整) */
void append(const char s[])
{
    int i = 0;
    while (result[i] != '\0') i++;

    int j = 0;
    while (s[j])
    {
        result[i++] = s[j++];
    }
    result[i] = '\0';
}

void append_zero()
{
    int i = 0;
    while (result[i] != '\0') i++;

    result[i++] = chnstr[0]; 
    result[i++] = chnstr[1]; 
    result[i] = '\0';
}

/* 追加一个数字（壹到玖，或作为“零圆”的“零”）的大写 */
void append_num(int num)
{
    // “零壹贰叁肆伍陆柒捌玖”必须从 chnstr 中取值
    char tmp[4] = { 0 };
    int offset = num * 2;
    tmp[0] = chnstr[offset];
    tmp[1] = chnstr[offset + 1];
    append(tmp);
}

// 核心函数：处理四位数字组 
// 返回值：更新后的零标志 (int)
int handle_group(int n, int has_digit_before, int zero_flag_in)
{
    int i = n;
    int k = i / 1000; 
    i %= 1000; // 仟
    int b = i / 100;
    i %= 100;  // 佰
    int s = i / 10;
    i %= 10;  // 拾
    int g = i; // 个

    int current_zero_flag = zero_flag_in;

    // 仟位 k
    if (k)
    {
        append_num(k);
        append("仟");
        has_digit_before = 1;
        current_zero_flag = 0;
    }
    else if (has_digit_before && (b || s || g))
    {
        if (current_zero_flag == 0)
        {
            append_zero(); 
            current_zero_flag = 1;
        }
    }

    // 佰位 b
    if (b)
    {
        if (k == 0 && current_zero_flag == 0 && has_digit_before)
            append_zero(); 
        append_num(b);
        append("佰");
        has_digit_before = 1;
        current_zero_flag = 0;
    }
    else if (has_digit_before && (s || g))
    {
        if (current_zero_flag == 0)
            append_zero(); 
        current_zero_flag = 1;
    }

    // 拾位 s
    if (s)
    {
        if (b == 0 && current_zero_flag == 0 && has_digit_before)
            append_zero(); 
        append_num(s);
        append("拾");
        has_digit_before = 1;
        current_zero_flag = 0;
    }
    else if (has_digit_before && g)
    {
        if (current_zero_flag == 0)
            append_zero(); 
        current_zero_flag = 1;
    }

    // 个位 g
    if (g)
    {
        if (s == 0 && current_zero_flag == 0 && has_digit_before)
            append_zero(); 
        append_num(g);
        has_digit_before = 1;
        current_zero_flag = 0;
    }

    return current_zero_flag;
}


int main(void)
{
    double n, n0;
    double int_part_d;
    int yi_group, wan_group, ge_group;
    int a, b; // a:拾亿, b:亿
    int c; // c:仟万
    int g; // g:仟
    int jiao, fen;

    printf("请输入[0-100亿)之间的数字:\n");
    if (scanf("%lf", &n) != 1)
        return 1;

    result[0] = '\0';
    n0 = n;

    // 增加微小量，防止浮点数精度误差导致取整错误
    n += 1e-8;

    int_part_d = floor(n);

    // 1. 个位组 (0-9999)
    ge_group = (int)fmod(int_part_d, 10000.0);

    // 2. 万位组 (0-9999)
    wan_group = (int)fmod(floor(int_part_d / 10000.0), 10000.0);

    // 3. 亿位组 (0-99)
    yi_group = (int)floor(int_part_d / 100000000.0);

    // 提取各个数字位
    a = yi_group / 10;
    b = yi_group % 10;
    c = wan_group / 1000; // 仟万位
    g = ge_group / 1000; // 仟位

    // 提取小数部分
    {
        double frac = n0 - floor(n0);
        frac += 1e-6;
        jiao = (int)(frac * 10);
        fen = (int)(round(frac * 100.0) - jiao * 10);
        if (fen == 10)
        {
            jiao++;
            fen = 0;
        }
    }

    int has_int = 0;
    int zero_flag = 0;
    int yi_has_output = 0;

    int is_pure_fraction = (yi_group == 0 && wan_group == 0 && ge_group == 0);


    // 亿级部分
    if (yi_group > 0)
    {
        if (a)
        {
            append_num(a);
            append("拾");
            yi_has_output = 1;
            has_int = 1;
            zero_flag = 0;
        }
        if (b)
        {
            append_num(b);
            yi_has_output = 1;
            has_int = 1;
            zero_flag = 0;
        }

        append("亿");
        zero_flag = 0;
    }


    // 万级部分
    if (wan_group > 0)
    {
        // 跨组零
        if (yi_has_output && c == 0 && (wan_group % 1000) != 0)
        {
            append_zero(); 
            zero_flag = 1;
        }

        zero_flag = handle_group(wan_group, has_int, zero_flag);
        has_int = 1;

        append("万");
        zero_flag = 0;
    }

    // 处理 亿/万/个 之间的跨级零 (wan_group = 0)
    else if (yi_group > 0 && ge_group > 0)
    {
        if (g == 0)
        {
            append_zero(); 
            zero_flag = 1;
        }
        else
        {
            zero_flag = 0;
        }
    }

    // 个级部分
    if (ge_group > 0)
    {
        zero_flag = handle_group(ge_group, has_int, zero_flag);
        has_int = 1;
    }


    // 圆和整/角/分部分

    /* 圆 */
    if (has_int)
    {
        append("圆");
    }
    else if (is_pure_fraction && jiao == 0 && fen == 0)
    {
        append_num(0); // 作为数字的“零”
        append("圆");
    }

    /* 小数部分 */
    if (jiao == 0 && fen == 0)
    {
        if (has_int || is_pure_fraction)
        {
            append("整");
        }
    }
    else
    {
        if (jiao)
        {
            append_num(jiao);
            append("角");
            if (fen == 0)
            {
                append("整");
            }
        }
        else if (fen)
        {
            if (has_int)
            {
                append_zero(); 
            }
        }

        if (fen)
        {
            append_num(fen);
            append("分");
        }
    }

    printf("大写结果是:\n");
    printf("%s\n", result);
    return 0;
}