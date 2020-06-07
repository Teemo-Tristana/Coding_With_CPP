#include <iostream>
using namespace std;

class A
{
private:
    int x;

public:
    A(int i = 0) : x(i)
    {
        cout << "A constructor" << endl;
    }

    ~A()
    {
        cout << "Desconstuctor A" << endl;
    }
};

class B
{
private:
    int b;

public:
    B(int i = 0) : b(i)
    {
        cout << "B constructor" << endl;
    }

    ~B()
    {
        cout << "Desconstuctor B" << endl;
    }
};

class C
{
private:
    int c;

public:
    C(int i = 0) : c(i)
    {
        cout << "C constructor" << endl;
    }

    ~C()
    {
        cout << "Desconstuctor C" << endl;
    }
};

class D : public B
{
public:
    C c1, c2;
    A *a1 = new A(100);
    A a0;
    C c3, c4;
    D() : c1(0), c2(1), a0(3), c3(4), c4(5)
    {
        cout << "D constructor" << endl;
    }

    ~D()
    {

        cout << "Desconstuctor D" << endl;
        delete a1;
    }
};

int main()
{
    //成员变量按声明顺序进行初始化
    //先构造基类 -> 然后构造成员变量       ->  最后构造自己
    //先析构自己 -> 在析构成员变量(若是类) ->  最后析构基类
    D d;

    return 0;
}

/*
输出:

B constructor
C constructor
C constructor
A constructor
A constructor
C constructor
C constructor
D constructor
Desconstuctor A
Desconstuctor D
Desconstuctor C
Desconstuctor C
Desconstuctor A
Desconstuctor C
Desconstuctor C
Desconstuctor B

*/