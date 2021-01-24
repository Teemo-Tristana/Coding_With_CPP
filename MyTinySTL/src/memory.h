/*
 * @Author: your name
 * @Date: 2020-11-25 22:28:11
 * @LastEditTime: 2020-12-08 21:41:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MyTinySTL\src\memory.h
 */
#ifndef MYTINYSTL_MEMORY_H_
#define MYTINYSTL_MEMORY_H_

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "algobase.h"
#include "allocator.h"
#include "construct.h"
#include "uninitialied.h"


namespace mystl
{
    // 获取对象地址
    template <class T>
    constexpr T *address_of(T &value) noexcept
    {
        return &value;
    }

    // 申请空间
    template<class T>
    pair<T*, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T*)
    {
        if (len  > static_cast<ptrdiff_t>(INT_MAX/sizeof(T)))
            len = INT_MAX / sizeof(T);
        
        while (len > 0)
        {
            T* tmp = static_cast<T*>(malloc(static_cast<size_t>(len)*sizeof(T)));
            if (tmp)
                return pair<T*, ptrdiff_t>(nullptr, 0);
            len >>= 1;
        }
        return pair<T*, ptrdiff_t>(nullptr, 0);
    }

    // 获取临时空间
    template<class T>
    pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len)
    {
        return get_buffer_helper(len, static_cast<T*>(0));
    }

    // 释放 ptr 指向的内存空间
    template<class T>
    void release_temporary_buffer(T* ptr)
    {
        free(ptr);
    }

    template<class ForwardIterator, class T>
    class temporary_buffer{
        private:
            ptrdiff_t capacity;
            ptrdiff_t len;
            T* buffer;
        
        public:
            temporary_buffer(ForwardIterator first, ForwardIterator last);
            ~temporary_buffer()
            {
                mystl::destory(buffer, buffer+len);
                free(buffer);
            }

        public:
            ptrdiff_t size() const noexcept {
                return len;
            }

            ptrdiff_t requested_size() const noexcept
            {
                return capacity;
            }

            T* begin() noexcept {
                return buffer;
            }

            T* end() noexcept
            {
                return buffer+len;
            }

        private:
            void allocate_buffer();
            void initialize_buffer(const T&, std::true_type){}
            void initialize_buffer(const T& value, std::false_type)
            {
                mystl::uninitialized_fill_n(buffer, len, value);
            }

            temporary_buffer(const temporary_buffer&);
            void operator=(const temporary_buffer&);
    };

    template<class ForwardIterator, class T>
    temporary_buffer<ForwardIterator, T>::temporary_buffer(ForwardIterator first, ForwardIterator last)
    {
        try 
        {
            len = mystl::distance(first, len);
            allocate_buffer();
            if (len > 0)
            {
                initialize_buffer(*first, std::is_trivially_default_constructible<T>());
            }
        }
        catch(...)
        {
            free(buffer);
            buffer = nullptr;
            len = 0;
        }
    }


    // allocate_buffer 函数
    template <class ForwardIterator, class T>
    void temporary_buffer<ForwardIterator, T>::allocate_buffer()
    {
        original_len = len;
        if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T)))
            len = INT_MAX / sizeof(T);
        while (len > 0)
        {
            buffer = static_cast<T*>(malloc(len * sizeof(T)));
            if (buffer)
                break;
            len /= 2;  // 申请失败时减少申请空间大小
        }
    }



    template<class T>
    class auto_ptr
    {
        public:
            typedef T elem_type;
        
        private:
            T* my_ptr;
        
        public:
            explicit auto_ptr(T*p = nullptr): my_ptr(p){}
            auto_ptr(auto_ptr& rhs): my_ptr(rhs.release()){}

            template<class U>
            auto_ptr(auto_ptr<U>& rhs): my_ptr(rhs.release()){}

            auto_ptr& operator=(auto_ptr& rhs)
            {
                if (this != &rhs)
                {
                    delete my_ptr;
                    my_ptr = rhs.relase();
                }
                return *this;
            }

            ~auto_ptr()
            {
                delete my_ptr;
                my_ptr=nullptr;
            }

        T& operator*() const{
            return *my_ptr;
        }

        T* operator->() const 
        {
            return my_ptr;
        }

        T* release()
        {
            T* tmp = my_ptr;
            my_ptr = nullptr;
            return tmp;
        }

        void reset(T* p = nullptr)
        {
            if (my_ptr != p)
            {
                delete my_ptr;
                my_ptr = p;
            }
        }
    };
}

#endif