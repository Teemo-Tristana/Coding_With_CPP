#include <iostream>
using namespace std;

class A
{
private:
    int i;

protected:
    int j;

public:
    int k;
};

//公有继承
class B : public A
{
    void f()
    {
        // i = 1; //公有继承,不能访问基类的priavate成员
        j = 2; //公有继承,可以访问基类的protected成员
        k = 3; //公有继承,可以访问基类的public成员
    }
};

int main()
{
    B b;
    // 对象不能访问private 和 protected成员
    // b.i = 1;
    // b.j = 2;
    b.k = 3;

    return 0;
}