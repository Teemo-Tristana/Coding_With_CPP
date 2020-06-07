
#include "clock.h"

#include <iostream>
using namespace std;

Clock::Clock(int newH, int NewM, int NewS)
{
    this->Hour = newH;
    this->Minute = NewM;
    this->Second = NewS;
}

Clock::Clock(Clock &c)
{
    Hour = c.Hour;
    Minute = c.Minute;
    Second = c.Second;
}

void Clock::SetTime(int H, int M, int S)
{
    this->Hour = H;
    this->Minute = M;
    this->Second = S;
}

void Clock::ShowTime()
{
    cout << "Hour    : " << Hour << endl;
    cout << "Minutes : "  << Minute << endl;
    cout << "Second  : " << Second << endl;
    cout <<"-----------------------------------" << endl;
}

Clock::~Clock()
{

}

int main()
{
    Clock c(0, 0, 0);
    c.SetTime(10, 20, 30);
    Clock c1(c);
    c1.ShowTime();
    
    c1.SetTime(50 ,60 ,70);
    c1.ShowTime();

    return 0;
}