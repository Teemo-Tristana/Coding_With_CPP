#include <iostream>

using namespace std;

/*
Union 是不同的类型的变量占用同一段内存，以最大的为Union的大小
Union可用于大小端

struct 是一种构造数据类型，把不同数据类型组合在一起

在Union和struct 需要主要 内存对齐的问题

*/
union myUnion
{
    char c;
    int i;
    float f;
    double d;
    struct{
        char ch;
        int ni;
        float ft;
        double de;
    }st;
}Un;



int main()
{
    Un.st.ch = 'c';
    Un.st.ni = 1;
    Un.st.ft = 2.1;
    Un.st.de = 3.2; 

    cout << "sizeof(char) = " << sizeof(char) << endl;
    cout << "sizeof(int) = " << sizeof(int) << endl;
    cout << "sizeof(float) = " << sizeof(float) << endl;
    cout << "sizeof(double) = " << sizeof(double) << endl;
    
    /*
        这里ch 1  ni 4 fl 4 de 8
        ch先与 ni 对齐， 因此1-> 4  4 + 4 = 8
        fl 需要与de对齐 4 -> 8 
        最后 8 + 8 + 8 = 24
        注意：不同的电脑类型可能不同
    */
    cout << sizeof(Un) << endl;  
    return 0;
}