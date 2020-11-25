/**
 *  用于 stl 的基本算法
*/

#ifndef MYTINYSTL_ALGOBASE_H_
#define MYTINYSTL_ALGOBASE_H_

#include "iterator.h"
#include "util.h"

namespace
{
#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("undefing marco min")
#undef min
#endif // min

    // max
    template <class T>
    const T &max(const T &lhs, const T &rhs)
    {
        return lhs < rhs ? rhs : lhs;
    }


    // min 
    template<class T, class Compare>
    const T& min(const T& lhs, const T &rhs, Compare comp)
    {
        return comp(rhs, lhs)? rhs : lhs;
    }

    template<class Iter1, class Iter2>
    void iter_swap(Iter1 lhs, Iter2 rhs)
    {
        mystl::swap(lhs, rhs);
    }

    //范围内的拷贝, 未作检查，不安全
    template<class Input, class Outpt>
    Outpt unckecked_copy_at(Input first, Input last, Outpt result, mystl::input_iterator_tag)
    {
        for(;first != last; ++first; ++result)
        {
            *result = *first;
        }
        return result;
    }


} // namespace

#endif