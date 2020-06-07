#include <iostream>
using namespace std;

class A
{
private:
    int a;

public:
    void SetA(int x) { a = x; }
    int getA() const { return a; }
};

class B : public A
{
private:
    int b;

public:
    void setB(int x) { b = x; }
    int getB() const { return b; }
};

void f1(A a, int x)
{
    a.SetA(x);
}

void f2(A *Pa, int x)
{
    Pa->SetA(x);
}

void f3(A &a, int x)
{
    a.SetA(x);
}

int main()
{
    A a1, *pa;
    B b1, *pb;
    a1.SetA(1);
    b1.SetA(20);

    a1 = b1; //1.派生类对象赋给基类
    cout << a1.getA() << endl;
    cout << b1.getA() << endl;

    a1.SetA(100);
    cout << a1.getA() << endl;
    cout << b1.getA() << endl;

    pa = &b1; //2. 派生类地址赋给积基类指针
    pa->SetA(100);
    cout << pa->getA() << endl;
    cout << b1.getA() << endl;

    A &ra = b1; //3. 用派生类对象初始化基类引用
    ra.SetA(300);
    cout << pa->getA() << endl;
    cout << b1.getA() << endl;

    b1.SetA(7);
    cout << b1.getA() << endl;
    f1(b1, 100);
    cout << b1.getA() << endl;
    f2(&b1, 200);
    cout << b1.getA() << endl;
    f3(b1, 300);
    cout << b1.getA() << endl;

    return 0;
}