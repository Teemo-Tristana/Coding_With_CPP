/**
 * 迭代器(iterator) 是 STL 的六大组件之一，底层大量采用 traits 技术， STL 中主要采用的是 iterator_traits 和 type_traits 
 * traits 也即是 类型萃取技术
*/

#ifndef MYTINYSTL_ITERATOR_H_
#define MYTINYSTL_ITERATOR_H_

#include <cstddef>

#include "type_traits.h"

namespace mystl
{
    // 五种迭代器

    // 只读
    struct input_iterator_tag
    {
    };

    // 只写
    struct output_iterator_tag
    {
    };

    // 读写， 顺序单向移动，只能向前移动
    struct forward_iterator_tag : public input_iterator_tag
    {
    };

    // 读写， 双向移动，两个方向移动
    struct bidirectional_iterator_tag : public forward_iterator_tag
    {
    };

    // 读写， 随机异地
    struct random_access_iterator_tag : public bidirectional_iterator_tag
    {
    };

    // 模板
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
    struct iterator
    {
        typedef Category iterator_category;
        typedef T value_type;             // 类型
        typedef Pointer pointer;          // 指针
        typedef Reference reference;      // 引用
        typedef Distance difference_type; // 两个iterator之间的距离
    };

    template <class T>
    struct has_iterator_cat
    {
    private:
        struct two
        {
            char a;
            char b;
        };
        template <class U>
        static two test(...);
        template <class U>
        static char test(typename U::iterator_category * = 0);

    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(char);
    };

    template <class Iterator, bool>
    struct iterator_traits_impl
    {
    };

    template <class Iterator>
    struct iterator_traits_impl<Iterator, true>
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::difference_type difference_type;
    };

    template <class Iterator, bool>
    struct iterator_traits_helper
    {
    };

    template <class Iterator>
    struct iterator_traits_helper<Iterator, true>
        : public iterator_traits_impl<Iterator,
                                      std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
                                          std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
    {
    };

    // iterator traits
    // 萃取迭代器的特性
    template <class Iterator>
    struct iterator_traits
        : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value>
    {
    };

    // 针对原生指针的偏特化版本
    template <class T>
    struct iterator_traits<T *>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef ptrdiff_t difference_type;
    };

    template <class T>
    struct iterator_traits<const T *>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef ptrdiff_t difference_type;
    };

    template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
    struct has_iterator_cat_of
        : public m_bool_constant<std::is_convertible<
              typename iterator_traits<T>::iterator_category, U>::value>
    {
    };

    // 采用 萃取技术获取迭代器类型
    template <class T, class U>
    struct has_iterator_cat_of<T, U, false> : public m_false_type
    {
    };

    template <class Iter>
    struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag>
    {
    };

    template <class Iter>
    struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag>
    {
    };

    template <class Iter>
    struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag>
    {
    };

    template <class Iter>
    struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag>
    {
    };

    template <class Iter>
    struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag>
    {
    };

    template <class Iterator>
    struct is_iterator : public m_bool_constant<is_input_iterator<Iterator>::value ||
                                                is_output_iterator<Iterator>::value>
    {
    };

    // 萃取迭代器的 category
    template <class Iterator>
    typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator &)
    {
        typedef typename iterator_traits<Iterator>::iterator_category Category;
        return Category;
    }

    // 萃取迭代器的 距离
    template <class Iterator>
    typename iterator_traits<Iterator>::difference_type *
    distance_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
    }

    // 萃取迭代的 类型
    template <class Iterator>
    typename iterator_traits<Iterator>::value_type *
    value_type(const Iterator &)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
    }

    // 以下函数 是用于在迭代器间移动指定距离(根据类型选择不同的重载版本)
    // 单向
    template <class InputIterator, class Distance>
    void advance_dispatch(InputIterator i, Distance n, input_iterator_tag)
    {
        while (n--)
            ++i;
    }

    // 双向
    template <class BidirectionIteror, class Distance>
    void advance_dispatch(BidirectionIteror &i, Distance n, bidirectional_iterator_tag)
    {
        if (n >= 0)
        {
            while (n--)
                ++i;
        }
        else
        {
            while (n++)
                --i;
        }
    }

    // 随机
    template <class RandomIter, class Distance>
    void advance_dispatch(RandomIter &i, Distance n, random_access_iterator_tag)
    {
        i += n;
    }

    // 对外接口，之所以 inputerItator，因为STL中对 模板参数 命名的潜规则即以强度最弱的iterator的名字来命令能够调用这个函数的模板的参数
    template <class InputIterator, class Distance>
    inline void advance(InputIterator &i, Distance n)
    {
        // 具体调用哪一个 advance_dispatch, 取决于第三个参数， iterator_category实际上就是个 traits
        advance_dispatch(i, n, iterator_category(i));
    }

    /******************************************************************************/
    // 反向迭代器模板类，也即是与正向迭代器相反
    template <class Iterator>
    class reverse_iterator
    {
    private:
        // 记录对应的正向迭代器
        Iterator current;

    public:
        // 五种反向迭代器
        typename iterator_traits<Iterator>::iterator_category iterator_category;
        typename iterator_traits<Iterator>::value_type *value_type;
        typename iterator_traits<Iterator>::difference_type difference_type;
        typename iterator_traits<Iterator>::pointer pointer;
        typename iterator_traits<Iterator>::reference reference;

        typedef Iterator iterator_type;
        typedef reverse_iterator<Iterator> self;

    public:
        reverse_iterator() {}
        explicit reverse_iterator(iterator_type i) : current(i) {}
        reverse_iterator(const self &rhs) : current(rhs.current) {}

    public:
        // 获取正向迭代器
        iterator_type base() const
        {
            return current;
        }

        /*********************************************************************  以下函数均重载运算符的函数  *********************************************************************/
        // 重载解引用运算符*
        reference operator*() const
        {
            auto tmp = current;
            return *--tmp; //先解引用，再--
        }

        // 重载->
        pointer operator->() const
        {
            return &(operator*());
        }

        // 重载前置++
        self &operator++()
        {
            --current;
            return *this;
        }

        // 重载后置++
        self operator++(int)
        {
            self tmp = *this;
            --current;
            return tmp;
        }

        // 重载前置--
        self &operator--()
        {
            ++current;
            return *this;
        }

        // 重载后置--
        self operator--(int)
        {
            self tmp = *this;
            ++current;
            return tmp;
        }

        // 重载 +
        self operator+(distance_type n) const
        {
            return self(current - n);
        }

        // 重载 -
        self operator-(difference_type n) const
        {
            return self(current + n);
        }

        // 重载 +=
        self &operator+=(distance_type n)
        {
            current -= n;
            return *this;
        }

        // 重载-=
        self operator-=(difference_type n)
        {
            current += n;
            return *this;
        }

        // 重载取下标运算符[]
        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }
    };

    /*********************************************************************  以下函数均重载运算符的函数 *********************************************************************/
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() - lhs.base();
    }

    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return !(lhs.base() == rhs.base());
    }

    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() < lhs.base();
    }

    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return rhs < lhs;
    }

    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return !(lhs > rhs);
    }
} // namespace mystl

#endif 