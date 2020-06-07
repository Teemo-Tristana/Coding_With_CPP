#include <iostream>
using namespace std;

enum Weekday{
    s, m, t, w, thu, f, s1
};

int main()
{
    enum Weekday week = s;
    for (int i = week; i != f; ++i)
    {
        cout << i << endl;
        cout << week + i << endl;
        cout <<"-------------------" << endl;
    }
}