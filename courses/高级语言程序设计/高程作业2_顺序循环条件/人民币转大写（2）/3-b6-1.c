/* 2451951 ´óÊý¾Ý ÓÚÅæ¿É */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main()
{
    double n;
    bool last_was_zero;
    bool has_non_zero_integer;
    int a, b, c, d, e, f, g, h, i, j, jiao, fen;
    double n_original, frac;
    bool has_yi_group, has_wan_group, has_ge_group;

    printf("ÇëÊäÈë[0-100ÒÚ)Ö®¼äµÄÊý×Ö:\n");

    /* ÊäÈëÊ¹ÓÃ scanf */
    scanf("%lf", &n);

    last_was_zero = false;
    has_non_zero_integer = false;

    // Î»Êý·Ö½â?
    n += 1e-8;
    n_original = n;

    a = (int)(n / 1000000000); 
    n -= a * 1000000000.0;
    b = (int)(n / 100000000); 
    n -= b * 100000000.0;
    c = (int)(n / 10000000);
    n -= c * 10000000.0;
    d = (int)(n / 1000000);
    n -= d * 1000000.0;
    e = (int)(n / 100000);
    n -= e * 100000.0;
    f = (int)(n / 10000);
    n -= f * 10000.0;
    g = (int)(n / 1000);
    n -= g * 1000.0;
    h = (int)(n / 100);
    n -= h * 100.0;
    i = (int)(n / 10);
    n -= i * 10.0;
    j = (int)(n);

    // Ð¡Êý²¿·Ö
    frac = n_original - floor(n_original);
    frac += 1e-6;
    jiao = (int)(frac * 10);
    fen = (int)(round(frac * 100) - jiao * 10);

    // ¸¨ÖúÅÐ¶Ï×éÊÇ·ñÓÐ·ÇÁãÊý×Ö
    has_yi_group = a > 0 || b > 0;
    has_wan_group = c > 0 || d > 0 || e > 0 || f > 0;
    has_ge_group = g > 0 || h > 0 || i > 0 || j > 0;

    printf("´óÐ´½á¹ûÊÇ:\n");

    // ÒÚÎ»×é?
    if (a > 0)
    {
        if (a == 1)
        {
            printf("Ò¼");
        }
        else if (a == 2)
        {
            printf("·¡");
        }
        else if (a == 3)
        {
            printf("Èþ");
        }
        else if (a == 4)
        {
            printf("ËÁ");
        }
        else if (a == 5)
        {
            printf("Îé");
        }
        else if (a == 6)
        {
            printf("Â½");
        }
        else if (a == 7)
        {
            printf("Æâ");
        }
        else if (a == 8)
        {
            printf("°Æ");
        }
        else if (a == 9)
        {
            printf("¾Á");
        }
        printf("Ê°");
        last_was_zero = false;
        has_non_zero_integer = true;
    }

    if (b > 0)
    {
        if (b == 1)
        {
            printf("Ò¼");
        }
        else if (b == 2)
        {
            printf("·¡");
        }
        else if (b == 3)
        {
            printf("Èþ");
        }
        else if (b == 4)
        {
            printf("ËÁ");
        }
        else if (b == 5)
        {
            printf("Îé");
        }
        else if (b == 6)
        {
            printf("Â½");
        }
        else if (b == 7)
        {
            printf("Æâ");
        }
        else if (b == 8)
        {
            printf("°Æ");
        }
        else if (b == 9)
        {
            printf("¾Á");
        }
        printf("ÒÚ");
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (a > 0)
        {
            printf("ÒÚ");
        }
        last_was_zero = false;
    }

    // ÍòÎ»×é?
    if (c > 0)
    {
        if (c == 1)
        {
            printf("Ò¼");
        }
        else if (c == 2)
        {
            printf("·¡");
        }
        else if (c == 3)
        {
            printf("Èþ");
        }
        else if (c == 4)
        {
            printf("ËÁ");
        }
        else if (c == 5)
        {
            printf("Îé");
        }
        else if (c == 6)
        {
            printf("Â½");
        }
        else if (c == 7)
        {
            printf("Æâ");
        }
        else if (c == 8)
        {
            printf("°Æ");
        }
        else
        {
            printf("¾Á");
        }
        printf("Çª");
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (d > 0 || e > 0 || f > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                printf("Áã");
                last_was_zero = true;
            }
        }
        else
        {
            last_was_zero = false;
        }
    }

    if (d > 0)
    {
        if (d == 1)
        {
            printf("Ò¼");
        }
        else if (d == 2)
        {
            printf("·¡");
        }
        else if (d == 3)
        {
            printf("Èþ");
        }
        else if (d == 4)
        {
            printf("ËÁ");
        }
        else if (d == 5)
        {
            printf("Îé");
        }
        else if (d == 6)
        {
            printf("Â½");
        }
        else if (d == 7)
        {
            printf("Æâ");
        }
        else if (d == 8)
        {
            printf("°Æ");
        }
        else
        {
            printf("¾Á");
        }
        printf("°Û");
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (e > 0 || f > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                printf("Áã");
                last_was_zero = true;
            }
        }
        else
        {
            last_was_zero = false;
        }
    }
    if (e > 0)
    {
        if (e == 1)
        {
            printf("Ò¼");
        }
        else if (e == 2)
        {
            printf("·¡");
        }
        else if (e == 3)
        {
            printf("Èþ");
        }
        else if (e == 4)
        {
            printf("ËÁ");
        }
        else if (e == 5)
        {
            printf("Îé");
        }
        else if (e == 6)
        {
            printf("Â½");
        }
        else if (e == 7)
        {
            printf("Æâ");
        }
        else if (e == 8)
        {
            printf("°Æ");
        }
        else
        {
            printf("¾Á");
        }

        printf("Ê°");
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (f > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                printf("Áã");
                last_was_zero = true;
            }
        }
        else
        {
            last_was_zero = false;
        }
    }
    if (f > 0)
    {
        if (f == 1)
        {
            printf("Ò¼");
        }
        else if (f == 2)
        {
            printf("·¡");
        }
        else if (f == 3)
        {
            printf("Èþ");
        }
        else if (f == 4)
        {
            printf("ËÁ");
        }
        else if (f == 5)
        {
            printf("Îé");
        }
        else if (f == 6)
        {
            printf("Â½");
        }
        else if (f == 7)
        {
            printf("Æâ");
        }
        else if (f == 8)
        {
            printf("°Æ");
        }
        else
        {
            printf("¾Á");
        }
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    if (has_wan_group)
    {
        printf("Íò");
    }
    last_was_zero = false; //ÖØÖÃÎª¼Ù£¬½øÈëÏÂÒ»×é´¦Àí

    //? ¸öÎ»×é?
    if (g > 0)
    {
        if (g == 1)
        {
            printf("Ò¼");
        }
        else if (g == 2)
        {
            printf("·¡");
        }
        else if (g == 3)
        {
            printf("Èþ");
        }
        else if (g == 4)
        {
            printf("ËÁ");
        }
        else if (g == 5)
        {
            printf("Îé");
        }
        else if (g == 6)
        {
            printf("Â½");
        }
        else if (g == 7)
        {
            printf("Æâ");
        }
        else if (g == 8)
        {
            printf("°Æ");
        }
        else
        {
            printf("¾Á");
        }
        printf("Çª");
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (h > 0 || i > 0 || j > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                printf("Áã");
                last_was_zero = true;
            }
        }
        else
        {
            last_was_zero = false;
        }
    }
    if (h > 0)
    {
        if (h == 1)
        {
            printf("Ò¼");
        }
        else if (h == 2)
        {
            printf("·¡");
        }
        else if (h == 3)
        {
            printf("Èþ");
        }
        else if (h == 4)
        {
            printf("ËÁ");
        }
        else if (h == 5)
        {
            printf("Îé");
        }
        else if (h == 6)
        {
            printf("Â½");
        }
        else if (h == 7)
        {
            printf("Æâ");
        }
        else if (h == 8)
        {
            printf("°Æ");
        }
        else
        {
            printf("¾Á");
        }

        printf("°Û");
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (i > 0 || j > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                printf("Áã");
                last_was_zero = true;
            }
        }
        else
        {
            last_was_zero = false;
        }
    }
    if (i > 0)
    {
        if (i == 1)
        {
            printf("Ò¼");
        }
        else if (i == 2)
        {
            printf("·¡");
        }
        else if (i == 3)
        {
            printf("Èþ");
        }
        else if (i == 4)
        {
            printf("ËÁ");
        }
        else if (i == 5)
        {
            printf("Îé");
        }
        else if (i == 6)
        {
            printf("Â½");
        }
        else if (i == 7)
        {
            printf("Æâ");
        }
        else if (i == 8)
        {
            printf("°Æ");
        }
        else
        {
            printf("¾Á");
        }

        printf("Ê°");
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (j > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                printf("Áã");
                last_was_zero = true;
            }
        }
        else
        {
            last_was_zero = false;
        }
    }
    if (j > 0)
    {
        if (j == 1)
        {
            printf("Ò¼");
        }
        else if (j == 2)
        {
            printf("·¡");
        }
        else if (j == 3)
        {
            printf("Èþ");
        }
        else if (j == 4)
        {
            printf("ËÁ");
        }
        else if (j == 5)
        {
            printf("Îé");
        }
        else if (j == 6)
        {
            printf("Â½");
        }
        else if (j == 7)
        {
            printf("Æâ");
        }
        else if (j == 8)
        {
            printf("°Æ");
        }
        else
        {
            printf("¾Á");
        }
        printf("Ô²");
        has_non_zero_integer = true;
    }
    else
    {
        if (has_non_zero_integer)
        {
            printf("Ô²");
        }
    }
    // ÕûÌåÁãµÄÌØÊâ´¦Àí
    if (!has_non_zero_integer && jiao == 0 && fen == 0)
    {
        printf("ÁãÔ²");
        has_non_zero_integer = true;
    }

    // Ð¡Êý²¿·Ö?
    if (jiao == 0 && fen == 0)
    {
        if (has_non_zero_integer)
        {
            printf("Õû");
        }
    }
    else
    {
        if (jiao > 0)
        {
            if (jiao == 1)
            {
                printf("Ò¼");
            }
            else if (jiao == 2)
            {
                printf("·¡");
            }
            else if (jiao == 3)
            {
                printf("Èþ");
            }
            else if (jiao == 4)
            {
                printf("ËÁ");
            }
            else if (jiao == 5)
            {
                printf("Îé");
            }
            else if (jiao == 6)
            {
                printf("Â½");
            }
            else if (jiao == 7)
            {
                printf("Æâ");
            }
            else if (jiao == 8)
            {
                printf("°Æ");
            }
            else
            {
                printf("¾Á");
            }
            printf("½Ç");
            if (fen == 0)
            {
                printf("Õû");
            }
            else
            {
                if (fen == 1)
                {
                    printf("Ò¼");
                }
                else if (fen == 2)
                {
                    printf("·¡");
                }
                else if (fen == 3)
                {
                    printf("Èþ");
                }
                else if (fen == 4)
                {
                    printf("ËÁ");
                }
                else if (fen == 5)
                {
                    printf("Îé");
                }
                else if (fen == 6)
                {
                    printf("Â½");
                }
                else if (fen == 7)
                {
                    printf("Æâ");
                }
                else if (fen == 8)
                {
                    printf("°Æ");
                }
                else
                {
                    printf("¾Á");
                }
                printf("·Ö");
            }
        }
        else if (fen > 0)
        {
            if (has_non_zero_integer)
            {
                printf("Áã");
            }
            if (fen == 1)
            {
                printf("Ò¼");
            }
            else if (fen == 2)
            {
                printf("·¡");
            }
            else if (fen == 3)
            {
                printf("Èþ");
            }
            else if (fen == 4)
            {
                printf("ËÁ");
            }
            else if (fen == 5)
            {
                printf("Îé");
            }
            else if (fen == 6)
            {
                printf("Â½");
            }
            else if (fen == 7)
            {
                printf("Æâ");
            }
            else if (fen == 8)
            {
                printf("°Æ");
            }
            else
            {
                printf("¾Á");
            }
            printf("·Ö");
        }
    }
    printf("\n");
    return 0;
}