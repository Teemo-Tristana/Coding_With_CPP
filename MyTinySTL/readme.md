# MyTinySTL
基于C++11实现的tinySTL，用于学习C++和STL
STL 由容器、算法、迭代器、适配器、内存分配器、仿函数六部分构造，后面四部分主要为前面两部分服务
## 容器
### 序列容器
### 关联容器

## 算法

## 迭代器
### 基本迭代器
## 适配器

## 内存分配器
#### 两级空间配置器

## 仿函数


## type_traits
type_traits 称为类型萃取技术， 用途如下：
1. 获取编译期参数/变量/类等C++相关对象的类型
2. 判断参数类型、两个变量是否是同一类型、是否是标量、是否是引用、是否是指针、是左值or右值等
3. 为变量去掉或增加cv(const volitale)属性。


type_traits是编译期就去确定具体的类型，从而根据不同的类型来执行不同的模块，消除重复，提高代码质量。

traits是c++模板编程中使用的一种技术，主要功能： 
    把功能相同而参数不同的函数抽象出来，通过traits将不同的参数的相同属性提取出来，在函数中利用这些用traits提取的属性，使得函数对不同的参数表现一致。


traits是一种特性萃取技术,它在Generic Programming中被广泛运用,常常被用于使不同的类型可以用于相同的操作,或者针对不同类型提供不同的实现.traits在实现过程中往往需要用到以下三种C++的基本特性: enum、typedef、template (partial) specialization
+ enum用于将在不同类型间变化的标示统一成一个,它在C++中常常被用于在类中替代define,你可以称enum为类中的define
+ typedef则用于定义你的模板类支持特性的形式,你的模板类必须以某种形式支持某一特性,否则类型萃取器traits将无法正常工作 
+ template (partial) specialization被用于提供针对特定类型的正确的或更合适的版本

## SFINAE(Substitution Failure is Not An Error)
在编译期间，将函数模板的形参替换为实参，如果替换失败，编译器不会视其为错误，直到找到最合适的特化版本，若所有模板版本都替换失败，此时编译器才会报错。

## 文件说明
util.h 主要实现 move()、forward()、swap()、pair以及重载比较运算符
type_traits.h 用到C++的type_traits技术(类型萃取技术)，用于萃取类型信息
allocator.h 第一级空间分配器
alloc.h 第二级空间分配器，采用内存池实现，主要争对小内存内存分配和回收


