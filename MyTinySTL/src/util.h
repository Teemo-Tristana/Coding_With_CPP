/**
 * 本文件实现辅助函数
*/

#ifndef MYTINYSTL_UTIL_H_
#define MYTINYSTL_UTIL_H_

#include <cstddef>
#include "type_traits.h"

namespace mystl
{

    //move : move(arg) 负责将表达式 arg 转换为右值，使用这一转换意味着不再关心 arg 的内容，它可以通过被移动（窃取）来解决移动语意问题。
    template <typename T>
    typename std::remove_reference<T>::type &&move(T &&arg) noexcept
    {
        return static_cast<typename std::remove_reference<T>::type &&>(arg);
    }

    /*****************************************************************************************************************************************************************/
    // forward : 用于完美转发
    // 将左值转为左值或右值转发
    template <typename T>
    T &&forward(typename std::remove_reference<T>::type &arg) noexcept
    {
        return static_cast<T &&> arg;
    }

    // 将右值作为右值转发
    template <typename T>
    T &&forward(typename std::remove_reference<T>::type &&arg) noexcept
    {
        static_cast(!std::is_lvalue_reference<T>::value, "bad forward call");
        return static_cast<T &&>(arg);
    }

    /*****************************************************************************************************************************************************************/
    // swap
    template <class T>
    void swap(T &lhs, T &rhs)
    {
        auto tmp{mystl::move(lhs)};
        lhs = mystl::move(rhs);
        rhs = mystl::move(tmp);
    }

