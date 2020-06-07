#include <iostream>
using namespace std;

int f(int);

int main()
{
    int x= 0;
    cout <<" enter x = ";
    cin >> x;
    cout << f(x) << endl;
}


int f(int n)
{
    cout <<"n = " << n << endl;
    if (0 == n)
    {
        return 1;
    }
    else
    {
        return n * f(n-1);
    }
    
}