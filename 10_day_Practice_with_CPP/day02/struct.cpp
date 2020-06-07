#include <iostream>
#include <cstring>
using namespace std;

//注意字节对齐
//sizeof() 计算的整个大小
//strlen() 计算的到\0结束的位置，不含\0
struct Studetn
{
    int num;
    char name[20];
    char gender;
};

int main()
{
    Studetn st{1, "xxx", 'm'};
    cout << st.num << endl;
    cout << sizeof(st.num) << endl;
    cout << sizeof(st.name) << endl; //sizeof() 计算的整个大小，
    cout << strlen(st.name) << endl; //strlen() 计算的到\0结束的位置，不含\0
    cout << sizeof(st.gender) << endl;
    cout << sizeof(st) << endl;
    return 0;
}