    template <class ForwardIter1, class ForwardIter2>
    ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2)
    {
        for (; first1 != last1; ++first1, (void)++first2)
            mystl::swap(*first1, *first2);
        return first2
    }

    template <class T, size_t N>
    void swap(T (&a)[N], T (&b)[N])
    {
        mystl::swap(a, a + N, b);
    }

    /*****************************************************************************************************************************************************************/
    // pair
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;   // 保存第一个数据
        second_type second; // 保存第二个数据

        // default constructiable
        template <class Other1 = T1, class Other2 = T2,
                  typename = typename std::enable_if<
                      std::is_default_constructible<Other1>::value &&
                          std::is_default_constructible<Other2>::value,
                      void>::type>
        constexpr pair()
            : first(), second()
        {
        }

        // implicit constructiable for this type
        template <class U1 = T1, class U2 = T2,
                  typename std::enable_if<
                      std::is_copy_constructible<U1>::value &&
                          std::is_copy_constructible<U2>::value &&
                          std::is_convertible<const U1 &, T1>::value &&
                          std::is_convertible<const U2 &, T2>::value,
                      int>::type = 0>
        constexpr pair(const T1 &a, const T2 &b)
            : first(a), second(b)
        {
        }

        // explicit constructible for this type
        template <class U1 = T1, class U2 = T2,
                  typename std::enable_if<
                      std::is_copy_constructible<U1>::value &&
                          std::is_copy_constructible<U2>::value &&
                          (!std::is_convertible<const U1 &, T1>::value ||
                           !std::is_convertible<const U2 &, T2>::value),
                      int>::type = 0>
        explicit constexpr pair(const T1 &a, const T2 &b)
            : first(a), second(b)
        {
        }

        pair(const pair &rhs) = default;
        pair(pair &&rhs) = default;

        // implicit constructiable for other type
        template <class Other1, class Other2,
                  typename std::enable_if<
                      std::is_constructible<T1, Other1>::value &&
                          std::is_constructible<T2, Other2>::value &&
                          std::is_convertible<Other1 &&, T1>::value &&
                          std::is_convertible<Other2 &&, T2>::value,
                      int>::type = 0>
        constexpr pair(Other1 &&a, Other2 &&b)
            : first(mystl::forward<Other1>(a)),
              second(mystl::forward<Other2>(b))
        {
        }

        // explicit constructiable for other type
        template <class Other1, class Other2,
                  typename std::enable_if<
                      std::is_constructible<T1, Other1>::value &&
                          std::is_constructible<T2, Other2>::value &&
                          (!std::is_convertible<Other1, T1>::value ||
                           !std::is_convertible<Other2, T2>::value),
                      int>::type = 0>
        explicit constexpr pair(Other1 &&a, Other2 &&b)
            : first(mystl::forward<Other1>(a)),
              second(mystl::forward<Other2>(b))
        {
        }

        // implicit constructiable for other pair
        template <class Other1, class Other2,
                  typename std::enable_if<
                      std::is_constructible<T1, const Other1 &>::value &&
                          std::is_constructible<T2, const Other2 &>::value &&
                          std::is_convertible<const Other1 &, T1>::value &&
                          std::is_convertible<const Other2 &, T2>::value,
                      int>::type = 0>
        constexpr pair(const pair<Other1, Other2> &other)
            : first(other.first),
              second(other.second)
        {
        }

        // explicit constructiable for other pair
        template <class Other1, class Other2,
                  typename std::enable_if<
                      std::is_constructible<T1, const Other1 &>::value &&
                          std::is_constructible<T2, const Other2 &>::value &&
                          (!std::is_convertible<const Other1 &, T1>::value ||
                           !std::is_convertible<const Other2 &, T2>::value),
                      int>::type = 0>
        explicit constexpr pair(const pair<Other1, Other2> &other)
            : first(other.first),
              second(other.second)
        {
        }

        // implicit constructiable for other pair
        template <class Other1, class Other2,
                  typename std::enable_if<
                      std::is_constructible<T1, Other1>::value &&
                          std::is_constructible<T2, Other2>::value &&
                          std::is_convertible<Other1, T1>::value &&
                          std::is_convertible<Other2, T2>::value,
                      int>::type = 0>
        constexpr pair(pair<Other1, Other2> &&other)
            : first(mystl::forward<Other1>(other.first)),
              second(mystl::forward<Other2>(other.second))
        {
        }

        // explicit constructiable for other pair
        template <class Other1, class Other2,
                  typename std::enable_if<
                      std::is_constructible<T1, Other1>::value &&
                          std::is_constructible<T2, Other2>::value &&
                          (!std::is_convertible<Other1, T1>::value ||
                           !std::is_convertible<Other2, T2>::value),
                      int>::type = 0>
        explicit constexpr pair(pair<Other1, Other2> &&other)
            : first(mystl::forward<Other1>(other.first)),
              second(mystl::forward<Other2>(other.second))
        {
        }

        // copy assign for this pair
        pair &operator=(const pair &rhs)
        {
            if (this != &rhs)
            {
                first = rhs.first;
                second = rhs.second;
            }
            return *this;
        }

        // move assign for this pair
        pair &operator=(pair &&rhs)
        {
            if (this != &rhs)
            {
                first = mystl::move(rhs.first);
                second = mystl::move(rhs.second);
            }
            return *this;
        }

        // copy assign for other pair
        template <class Other1, class Other2>
        pair &operator=(const pair<Other1, Other2> &other)
        {
            first = other.first;
            second = other.second;
            return *this;
        }

        // move assign for other pair
        template <class Other1, class Other2>
        pair &operator=(pair<Other1, Other2> &&other)
        {
            first = mystl::forward<Other1>(other.first);
            second = mystl::forward<Other2>(other.second);
            return *this;
        }

        ~pair() = default;

        void swap(pair &other)
        {
            if (this != &other)
            {
                mystl::swap(first, other.first);
                mystl::swap(second, other.second);
            }
        }
    };

    /*****************************************************************************************************************************************************************/
    // 重载比较运算符
    // == (lhs == rhs)
    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return rhs.first == lhs.first && rhs.second == lhs.second;
    }

    // != ((lhs != rhs))
    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(rhs == lhs);
    }

    // < (lhs < rhs)
    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return lhs.first < lhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
    }

    // > ((lhs > rhs))
    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (rhs < lhs);
    }

    // <= ((lhs <= rhs))
    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs > rhs);
    }

    // >= ((lhs <= rhs))
    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T1, class T2>
    void swap(pair<T1, T2> &lhs, pair<T1, T2> &rhs)
    {
        lhs.swap(rhs);
    }

    // 将两个数据构成对
    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 &&val1, T2 &&val2)
    {
        return pair<T1, T2>(mystl::forward<T1>(val1), mystl::forward<T2>(val2));
    }

}; // namespace mystl

#endif