#include <iostream>
#include <memory>
#include <vector>
#include <string>


using namespace std;

// 12_16
void test_12_16(){
    unique_ptr<int> p1(new int(1024));
// use of deleted function 'std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&)
// [with _Tp = int; _Dp = std::default_delete<int>]'
// 大致意思: 对 unique_ptr() 使用了拷贝 ？
    unique_ptr<int> p2(p1); // ❌

// use of deleted function 'std::unique_ptr<_Tp, _Dp>& std::unique_ptr<_Tp, _Dp>::operator=(const std::unique_ptr<_Tp, _Dp>&) 
// [with _Tp = int; _Dp = std::default_delete<int>]'
// 大致意思: 对 unique_ptr() 使用了赋值 = ？
    unique_ptr<int> p3 ; // ❌
    p3 = p1;
}


// 12_17
void test_12_17(){
    int ix = 1024, *pi = &ix, *pi2 = new int(2048);
    typedef unique_ptr<int> IntP;

    // a 
    IntP p0(ix);  // 不合法，将一个整数赋给一个智能指针， unique_ptr 只能绑定 new 返回的指针
    
    // b
    IntP p1(pi); // 编译不报错，但是 不合法， 智能指针默认分配的是动态空间, 超过其作用域时会调用 
    // delete 释放空间，但这里 pi 不是 new 分配的动态空间，因此不能使用 delete去释放。在运行时可能会报错。

    // c
    IntP p2(pi2); // 合法

    // d
    IntP p3(&ix); // 和 b 一样。编译不报错，但无法用delete释放

    // e 
    IntP p4(new int(2048)); // 合法

    // f 
    IntP p5(p2.get()); // 不合法， 使用 get() 方法获取返回指针，此时 p5 和 p2 指向同一块内存，
    //  unique_ptr是基于所有权默认的，任意时刻只能有一个拥有者，而且若智能指针释放，则导致二次释放。


}



// 12_18 shared_ptr 为什么没有 release() 成员？
/**
 * release() 返回一个指向被管理对象的指针，并释放所有权
 * 但 shared_ptr 使基于计数器模式， 可以多对一。 一个 shared_ptr 交出所有权，但是共享此对象的 shared_ptr 
 * 仍然可以控制该对象，因此 release() 对 shared_ptr 是没有意义的。
*/
int main(){
    test_12_16();


    return 0;
}