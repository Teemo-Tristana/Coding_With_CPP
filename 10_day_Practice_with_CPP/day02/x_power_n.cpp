#include <iostream>
using namespace std;
double power(double x, int n);

int main()
{
    double x = 0;
    int n = 0;
    cout <<"like 1.0 2\n";
    cin >> x >> n;
    double sum = power(x, n);
    cout << sum << endl;
    system("pause");
    return 0;
}
double power(double x, int n)
{
    double val = 1.0;
    for (int i = n; i != 0; i/= 2)
    {
        if (i % 2 != 0)
            val *= x;

        x *= x;
    }
    return n < 0 ? 1.0/val : val;
}
