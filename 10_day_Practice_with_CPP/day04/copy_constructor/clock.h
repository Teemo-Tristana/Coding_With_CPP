#ifndef CLOCK_H_
#define CLOCK_H_

class Clock{
    private:
        int Hour, Minute, Second;
    public:
        Clock(int newH, int NewM, int NewS);
        //拷贝构造函数,如果不加，编译器会自动生成一个拷贝构造函数，因此加不加都可以直接使用。
        Clock(Clock& c); //拷贝构造
        void SetTime(int H, int M,int S);
        void ShowTime();
        ~Clock();
};

#endif