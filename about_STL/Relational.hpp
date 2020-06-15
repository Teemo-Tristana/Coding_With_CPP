#ifndef RELATION__HPP__
#define RELATION__HPP__

#include <iostream>
#include <functional>

template<typename T>
struct equal_to: public binary_function<T, T, bool>
{
    bool operator()(const T& ,x const T& y)
    {
        return x == y;
    }
};

template<typename T>
struct equal_to: public binary_function<T, T, bool>
{
    bool operator()(const T& ,x const T& y)
    {
        return x == y;
    }
};

template<typename T>
struct not_equal_to: public binary_function<T, T, bool>
{
    bool operator()(const T& ,x const T& y)
    {
        return x != y;
    }
};

template<typename T>
struct greater: public binary_function<T, T, bool>
{
    bool operator()(const T& ,x const T& y)
    {
        return x > y;
    }
};

template<typename T>
struct greater_equal: public binary_function<T, T, bool>
{
    bool operator()(const T& ,x const T& y)
    {
        return x >= y;
    }
};

template<typename T>
struct less: public binary_function<T, T, bool>
{
    bool operator()(const T& ,x const T& y)
    {
        return x < y;
    }
};

template<typename T>
struct less_equal: public binary_function<T, T, bool>
{
    bool operator()(const T& ,x const T& y)
    {
        return x <= y;
    }
};

#endif