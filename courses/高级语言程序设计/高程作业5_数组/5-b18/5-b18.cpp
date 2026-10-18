/* 2451951 大数据 于沛可 */
/* 2450388 蒲天蓝 2450368 仇智 2453816 温玳宁 2453748 雷志成 2451666 侯翔译 */
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

bool in_other_list(char ch)
{
    const char other_list[] = "!@#$%^&*-_=+,.?";
    for (int i = 0; other_list[i] != '\0'; i++)
    {
        if (other_list[i] == ch) return true;
    }
    return false;
}

int main()
{
    char line[512];

    // 读取并忽略第一行（上一题的输入提示，可能含空格）
    cin.getline(line, 512);
    // 读取 5 个整数
    int key_len, minU, minL, minD, minO;
    if (!(cin >> key_len >> minU >> minL >> minD >> minO))
    {
        cout << "错误\n";
        return 0;
    }
    cin.getline(line, 512); // 读掉数字行剩余的换行
    bool ok = true;
    for (int t = 0; t < 10; t++)
    {
        char p[512];
        if (!cin.getline(p, 512))
        {
            ok = false;
            break;
        }
        int len = (int)strlen(p);
        if (len != key_len)
        {
            ok = false;
            break;
        }
        int cntU = 0, cntL = 0, cntD = 0;
        int cntOtherTotal = 0;      // 所有“非字母非数字”的符号总数

        for (int i = 0; i < key_len; i++)
        {
            unsigned char ch = (unsigned char)p[i];
            // 可见 ASCII 33~126
            if (ch < 33 || ch > 126)
            {
                ok = false;
                break;
            }
            if (isupper(ch)) 
                cntU++;
            else if (islower(ch)) 
                cntL++;
            else if (isdigit(ch)) 
                cntD++;
            else
            {
                if (!in_other_list((char)ch))
                {
                    ok = false;
                    break;
                }
                cntOtherTotal++;
            }
        }
        if (!ok) 
            break;
        // 最小数量检查：大写/小写/数字/其他
        if (cntU < minU || cntL < minL || cntD < minD|| cntOtherTotal< minO)
        {
            ok = false;
            break;
        }
        
        // 四类合计必须等于长度
        if (cntU + cntL + cntD + cntOtherTotal != key_len)
        {
            ok = false;
            break;
        }
    }
    cout << (ok ? "正确\n" : "错误\n");
    return 0;
}
