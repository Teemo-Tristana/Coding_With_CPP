
/**
 * 本文件是构造函数和析构函数中组成
 * construct(),构造函数，负责构造对象
 * destroy()，析构函数，负责将对象析构
*/

#ifndef MYTINYSTL_CONSTRUCT_H_
#define MYTINYSTL_CONSTRUCT_H_

#include <new>

#include "type_traits.h"
#include "iterator.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100) // unused parameter
#endif                          // _MSC_VER

namespace stl
{
    // 构造函数
    template <class T>
    void construct(T *ptr)
    {
        ::new ((void *)ptr) T();
    }

    template <class T1, class T2>
    void construct(T1 *ptr, const T2 &value)
    {
        ::new ((void *)ptr) T1(value);
    }

    template <class Ty, class... Args>
    void construct(Ty *ptr, Args &&... args)
    {
        ::new ((void *)ptr) Ty(mystl::forward<Args>(args)...);
    }

    // 不同析构函数版本
    template <class T1>
    void destory_one(T1, std::true_type) {}

    template <class T1>
    void destory_one(T1 *pointer, std::false_type)
    {
        if (nullptr != pointer)
        {
            pointer->~T1();
        }
    }

    template <class ForwardIter>
    void destory_cat(ForwardIter, ForwardIter, std::true_type) {}

    template <class ForwardIter>
    void destory_cat(ForwardIter first, ForwardIter last, std::false_type)
    {
        for (; first != last; ++first)
            destory(&*first);
    }


    // 析构函数版本
    template <class T>
    void destory(T *pointer)
    {
        destory_one(pointer, std::is_trivially_destructible<T>{});
    }

    template <class ForwardIter>
    void destory(ForwardIter first, ForwardIter last)
    {
        destory_cat(first, last, std::is_trivially_destructible<typename iterator_traits<ForwardIter>::value_type>{});
    }

} // namespace stl

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif