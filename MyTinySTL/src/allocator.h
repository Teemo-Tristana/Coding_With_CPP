/**
 * 空间配置器分配两级，
 *      第一级是 allocate.h, 一般是对 malloc 的一层封装，没有考虑内存碎片化的问题，在大量申请小空间的内存块内存碎片严重时，导致空闲内存无法充分利用。
*/

#ifndef MTTINYSTL_ALLOCATOR_H_
#define MTTINYSTL_ALLOCATOR_H_

#include "util.h"
#include "construct.h"

namespace mystl
{

    template <class T>
    class allocator
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
        static T *allocate();
        static T *allocate(size_type n);

        static void deallocate(T *ptr);
        static void deallocate(T *ptr, size_type n);

        static void construct(T *ptr);
        static void construct(T *ptr, const T &value);
        static void construct(T *ptr, T &&value);

        template <class... Args>
        static void construct(T *ptr, Args &&... args);

        static void destroy(T *ptr);
        static void destroy(T *first, T *last);
    };

    template <class T>
    T *allocator<T>::allocate()
    {
        return static_cast<T *>(::operator new(sizeof(T)));
    }

    template <class T>
    T *allocator<T>::allocate(size_type n)
    {
        if (0 == n)
            return nullptr;
        return static_cast<T *>(::operator new(n * sizeof(T)));
    }

    template <class T>
    void allocator<T>::deallocate(T *ptr)
    {
        if (nullptr == ptr)
            return;
        ::operator delete(ptr);
    }

    template <class T>
    void allocator<T>::deallocate(T *ptr, size_type n)
    {
        if (nullptr == ptr)
            return;
        ::operator delete(ptr);
    }

    template <class T>
    void allocator<T>::construct(T *ptr)
    {
        mystl::contruct(ptr);
    }

    template <class T>
    void allocator<T>::construct(T *ptr, const T &value)
    {
        mystl::construct(ptr, value);
    }

    template <class T>
    void allocator<T>::construct(T *ptr, T &&value)
    {
        mystl::construct(ptr, mystl::move(value);)
    }

    template <class T>
    template <class... Args>
    void allocator<T>::construct(T *ptr, Args &&... args)
    {
        mystl::construct(ptr, mystl::forward<Args>(args)...);
    }

    template <class T>
    void allocator<T>::destroy(T *ptr)
    {
        mystl::destory(ptr);
    }

    template <class T>
    void allocator<T>::destroy(T *first, T *last)
    {
        mystl::destory(first, last);
    }

} // namespace mystl

#endif