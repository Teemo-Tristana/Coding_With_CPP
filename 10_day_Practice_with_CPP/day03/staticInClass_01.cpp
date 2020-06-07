/*
类的成员函数|变量：
    类的静态成员变量必须在类外初始化[初始化在方法文件中]，
    类的静态成员函数属于类所有，不属于任何实例对象，类的静态成员函数没有this指针
    
    类的成员函数和成员变量 不占类的空间：静态成员函数单独存储，不是对象的组成部分。
    必须在类外初始化静态成员变量：因为声明只是描述如何分配内存，但并不分配内存
   
    可以使用类名和作用域操作符来调用类的静态函数
    静态成员函数只能引用属于该类的静态数据成员或静态成员函数。
   
    类的成员函数不能在后面加const：因为静态成员函数没有this指针，所有不能加const
    也即是对于的类的成员函数 static 和 const 是冲突的


    类的成员函数占类的空间
*/

#include <iostream>
using namespace std;

class Application
{
private:
    char ch= 'a';
    int a = 1;
    double d = 2;
    static int si; //必须在类外初始化静态成员变量：因为声明只是描述如何分配内存，但并不分配内存
    static int getval();

public:
    static void f();
    static void g() ;
};

int Application::si = 0; //初始化类的成员变量，这里没有使用staitc


void Application::f()
{
    si = 5;
}

void Application::g()
{
    // cout <<"a = " <<  a << endl; //静态成员函数只能调用 静态成员变量或静态成员函数
    cout << "si = " << si << endl;
}

int main()
{
    Application a;
    cout <<"sizeof(a) = " << sizeof(a) << endl;


    Application::f();
    Application::g();

    return 0;
}