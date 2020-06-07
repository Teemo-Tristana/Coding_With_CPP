#include <iostream>
using namespace std;

class Time
{
private:
    int Hour, Min, Sec;

public:
    Time(int h = 0, int m = 0, int s = 0) : Hour(h), Min(m), Sec(s)
    {
    }

    void operator()(int h, int m, int s) //重载()符号
    {
        Hour = h;
        Min = m;
        Sec = s;
    }

    void operator++() //重载++符号
    {
        ++Sec;
        if(Sec == 60)
        {
            Sec = 0;
            ++Min;
        }
        if (Min == 60)
        {
            Min = 0;
            Hour++;
        }

        if (Hour == 24)
        {
            Hour = 0;
        }
    }
    
    void ShowTime() const{
        cout <<"time = " << Hour <<" : " << Min <<" : " << Sec << endl;
    }

    void ShowTime()
    {
        cout << "Hour    : " << Hour << endl;
        cout << "Minutes : " << Min<< endl;
        cout << "Second  : " << Sec << endl;
        cout << "-----------------------------------" << endl;
    }
};

int main()
{
    Time t1(1, 2, 3);
    t1.ShowTime();
    t1.operator()(10 ,20 ,30);
    t1.ShowTime();

    Time t2(21, 59, 59);
    ++t2;
    t2.ShowTime();


    return 0;
}