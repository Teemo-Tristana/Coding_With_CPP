#include <iostream>

using namespace std;

/*
静态变量从 作用域， 寿命 ，以及初始化 等几个方面来理解
1.作用域无非 全局作用域， 局部作用域
2.寿命一般是整个运行期键存在，但是否可以使用，则要看其作用域， 
    全局作用域的话，可以直接使用
    局部作用域的话，只能在对局的作用域可用，做超过该局部作用域时，它并不销毁，再次回到该作用域时，又可以直接使用
3.静态变量只会被初始化一次，为指定的话会自动初始化为对于的类型，比如 int 为0 

*/
int i = 1; //i 是全局变量，具有静态生存周期


int main()
{
    static int a ;//静态局部变量，局部可见，全局寿命， 为被初始化时，会自动被初始化为0，只初始化一次
    int b = 10; //b, c局部变量，具有动态生存周期
    int c= 0 ;
    void other(void);
  
    other();
    cout <<"-------main-----------\n";
    cout <<"i = " << i <<", a = " << a <<", b = " << b <<", c = " << c << endl;
    c = c + 8;
    other();
    cout <<"i = " << i <<", a = " << a <<", b = " << b <<", c = " << c << endl;
    i += 10;
    other();

    return 0;
}

void other(void)
{
    static int a = 2; 
    static int b; //a, b局部静态变量，局部可见， 具有全局寿命， 只被初始化一次， static 变量只能在声明的文件中使用，若要跨文件，使用extern 
    int c = 10;
    a = a + 2;
    i += 2;
    c = c+ 5;
    cout <<"-------other----------\n";
    cout <<"i = " << i <<", a = " << a <<", b = " << b << ", c = " << c << endl;
     cout <<"-------other----------\n";
}