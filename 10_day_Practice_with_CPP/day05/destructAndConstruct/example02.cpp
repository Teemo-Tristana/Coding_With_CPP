#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "Constructing A" << endl;
    }
    ~A()
    {
        cout << "Des A" << endl;
    }
};
class B
{
public:
    B()
    {
        cout << "Constructing B" << endl;
    }
    ~B()
    {
        cout << "Des B " << endl;
    }
};

class C
{
public:
    C()
    {
        cout << "Constructing C" << endl;
    }
    ~C()
    {
        cout << "Des C" << endl;
    }
    B b;
    A a;
};

int main()
{
    C c;

}
// 构造 b -> a -> c
// 析构 c -> a -> b