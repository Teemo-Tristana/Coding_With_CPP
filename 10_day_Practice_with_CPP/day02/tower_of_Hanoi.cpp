#include <iostream>
using namespace std;

void move(char A, char B);
void Hanoi(int n , char A, char B ,char C);

int main()
{
    int disks = 0;
    cout <<"disk = ";
    cin >> disks;
    Hanoi(disks, 'A', 'B', 'C');

    return 0;
}

void move(char A, char B)
{
    cout << A <<" -> " << B << endl;
}

void Hanoi(int n, char A, char B, char C)
{
    if (n == 1)
    {
        move(A, C);
    }
    else
    {
        Hanoi(n-1, A, C, B);
        move(A,C);
        Hanoi(n-1, B, A, C);
    }
}