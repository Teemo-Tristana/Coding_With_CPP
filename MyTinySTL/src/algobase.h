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
    template <class T, class Compare>
    const T &min(const T &lhs, const T &rhs, Compare comp)
    {
        return comp(rhs, lhs) ? rhs : lhs;
    }

    template <class Iter1, class Iter2>
    void iter_swap(Iter1 lhs, Iter2 rhs)
    {
        mystl::swap(lhs, rhs);
    }

    //基于范围的拷贝, 未作检查，不安全
    template <class Input, class Outpt>
    Outpt unckecked_copy_at(Input first, Input last, Outpt result, mystl::input_iterator_tag)
    {
        for (; first != last; ++first; ++result)
        {
            *result = *first;
        }
        return result;
    }

    template <class RandomIter, class OutputIter>
    OutputIter
    unckecked_copy_at(RandomIter first, RandomIter last, OutputIter result, mystl::random_access_iterator_tag)
    {
        for (auto n = last - first; n > 0; --n, ++first, ++result)
        {
            *result = *first;
        }
        return result;
    }

    template <class Input, class Output>
    Output unchecked_copy(Input first, Input last, Output result)
    {
        return unckecked_copy_at(first, last, result, iterator_category(first));
    }

    template <class T, class Up>
    typename std::enable_if<
        std::is_same<typename std::remove_const<T>::type, Up>::value &&
            std::is_trivially_copy_assignable<Up>::value,
        Up *>::type
    unchecked_copy(T *first, T *last, Up *result)
    {
        const auto n = static_cast<size_t>(last - first);
        if (n != 0)
            std::memove(result, first, n * sizeof(Up));
        return result + n;
    }

    template <class Input, class Output>
    Output copy(Input first, Input last, Output result)
    {
        return unchecked_copy(first, last, result);
    }

    template <class BidirectionalIter1, class BidirectionalIter2>
    BidirectionalIter2 unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result, mystl::bidirectional_iterator_tag)
    {

        while (first != last)
        {
            *--result = *--last;
            // *result = *last;
            // --result;
            // --last;
            return result;
        }
    }

    template <class BidirectionalIter1, class BidirectionalIter2>
    BidirectionalIter2 unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result, mystl::random_access_iterator_tag)
    {
        for (auto n = last - first; n > 0; --n)
        {
            *--result = *--last;
        }
        return result;
    }

    template <class BidirectionalIter1, class BidirectionalIter2>
    BidirectionalIter2 unchecked_copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result)
    {
        return unchecked_copy_backward_cat(first, last, result, iterator_category(first));
    }

    template <class T, class U>
    typename std::enable_if<
        std::is_same<typename std::remove_const<T>::type, U>::value &&
            std::is_trivially_copy_assignable<U>::value,
        U *>::type
    unckecked_copy_backward(T *first, T *last, U *result)
    {
        const auto n = static_cast<size_t>(last - first);
        if (0 != n)
        {
            result -= n;
            std::memmove(result, first, n * sizeof(U));
        }

        return result;
    }

} // namespace

#endif