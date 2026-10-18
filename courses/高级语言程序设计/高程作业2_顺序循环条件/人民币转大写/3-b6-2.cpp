/* 2451951 ´óÊý¾Ý ÓÚÅæ¿É */
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    double n;
    bool last_was_zero,has_non_zero_integer;
    int a, b, c, d, e, f, g, h, i, j, jiao, fen;
    double n_original, frac;
    bool has_yi_group, has_wan_group, has_ge_group;

    cout << "ÇëÊäÈë[0-100ÒÚ)Ö®¼äµÄÊý×Ö:" << endl;

    cin >> n;

    last_was_zero = false;
    has_non_zero_integer = false;

    // Î»Êý·Ö½â 
    n += 1e-8;
    n_original = n;

    a = (int)(n / 1000000000); // Ê®ÒÚ
    n -= a * 1000000000.0;
    b = (int)(n / 100000000); // ÒÚ
    n -= b * 100000000.0;
    c = (int)(n / 10000000); // Ç§Íò
    n -= c * 10000000.0;
    d = (int)(n / 1000000);  // °ÙÍò
    n -= d * 1000000.0;
    e = (int)(n / 100000);   // Ê®Íò
    n -= e * 100000.0;
    f = (int)(n / 10000);    // Íò
    n -= f * 10000.0;
    g = (int)(n / 1000);     // Ç§
    n -= g * 1000.0;
    h = (int)(n / 100);      // °Ù
    n -= h * 100.0;
    i = (int)(n / 10);      // Ê®
    n -= i * 10.0;
    j = (int)(n);           // ¸ö

    // Ð¡Êý²¿·Ö
    frac = n_original - floor(n_original);
    frac += 1e-6;
    jiao = (int)(frac * 10);
    fen = (int)(round(frac * 100) - jiao * 10);

    // ¸¨ÖúÅÐ¶Ï×éÊÇ·ñÓÐ·ÇÁãÊý×Ö
    has_yi_group = a > 0 || b > 0;
    has_wan_group = c > 0 || d > 0 || e > 0 || f > 0;
    has_ge_group = g > 0 || h > 0 || i > 0 || j > 0;

    cout << "´óÐ´½á¹ûÊÇ:" << endl;

    // ÒÚÎ»×é 
    if (a > 0)
    {
        if (a == 1)
        {
            cout << "Ò¼";
        }
        else if (a == 2)
        {
            cout << "·¡";
        }
        else if (a == 3)
        {
            cout << "Èþ";
        }
        else if (a == 4)
        {
            cout << "ËÁ";
        }
        else if (a == 5)
        {
            cout << "Îé";
        }
        else if (a == 6)
        {
            cout << "Â½";
        }
        else if (a == 7)
        {
            cout << "Æâ";
        }
        else if (a == 8)
        {
            cout << "°Æ";
        }
        else if (a == 9)
        {
            cout << "¾Á";
        }
        cout << "Ê°";
        last_was_zero = false;
        has_non_zero_integer = true;
    }

    if (b > 0)
    {
        if (b == 1)
        {
            cout << "Ò¼";
        }
        else if (b == 2)
        {
            cout << "·¡";
        }
        else if (b == 3)
        {
            cout << "Èþ";
        }
        else if (b == 4)
        {
            cout << "ËÁ";
        }
        else if (b == 5)
        {
            cout << "Îé";
        }
        else if (b == 6)
        {
            cout << "Â½";
        }
        else if (b == 7)
        {
            cout << "Æâ";
        }
        else if (b == 8)
        {
            cout << "°Æ";
        }
        else if (b == 9)
        {
            cout << "¾Á";
        }
        cout << "ÒÚ";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (a > 0)
        {
            cout << "ÒÚ";
        }
        last_was_zero = false;
    }

    // ÍòÎ»×é 
    if (c > 0)
    {
        if (c == 1)
        {
            cout << "Ò¼";
        }
        else if (c == 2)
        {
            cout << "·¡";
        }
        else if (c == 3)
        {
            cout << "Èþ";
        }
        else if (c == 4)
        {
            cout << "ËÁ";
        }
        else if (c == 5)
        {
            cout << "Îé";
        }
        else if (c == 6)
        {
            cout << "Â½";
        }
        else if (c == 7)
        {
            cout << "Æâ";
        }
        else if (c == 8)
        {
            cout << "°Æ";
        }
        else
        {
            cout << "¾Á";
        }
        cout << "Çª";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (d > 0 || e > 0 || f > 0) 
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                cout << "Áã";
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
            cout << "Ò¼";
        }
        else if (d == 2)
        {
            cout << "·¡";
        }
        else if (d == 3)
        {
            cout << "Èþ";
        }
        else if (d == 4)
        {
            cout << "ËÁ";
        }
        else if (d == 5)
        {
            cout << "Îé";
        }
        else if (d == 6)
        {
            cout << "Â½";
        }
        else if (d == 7)
        {
            cout << "Æâ";
        }
        else if (d == 8)
        {
            cout << "°Æ";
        }
        else
        {
            cout << "¾Á";
        }
        cout << "°Û";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (e > 0 || f > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                cout << "Áã";
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
            cout << "Ò¼";
        }
        else if (e == 2)
        {
            cout << "·¡";
        }
        else if (e == 3)
        {
            cout << "Èþ";
        }
        else if (e == 4)
        {
            cout << "ËÁ";
        }
        else if (e == 5)
        {
            cout << "Îé";
        }
        else if (e == 6)
        {
            cout << "Â½";
        }
        else if (e == 7)
        {
            cout << "Æâ";
        }
        else if (e == 8)
        {
            cout << "°Æ";
        }
        else
        {
            cout << "¾Á";
        }

        cout << "Ê°";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (f > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                cout << "Áã";
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
            cout << "Ò¼";
        }
        else if (f == 2)
        {
            cout << "·¡";
        }
        else if (f == 3)
        {
            cout << "Èþ";
        }
        else if (f == 4)
        {
            cout << "ËÁ";
        }
        else if (f == 5)
        {
            cout << "Îé";
        }
        else if (f == 6)
        {
            cout << "Â½";
        }
        else if (f == 7)
        {
            cout << "Æâ";
        }
        else if (f == 8)
        {
            cout << "°Æ";
        }
        else
        {
            cout << "¾Á";
        }
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    if (has_wan_group)
    {
        cout << "Íò";
    }
	last_was_zero = false; //ÖØÖÃÎª¼Ù£¬½øÈëÏÂÒ»×é´¦Àí

    //  ¸öÎ»×é 
    if (g > 0)
    {
        if (g == 1)
        {
            cout << "Ò¼";
        }
        else if (g == 2)
        {
            cout << "·¡";
        }
        else if (g == 3)
        {
            cout << "Èþ";
        }
        else if (g == 4)
        {
            cout << "ËÁ";
        }
        else if (g == 5)
        {
            cout << "Îé";
        }
        else if (g == 6)
        {
            cout << "Â½";
        }
        else if (g == 7)
        {
            cout << "Æâ";
        }
        else if (g == 8)
        {
            cout << "°Æ";
        }
        else
        {
            cout << "¾Á";
        }
        cout << "Çª";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (h > 0 || i > 0 || j > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                cout << "Áã";
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
            cout << "Ò¼";
        }
        else if (h == 2)
        {
            cout << "·¡";
        }
        else if (h == 3)
        {
            cout << "Èþ";
        }
        else if (h == 4)
        {
            cout << "ËÁ";
        }
        else if (h == 5)
        {
            cout << "Îé";
        }
        else if (h == 6)
        {
            cout << "Â½";
        }
        else if (h == 7)
        {
            cout << "Æâ";
        }
        else if (h == 8)
        {
            cout << "°Æ";
        }
        else
        {
            cout << "¾Á";
        }

        cout << "°Û";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (i > 0 || j > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                cout << "Áã";
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
            cout << "Ò¼";
        }
        else if (i == 2)
        {
            cout << "·¡";
        }
        else if (i == 3)
        {
            cout << "Èþ";
        }
        else if (i == 4)
        {
            cout << "ËÁ";
        }
        else if (i == 5)
        {
            cout << "Îé";
        }
        else if (i == 6)
        {
            cout << "Â½";
        }
        else if (i == 7)
        {
            cout << "Æâ";
        }
        else if (i == 8)
        {
            cout << "°Æ";
        }
        else
        {
            cout << "¾Á";
        }

        cout << "Ê°";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (j > 0)
        {
            if (has_non_zero_integer && !last_was_zero)
            {
                cout << "Áã";
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
            cout << "Ò¼";
        }
        else if (j == 2)
        {
            cout << "·¡";
        }
        else if (j == 3)
        {
            cout << "Èþ";
        }
        else if (j == 4)
        {
            cout << "ËÁ";
        }
        else if (j == 5)
        {
            cout << "Îé";
        }
        else if (j == 6)
        {
            cout << "Â½";
        }
        else if (j == 7)
        {
            cout << "Æâ";
        }
        else if (j == 8)
        {
            cout << "°Æ"; 
        }
        else
        {
            cout << "¾Á";
        }
        cout << "Ô²";
        has_non_zero_integer = true;
    }
    else
    {
        if (has_non_zero_integer)
        {
            cout << "Ô²";
        }
    }
    // ÕûÌåÁãµÄÌØÊâ´¦Àí
    if (!has_non_zero_integer && jiao == 0 && fen == 0)
    {
        cout << "ÁãÔ²";
        has_non_zero_integer = true;
    }

    // Ð¡Êý²¿·Ö 
    if (jiao == 0 && fen == 0)
    {
        if (has_non_zero_integer)
        {
            cout << "Õû";
        }
    }
    else
    {
        if (jiao > 0)
        {
            if (jiao == 1)
            {
                cout << "Ò¼";
            }
            else if (jiao == 2)
            {
                cout << "·¡";
            }
            else if (jiao == 3)
            {
                cout << "Èþ";
            }
            else if (jiao == 4)
            {
                cout << "ËÁ";
            }
            else if (jiao == 5)
            {
                cout << "Îé";
            }
            else if (jiao == 6)
            {
                cout << "Â½";
            }
            else if (jiao == 7)
            {
                cout << "Æâ";
            }
            else if (jiao == 8)
            {
                cout << "°Æ";
            }
            else
            {
                cout << "¾Á";
            }
            cout << "½Ç";
            if (fen == 0)
            {
                cout << "Õû";
            }
            else
            {
                if (fen == 1)
                {
                    cout << "Ò¼";
                }
                else if (fen == 2)
                {
                    cout << "·¡";
                }
                else if (fen == 3)
                {
                    cout << "Èþ";
                }
                else if (fen == 4)
                {
                    cout << "ËÁ";
                }
                else if (fen == 5)
                {
                    cout << "Îé";
                }
                else if (fen == 6)
                {
                    cout << "Â½";
                }
                else if (fen == 7)
                {
                    cout << "Æâ";
                }
                else if (fen == 8)
                {
                    cout << "°Æ";
                }
                else
                {
                    cout << "¾Á";
                }
                cout << "·Ö";
            }
        }
        else if (fen > 0)
        {
            if (has_non_zero_integer)
            {
                cout << "Áã";
            }
            if (fen == 1)
            {
                cout << "Ò¼";
            }
            else if (fen == 2)
            {
                cout << "·¡";
            }
            else if (fen == 3)
            {
                cout << "Èþ";
            }
            else if (fen == 4)
            {
                cout << "ËÁ";
            }
            else if (fen == 5)
            {
                cout << "Îé";
            }
            else if (fen == 6)
            {
                cout << "Â½";
            }
            else if (fen == 7)
            {
                cout << "Æâ";
            }
            else if (fen == 8)
            {
                cout << "°Æ";
            }
            else
            {
                cout << "¾Á";
            }
            cout << "·Ö";
        }
    }
    cout << endl;
    return 0;
}