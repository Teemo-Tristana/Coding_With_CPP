#include <iostream>
#include <memory>

using namespace std;

void process(shared_ptr<int> ptr){
    //使用 ptr
}//ptr离开作用域，ptr 被销毁

// 12.10 
// 正确
void test_12_10(){

     //用常规指针显示初始化智能指针
    shared_ptr<int> p(new int(1024)); 

    // process参数是值传递， ptr 会先拷贝一份，在离开作用后 ptr 被销毁
    // 被传入的智能指针对象仍然存在
    process(p);
}

// 12.11
// p 将成为一个悬空指针
void test_12_11(){
    shared_ptr<int> p(new int(1024)); 

    // 传递给 process 的是由 get() 初始化的一个临时 shared_ptr
    // 与 p 指向同一个对象，由于是使用 get() 方法获取，该对象的引用计数仍然为 1
    // 待离开 process 后，ptr 被销毁，也即是 p 指向的对于也被释放[两者指向同一个对象]
    // 因此 p 也就成为了一个 悬空指针
    process(shared_ptr<int>(p.get()));
}

// 12.12 
void test_12_12(){
    auto p = new int();
    auto sp = make_shared<int>();

    process(sp); // 合法, 将一个shared_ptr传给process,发生的是值拷贝。
    
    process(new int()); // 不合法， 内置指针不能隐式地转为智能指针,改正如下
    // process(shared_ptr<int>(new int()));

    process(p);// 不合法。 内置指针不能隐式地转为智能指针, 改正如下
    // auto tempSp = make_shared<int>(p);
    // process(tempSp);

    // 合法，但是不建议这样做，常规指针和智能指针的混用可能导致二次释放
    // 因此，此时创建的零时指针指针和p指向同一块内存，其引用计数为 1
    // 离开process 时，引用计数变为 0 , 所指向的内存被释放，
    // 若在使用 p 或 释放 p ,则导致非法访问或二次释放等问题
    process(shared_ptr<int>(p)); 
}

// 12.13
// sp 是一个 shared_ptr 智能指针， p 是 sp 的 get() 返回的一个常规指针， p 和 sp 指向同一块内存
// 这里 delete p 后，在 离开作用域后 sp 会自动释放，则会出现对同一块内存两次释放即二次释放的问题。
void test_12_13(){
    auto sp = make_shared<int>();
    auto p = sp.get(); 
    delete p; //会导致二次释放
}