#include <iostream>
using namespace std;

/*  inline 内联函数 ： 内联函数在实现时需要和函数体放在一起才能成为内联，只将inline 放在声明时不会起作用
    在函数前加 inline 关键字，显示声明该该函数为内联函数
    inline 函数 | 宏 | 普通函数
        使用内联函数，而是直接在该处展开， 宏定义的也是直接在调用处直接展开， 普通函数需要跳转
        内联函数相比宏而言，内联函数需要做参数类型检查，因此相对而言更为安全
        内联函数在允许时，可以调试，宏不可以[在编译阶段就直接进行替换了]
        普通函数在执行时会跳转到该函数，执行后在返回或结束

    
 */
inline double CalArea(double radius);

#define add(x, y) (x + y)
inline int jia(int, int);

int main()
{
    double r = 3.0;
    double area = 0.0;

    int x = 1;
    int y = 99;
    int res1 = add(x, y);
    int res2 = jia(x, y);

    cout << res1 << endl;
    cout << res2 << endl;

    area = CalArea(r);
    cout << "area = " << area << endl;

    return 0;
}

inline int jia(int x, int y)
{
    cout << "plus";
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    return x + y;
}

inline double CalArea(double radius)
{
    return 3.14 * radius * radius;
}