#ifndef VECTOR_H_
#define VECTOR_H_

#include <initializer_list>

#include "iterator.h"
#include "memory.h"
#include "util.h"
#include "exceptdef.h"

namespace mystl
{
#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif

    template <class T>
    class vector
    {
    public:
        typedef mystl::allocator<T> allocator_type;
        typedef mystl::allocator<T> data_allocator;

        typedef typename allocator_type::value_type value_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef value_type *iterator;
        typedef const value_type *const_iterator;
        typedef mystl::reverse_iterator<iterator> reverse_iterator;
        typedef mystl::reverse_iterator<const_iterator> const_reverse_iterator;

        allocator_type get_allocator() { return data_allocator(); }

    private:
        iterator _begin;
        iterator _size;
        iterator _capacity;

    public:
        vector() noexcept{
            try_init();
        }
        
        explicit vector(size_t n)
        {
            fill_init(n, value_type());
        }

        vector(size_type n, const value_type& value)
        {
            fill_init(n, value);
        }

        template<class Iter, typename std::enable_if<mystl::is_input_iterator<Iter>::value, int>::type =0>
        vector(Iter first, Iter last)
        {
            MYSTL_DEBUG(!(last < first));
            range_init(first, last);
        }

        vector(const vector& rhs)
        {
            range_init(rhs._begin, rhs._size);
        }

        vector(vector&& rhs) noexcept: _begin(rhs._begin), _size(rhs._size), _capacity(_capacity)
        {
            rhs._begin = nullptr;
            rhs._size = nullptr;
            rhs._capacity = nullptr;
        }

        vector(<std::initializer_list<value_type> ilist)
        {
            range_init(ilist.begin(), ilist.end());
        }

        vector& operator=(const vector& rhs);
        vector& operator=(vector&& rhs) noexcept;

        vector& operator=(std::initializer_list<value_type> ilist)
        {
            vector tmp(ilist.begin(), ilist.end());
            swap(tmp);
            return *this;
        }

        ~vector()
        {
            destroy_and_recover(_begin, _size, _capacity - _size);
            _begin = _end = _capacity = nullptr;
        }


        public:
            iterator begin() noexcept
            {
                return _begin;
            }

            const_iterator begin()  const noexcept
            {
                return _begin;
            }

            iterator end() noexcept
            {
                return _size;
            }

            const_iterator end() const noexcept
            {
                return _size;
            }

            
    };
} // namespace mystl

#endif