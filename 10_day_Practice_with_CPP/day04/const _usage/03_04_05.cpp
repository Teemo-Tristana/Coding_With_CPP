#include <iostream>

using namespace std;

class R{
    private:
        int r1, r2;
    public:
        R(int x1, int x2): r1(x1), r2(x2){}
        void print();
        void print() const; //常成员函数
};

/*
常成员函数： 类型说明符 函数名 参数列表 const; 
    这里的const是该常成员函数的一部分’
    这里的const可以用于区分重载
    常成员函数，对成员变量只读
    通过常对象只能调用它的常成员函数
*/

void R::print()
{
    cout <<"common function" << endl;
    cout << r1 <<" : " << r2 << endl;
}

void R::print() const
{
    cout <<"const function\n";
    cout << r1 <<" | " << r2 << endl;
}

int main()
{   
    R a(5,4);
    a.print();  //调用void print()
    //通过常对象只能调用它的常成员函数
    const R b(20,52);  
    b.print();  //调用void print() const
    system("pause");
    return 0;
}