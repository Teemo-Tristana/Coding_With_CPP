#include <iostream>

using namespace std;

int main()
{
    int year = 0;
    bool isLeapYear = false;
    cout << "Enter the year : ";
    cin >> year;
    //闰年： 整除400 || 整数4 但不整除100
    isLeapYear = ((0 == year % 400) || (0 == year % 4) && (0 != year % 100));
    if (isLeapYear)
    {
        cout << year << " is a leap year\n";
    }
    else
    {
        cout << year << " is not a leap year" << endl;
    }

    system("pause");
    return 0;
}