#include<iostream>
#include<string>
using namespace std;
struct Student   //设计第一层数据结构--学生基本类（元数据）
{
    string id; //学号
    string name; //姓名
};
struct StudentList  //设计第二层数据结构--学生顺序表
{
    Student arr[20000]; //题目中说不超过10000，可适当放宽
    int len; //顺序表当前的实际长度
};
/**
 * @brief 在学生顺序表的指定位置插入一个新学生记录。
 * @param i 要插入的位置（从1开始计算）
 * @param list 指向 StudentList 结构体的指针，即学生顺序表
 * @param stu_id 待插入学生的学号
 * @param stu_name 待插入学生的姓名
 * @return int 0 表示插入成功，-1 表示插入失败
 */
int insert(int i, StudentList* list, string& stu_id, string& stu_name)
{
    if (i<1 || i>list->len + 1 || list->len >= 20000) //插入之前一定要检查位置是否合法
    {
        cout<<"插入位置不合法！"<<endl;
        return -1;
    }
    else
    {
        for (int j = list->len; j >= i; --j) //插入位置及之后的元素后移
        {
            list->arr[j] = list->arr[j - 1]; //注意下标，位置从1开始
        }
        list->arr[i - 1].id = stu_id;
        list->arr[i - 1].name = stu_name;
        ++list->len;
        return 0;
    }
}
int remove(int i, StudentList* list)
{
    if (i<1 || i>list->len || list->len == 0) //删除之前检查位置是否合法
        return -1;
    else
    {
        for (int j = i; j < list->len; j++) //删除位置及之前的元素前移
        {
            list->arr[j - 1] = list->arr[j]; //注意下标，位置从1开始
        }
        --list->len;
        return 0;
    }
}
void checkName(StudentList* list, string y) 
{
    for (int i = 0; i < list->len; i++)
    {
        if (list->arr[i].name == y)
        {
            cout << i + 1 << ' ' << list->arr[i].id << ' ' << list->arr[i].name << "\n";
            return ;   //找到姓名，直接返回
        }
    }
    cout<<-1<<"\n";  //未找到，返回-1
}
void checkNo(StudentList* list, string x)
{
    for (int i = 0; i < list->len; i++)
    {
        if (list->arr[i].id == x)
        {
            cout << i + 1 << ' ' << list->arr[i].id << ' ' << list->arr[i].name << "\n";
            return ;   //找到id，直接返回
        }
    }
    cout<<-1<<"\n";  //未找到，返回-1
}
int main()
{
    StudentList* list = new StudentList;
    if (list == NULL)
    {
        cout << "Memory allocation failed!" << "\n";
        return 1;
    }
    list->len = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string name, id;
        cin >> id >> name;
        // insert(list->len + 1, list, id, name);
        list->arr[list->len].id=id;
        list->arr[list->len].name=name;
        ++list->len;
    }
    string operation;
    while ((cin >> operation) && operation != "end")
    {
        if (operation == "insert")
        {
            int i;
            string id, name;
            cin >> i >> id >> name;
            cout << insert(i, list, id, name) << "\n";
        }
        else if (operation == "remove")
        {
            int i;
            cin >> i;
            cout << remove(i, list) << "\n";
        }
        else if (operation == "check")
        {
            string type;
            cin >> type;
            if (type == "no")
            {
                string x;
                cin >> x;
                checkNo(list, x);
            }
            else
            {
                string y;
                cin >> y;
                checkName(list, y);
            }
        }
    }
    cout << list->len << "\n";
    delete list;
    return 0;
}

// #include <iostream>
// #include <vector>
// #include <string>
// using namespace std;

// struct Student {
//     string no;   // 学号
//     string name; // 姓名
// };

// class SeqList {
// private:
//     vector<Student> data; // 顺序表（动态数组）
// public:
//     // 创建
//     void create(int n) {
//         data.resize(n);
//         for (int i = 0; i < n; i++) {
//             cin >> data[i].no >> data[i].name;
//         }
//     }

//     // 插入
//     int insert(int pos, const Student &s) {
//         if (pos < 1 || pos > (int)data.size() + 1) return -1;
//         data.insert(data.begin() + (pos - 1), s);
//         return 0;
//     }

//     // 删除
//     int remove(int pos) {
//         if (pos < 1 || pos > (int)data.size()) return -1;
//         data.erase(data.begin() + (pos - 1));
//         return 0;
//     }

//     // 查找（按姓名）
//     int checkByName(const string &name) {
//         for (int i = 0; i < (int)data.size(); i++) {
//             if (data[i].name == name) {
//                 cout << i + 1 << " " << data[i].no << " " << data[i].name << endl;
//                 return 0;
//             }
//         }
//         cout << -1 << endl;
//         return -1;
//     }

//     // 查找（按学号）
//     int checkByNo(const string &no) {
//         for (int i = 0; i < (int)data.size(); i++) {
//             if (data[i].no == no) {
//                 cout << i + 1 << " " << data[i].no << " " << data[i].name << endl;
//                 return 0;
//             }
//         }
//         cout << -1 << endl;
//         return -1;
//     }

//     // 获取学生人数
//     int size() const {
//         return data.size();
//     }
// };

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int n;
//     cin >> n;
//     SeqList list;
//     list.create(n);

//     string cmd;
//     while (cin >> cmd) {
//         if (cmd == "insert") {
//             int pos;
//             Student s;
//             cin >> pos >> s.no >> s.name;
//             cout << list.insert(pos, s) << "\n";
//         } else if (cmd == "remove") {
//             int pos;
//             cin >> pos;
//             cout << list.remove(pos) << "\n";
//         } else if (cmd == "check") {
//             string type;
//             cin >> type;
//             if (type == "name") {
//                 string name;
//                 cin >> name;
//                 list.checkByName(name);
//             } else if (type == "no") {
//                 string no;
//                 cin >> no;
//                 list.checkByNo(no);
//             }
//         } else if (cmd == "end") {
//             cout << list.size() << "\n";
//             break;
//         }
//     }
//     return 0;
// }
