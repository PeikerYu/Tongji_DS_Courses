/* 2451951 大数据 于沛可 */
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void daxie(int num, int flag_of_zero)
{
	/* 不允许对本函数做任何修改 */
	switch (num) {
	case 0:
		if (flag_of_zero)	//此标记什么意思请自行思考
			cout << "零";
		break;
	case 1:
		cout << "壹";
		break;
	case 2:
		cout << "贰";
		break;
	case 3:
		cout << "叁";
		break;
	case 4:
		cout << "肆";
		break;
	case 5:
		cout << "伍";
		break;
	case 6:
		cout << "陆";
		break;
	case 7:
		cout << "柒";
		break;
	case 8:
		cout << "捌";
		break;
	case 9:
		cout << "玖";
		break;
	default:
		cout << "error";
		break;
	}
}

int main()
{
    double n;
    bool last_was_zero, has_non_zero_integer;
    int a, b, c, d, e, f, g, h, i, j, jiao, fen;
    double n_original, frac;
    bool has_yi_group, has_wan_group, has_ge_group;

    cout << "请输入[0-100亿)之间的数字:" << endl;

    cin >> n;

    last_was_zero = false;//默认最后一位不是零
	has_non_zero_integer = false; //默认整数部分没有非零数字

    // 位数分解 
    n += 1e-8;
    n_original = n;

    a = (int)(n / 1000000000); // 十亿
    n -= a * 1000000000.0;
    b = (int)(n / 100000000); // 亿
    n -= b * 100000000.0;
    c = (int)(n / 10000000); // 千万
    n -= c * 10000000.0;
    d = (int)(n / 1000000);  // 百万
    n -= d * 1000000.0;
    e = (int)(n / 100000);   // 十万
    n -= e * 100000.0;
    f = (int)(n / 10000);    // 万
    n -= f * 10000.0;
    g = (int)(n / 1000);     // 千
    n -= g * 1000.0;
    h = (int)(n / 100);      // 百
    n -= h * 100.0;
    i = (int)(n / 10);      // 十
    n -= i * 10.0;
    j = (int)(n);           // 个

    // 小数部分
    frac = n_original - floor(n_original);
    frac += 1e-6;
    jiao = (int)(frac * 10);
    fen = (int)(round(frac * 100) - jiao * 10);

    // 辅助判断组是否有非零数字
    has_yi_group = a > 0 || b > 0;
    has_wan_group = c > 0 || d > 0 || e > 0 || f > 0;
    has_ge_group = g > 0 || h > 0 || i > 0 || j > 0;

    cout << "大写结果是:" << endl;

    int flag_of_zero=1;
    //亿位组
    if (a > 0)
    {
        flag_of_zero = 0;
		daxie(a, flag_of_zero);
        cout << "拾";
        last_was_zero = false;
        has_non_zero_integer = true;
    }

    if (b > 0)
    {
        flag_of_zero = 0;
		daxie(b, flag_of_zero);
        cout << "亿";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
    {
        if (a > 0)
            cout << "亿";
        last_was_zero = false;
    }

    //万位组
    if (c > 0)
    {
		flag_of_zero = 0;
        daxie(c, flag_of_zero);
        cout << "仟";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
        if (d > 0 || e > 0 || f > 0)
            if (has_non_zero_integer && !last_was_zero)
            {
				daxie(0, 1);
                last_was_zero = true;
            }
       
    if (d > 0)
    {
        flag_of_zero = 0;
        daxie(d, flag_of_zero);
        cout << "佰";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
        if (e > 0 || f > 0)
            if (has_non_zero_integer && !last_was_zero)
            {
				daxie(0, 1);
                last_was_zero = true;
            }
            
    if (e > 0)
    {
        flag_of_zero = 0;
        daxie(e, flag_of_zero);
        cout << "拾";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
        if (f > 0)
            if (has_non_zero_integer && !last_was_zero)
            {
                daxie(0, 1);
                last_was_zero = true;
            }
       
    if (f > 0)
    {
        flag_of_zero = 0;
        daxie(f, flag_of_zero);
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    if (has_wan_group)
    {
        cout << "万";
        last_was_zero = false;
    }
    
    //个位组
    if (g > 0)
    {
        flag_of_zero = 0;
        daxie(g, flag_of_zero);
        cout << "仟";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
        if (h > 0 || i > 0 || j > 0)
            if (has_non_zero_integer && !last_was_zero)
            {
                daxie(0, 1);
                last_was_zero = true;
            }

    if (h > 0)
    {
        flag_of_zero = 0;
        daxie(h, flag_of_zero);
        cout << "佰";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
        if (i > 0 || j > 0)
            if (has_non_zero_integer && !last_was_zero)
            {
				daxie(0, 1);
                last_was_zero = true;
            }
      
    if (i > 0)
    {
        flag_of_zero = 0;
        daxie(i, flag_of_zero);
        cout << "拾";
        last_was_zero = false;
        has_non_zero_integer = true;
    }
    else
        if (j > 0)
            if (has_non_zero_integer && !last_was_zero)
            {
				daxie(0, 1);
                last_was_zero = true;
            }
        
    if (j > 0)
    {
        flag_of_zero = 0;
        daxie(j, flag_of_zero);
        cout << "圆";
        has_non_zero_integer = true;
    }
    else
        if (has_non_zero_integer)
            cout << "圆";

    // 整体零的特殊处理
    if (!has_non_zero_integer && jiao == 0 && fen == 0)
    {
        daxie(0, 1);
        cout<< "圆";
        has_non_zero_integer = true;
    }
    // 小数部分 
    if (jiao == 0 && fen == 0)
    {
        if (has_non_zero_integer)
            cout << "整";
    }
    else
    {
        if (jiao > 0)
        {
            flag_of_zero = 0;
            daxie(jiao, flag_of_zero);
            cout << "角";
            if (fen == 0)
                cout << "整";
            else
            {
                flag_of_zero = 0;
                daxie(fen, flag_of_zero);
                cout << "分";
            }
        }
        else if (fen > 0)
        {
            if (has_non_zero_integer)
                daxie(0, 1);
            flag_of_zero = 0;
            daxie(fen, flag_of_zero);
            cout << "分";
        }
    }
    cout << endl;
    return 0;
}