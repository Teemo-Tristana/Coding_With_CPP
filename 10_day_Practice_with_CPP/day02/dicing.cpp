#include <iostream>
#include <cstdlib>
using namespace std;

int rolldice();

int main()
{
    int flag = 0;
    unsigned seed;
    cout << "enter seed =  ";
    cin >> seed;

    srand(seed);
    int sum = rolldice();
    int selfdim;

    switch (sum)
    {
    case 7:
    case 11:
        flag = 1;
        break;

    case 2:
    case 3:
    case 12:
        flag = 2;
        break;

    default:
        flag = 0;
        selfdim = sum;
        break;
    }

    while (flag == 0)
    {
        sum = rolldice();
        if (sum == selfdim)
        {
            flag = 1;
        }
        else if (7 == sum)
        {
            flag = 2 ;
        }
    }

    if (1 == flag)
    {
        cout<< "Player Win \n";
    }
    else 
    {
        cout << "Player lose\n";
    }
}

int rolldice()
{
    int sum = 0;
    int dim1 = rand() % 6  + 1;
    int dim2 = rand() % 6 + 1; //0~ 5 + 1 = 1 ~ 6
    sum = dim1 + dim2;
    cout <<"sum = " << dim1 <<" + " << dim2 << endl;
    return sum;
}