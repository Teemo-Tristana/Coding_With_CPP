#include <iostream>

using namespace std;

class Base
{
private:
    int b;

public:
    Base(int _x = 0) : b(_x)
    {
        cout << "Base Constructor\n";
    }

    ~Base()
    {
        cout << "Des Base \n";
    }
};

class Derived : public Base
{
private:
    int d;

public:
    Derived(int x, int y) : Base(x), d(y)
    {
        cout << "Derived Constructor\n";
    }

    ~Derived()
    {
        cout << "Des Derived\n";
    }
};

int main()
{
    Derived d(1, 2);

    return 0;
}