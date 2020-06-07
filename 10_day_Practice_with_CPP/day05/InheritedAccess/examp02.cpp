#include <iostream>
using namespace std;

class Base
{
    int x;

protected:
    int getX()
    {
        return x;
    }

public:
    void setX(int n) { x = n; }
    void showX() { cout << "x : " << x << endl; }
};

class Derived:protected Base
{
    private :
    int y;
    public:
        void setY(int n){y = n;}
        void sety() { y =getX();}
        void show() {cout <<"y = " << y << endl;}
};

/*
保护继承:
    保护继承是的public变为protected, 原来的private 和 protected
    不变
    而portected成员,可以在派生类中访问,但派生类对象不能使用
*/

int main()
{
    Derived obj;
    // obj.setX(10); //error
    obj.setY(20);
    // obj.showX(); // error
    obj.show();
    
    return 0;
}