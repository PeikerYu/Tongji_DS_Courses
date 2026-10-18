/* 2451951 大数据 于沛可 */
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    double num;
    cout << "请输入找零值：" << endl; 
    cin >> num;                       

    // 浮点数精度修复
    num += 0.00001;
    int cents = int(num * 100);
    int count = 0;
    int _50_yuan = 0, _20_yuan = 0, _10_yuan = 0, _5_yuan = 0, _1_yuan = 0;
    int _5_jiao = 0, _1_jiao = 0;
    int _5_fen = 0, _2_fen = 0, _1_fen = 0;

    // 50元 (5000分)
    if (cents >= 5000)
    {
        _50_yuan = cents / 5000;
        cents -= 5000 * _50_yuan;
        count += _50_yuan;
    }

    // 20元 (2000分)
    if (cents >= 2000)
    {
        _20_yuan = cents / 2000;
        cents -= 2000 * _20_yuan;
        count += _20_yuan;
    }

    // 10元 (1000分)
    if (cents >= 1000)
    {
        _10_yuan = cents / 1000;
        cents -= 1000 * _10_yuan;
        count += _10_yuan;
    }

    // 5元 (500分)
    if (cents >= 500)
    {
        _5_yuan = cents / 500;
        cents -= 500 * _5_yuan;
        count += _5_yuan;
    }

    // 1元 (100分)
    if (cents >= 100)
    {
        _1_yuan = cents / 100;
        cents -= 100 * _1_yuan;
        count += _1_yuan;
    }

    // 5角 (50分)
    if (cents >= 50)
    {
        _5_jiao = cents / 50;
        cents -= 50 * _5_jiao;
        count += _5_jiao;
    }

    // 1角 (10分)
    if (cents >= 10)
    {
        _1_jiao = cents / 10;
        cents -= 10 * _1_jiao;
        count += _1_jiao;
    }

    // 5分
    if (cents >= 5)
    {
        _5_fen = cents / 5;
        cents -= 5 * _5_fen;
        count += _5_fen;
    }

    // 2分
    if (cents >= 2)
    {
        _2_fen = cents / 2;
        cents -= 2 * _2_fen;
        count += _2_fen;
    }

    // 1分 
    if (cents >= 1)
    {
        _1_fen = cents; 
        cents -= 1 * _1_fen;
        count += _1_fen;
    }

    cout << "共" << count << "张找零，具体如下：" << endl;

    cout << setiosflags(ios::left); 
    if (_50_yuan > 0)
    {
        cout << setw(4) << "50元" << " : " << _50_yuan << "张" << endl;
    }

    if (_20_yuan > 0)
    {
        cout << setw(4) << "20元" << " : " << _20_yuan << "张" << endl;
    }

    if (_10_yuan > 0)
    {
        cout << setw(4) << "10元" << " : " << _10_yuan << "张" << endl;
    }

    if (_5_yuan > 0)
    {
        cout << setw(4) << "5元" << " : " << _5_yuan << "张" << endl;
    }

    if (_1_yuan > 0)
    {
        cout << setw(4) << "1元" << " : " << _1_yuan << "张" << endl;
    }

    if (_5_jiao > 0)
    {
        cout << setw(4) << "5角" << " : " << _5_jiao << "张" << endl;
    }

    if (_1_jiao > 0)
    {
        cout << setw(4) << "1角" << " : " << _1_jiao << "张" << endl;
    }

    if (_5_fen > 0)
    {
        cout << setw(4) << "5分" << " : " << _5_fen << "张" << endl;
    }

    if (_2_fen > 0)
    {
        cout << setw(4) << "2分" << " : " << _2_fen << "张" << endl;
    }

    if (_1_fen > 0)
    {
        cout << setw(4) << "1分" << " : " << _1_fen << "张" << endl;
    }

    return 0;
}