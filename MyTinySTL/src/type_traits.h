/**
 * type_traits(类型萃取技术)， 主要用于提取C++对象的类型
 * type_traits 是 STL 中基础部分，用于在编译期间获取类型的信息，然后根据类型信息做不同的处理，常结合函数重载使用。
 * traits的实现，基本都是靠类型typedef，然后通过特化一些类型，这样子就可以在编译器获取类型的某些性质
 * 
*/
#ifndef MYTINYSTL_TYPE_TRAITS_H_
#define MYTINYSTL_TYPE_TRAITS_H_

#include <type_traits>

namespace mystl
{
    template <class T, T v>
    struct m_integral_constan
    {
        static constexpr T value = v;
    };

    template <bool b>
    using m_bool_constant = m_integral_constan<bool, b>;


    typedef m_bool_constant<true> m_true_type;
    typedef m_bool_constant<false> m_false_type;

    /*********************************************************************/

    template <class T1, class T2>
    struct pair;

    template <class T>
    struct is_pair : mystl::m_false_type
    {
    };

    template <class T1, class T2>
    struct is_pair<mystl::pair<T1, T2>> : mystl::m_true_type
    {
    };
}; // namespace mystl
#endif