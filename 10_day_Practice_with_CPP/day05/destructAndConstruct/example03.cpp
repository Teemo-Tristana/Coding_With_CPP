//没有构造函数的类[默认构造函数]
#include <iostream>
using namespace std;
class A
{
public:
    A() { cout << "Constructing A" << endl; }
    ~A() { cout << "Destructing A" << endl; }
};
class B : public A
{
public:
    // B() { cout << "Constructing B" << endl; }
    ~B() { cout << "Destructing B" << endl; }
};

int main()
{
    B b;
    return 0;
}