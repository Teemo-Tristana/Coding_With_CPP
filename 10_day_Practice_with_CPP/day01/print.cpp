#include <iostream>

/*  
    练习CPP 输出
*/

using namespace std;

int main()
{
    int i = 0, j = 0, k = 0;
    for(i = 1; i <= 4; ++i)
    {
        for (j = 1; j<=30; ++j)
            cout <<" ";

        for (k = 1; k <= 8 * 2; ++k)
            cout << " ";

        for (k= 1; k <= 2* i; ++k)
        cout <<"*";
    }

    for (i = 1; i <= 3; ++i)
    {
        for(j = 1; j <= 30; ++j)
            cout <<" ";
        for(int f = 1; f <= 7 *- 2*i; ++f)
            cout <<"*";
        cout << endl;
    }

    system("pause");
    return 0;
}