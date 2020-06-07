#include <iostream>
using namespace std;

int f(int, int);

int main()
{
    int n = 0;
    int k = 0;
    cout << " enter k , n :\n";
    cin >> n;
    cin >> k;
    cout << f(k, n) << endl;

    return 0;
}

int f(int n, int k)
{
    cout << "n = " << n << ", k = " << k << endl;
    if ((n == k) || (k == 0))
    {
        return 1;
    }
    else
    {
        return f(n - 1, k - 1) + f(n - 1, k);
    }
}