/*
    常量指针 ： 只能读取所指内存中的数据不能修改（指向常量的指针）: 内存中的内容是一个常量，不可以该
        const int *p | int const *p

    指针常量 ： 指向的位置不能改变，即指针本身是一个常量，但是所指向内存的数据是可以修改的 ： 指针是一个常量，不可改
        int* const p = &a; 
*/

// 常引用与常对象
#include <iostream>
using namespace std;

void display(const double& r);

class A{
    private:
        int x, y;
    public:
        A(int i, int j):x(i), y(j){};
};

int main()
{
    double d = 9.5;
    display(d);
    A const a(3, 5); //a是一个const 对象，不可修改
    
    return 0;
}

//常引用： 常引用作为形参是，在函数中中不能修改所指对象的值 与 常量指针功能类似
void display(const double& r)
{
    cout << "r = " << r << endl;
}