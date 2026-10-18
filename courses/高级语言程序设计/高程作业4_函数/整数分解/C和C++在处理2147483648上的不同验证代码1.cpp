///* 测试 C 和 C++ 在处理 2147483648 时的不同行为 */
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <cstdio>
//#include <climits>
//
//using namespace std;
//
//int main()
//{
//    cout << "=== INT 的范围 ===" << endl;
//    cout << "INT_MIN = " << INT_MIN << endl;
//    cout << "INT_MAX = " << INT_MAX << endl;
//    cout << endl;
//
//    // C++ 方式
//    cout << "=== C++ 方式 (cin) ===" << endl;
//    cout << "请输入 2147483648 测试:" << endl;
//    int n1;
//    cin >> n1;
//    cout << "读取到的值: " << n1 << endl;
//
//    // 清空输入缓冲
//    cin.clear();
//    cin.ignore(10000, '\n');
//
//    // C 方式
//    cout << "\n=== C 方式 (scanf) ===" << endl;
//    cout << "请输入 2147483648 测试:" << endl;
//    int n2;
//    scanf("%d", &n2);
//    cout << "读取到的值: " << n2 << endl;
//
//    cout << "\n=== 分析 ===" << endl;
//    cout << "2147483648 = INT_MAX + 1" << endl;
//    cout << "超出 int 范围,会发生溢出" << endl;
//
//    return 0;
//}