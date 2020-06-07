#include <iostream>
using namespace std;
/*
    02. 友元类示例：
        友元类的所有方法都都可以访问原始类的所有私有和保护成员，权限和原始类成员函数一样
        但反之则不行
*/
class A
{
    friend class B; //B是A类的友元类

private:
    int x;

public:
    void Display()
    {
        cout << x << endl;
    }
};

class B
{
private:
    A a;

public:
    void Set(int i);
    void Display();
};

void B::Set(int i)
{
    a.x = i; //访问并设置A类私有成员
}
void B::Display()
{
    a.Display(); //调用A类成员函数
}

int main()
{
    B b;
    b.Set(12);
    b.Display();

    return 0;
}