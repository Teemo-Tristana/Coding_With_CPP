/*
一圆型游泳池如图所示，现在需在其周围建一圆型过道，并在其四周围上栅栏。栅栏价格为35元/米，过道造价为20元/平方米。
过道宽度为3米，游泳池半径由键盘输入。要求编程计算并输出过道和栅栏的造价。
图形描述：大圆嵌套小圆：
小圆在大圆中间，小圆为游泳池，大圆与小圆间隔为过道。
*/

#include <iostream>
using namespace std;

const float PI = 3.1416925f;
const float FencePrice = 35.0f;
const float ConcretePrice = 20.0f;

/*  编译器会自动给每一个非静态成员函数加一个this指针
    成员函数 前面使用const | 后面使用const：
        前面使用const ： 表示返回值是const ： 
            eg: const int getValue()
        后面使用const ： 该函数不可修改class的成员 ：其实是修饰this指针，形式为： pointer to const object
        修饰成员函数本质上就是修饰“this”指针，所以不能修改函数内部的成员变量
            eg: int getValue() const;

    
*/
class Circle
{
private:
    float radius;

public:
    Circle(float r) : radius(r){};
    float Circumferen() const;
    float Area() const;
};

float Circle::Circumferen() const
{
    return 2 * PI * radius;
}

float Circle::Area() const
{
    return 2 * radius * radius;
}

int main()
{
    float radius = 0.0f;  //c++ 浮点数默认是double, 我们这里在后面+f，指定类型是f
    float fenceCost = 0.0f, ConcreteCost = 0.0f;

    cout << "Enter the radius of the poll : ";
    cin >> radius;

    Circle Pool(radius);
    Circle PoolRim(radius + 3);
    fenceCost = PoolRim.Circumferen() * FencePrice;
    cout << "Fenceing Cost is $:" << fenceCost << endl;


      //  计算过道造价并输出
    ConcreteCost = (PoolRim.Area() - Pool.Area())*ConcretePrice;
    cout << "Concrete Cost is $" << ConcreteCost << endl;
    return 0;
}