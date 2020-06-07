#include <iostream>
using namespace std;

void swap(int &, int &);

int main()
{
    int x = 5;
    int y = 10;
    cout << "x = " << x << ", y = " << y << endl;
    swap(x, y);

    cout << "x = " << x << ", y = " << y << endl;

    return 0;
}

void swap(int &a, int &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a^ b;
}