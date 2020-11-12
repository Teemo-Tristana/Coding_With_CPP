/**
 * 只用位运算不用算数运算实现整数的加减乘除运算
*/

/**
 * 加法： 
 *      ^ 和 & 组合运算
*/

#include "header.h"

int add(int a, int b)
{
    int sum = a;
    while (b != 0)
    {
        sum = a ^ b;
        b = (a & b) << 1;
        a = sum;
    }
    return a;
}

/**
 * a - b = a + (-b)
 * 一个整数的相反数为 该数的二级制取反+1，也即是 ~b + 1 == -b
*/

int negNum(int n)
{
    return add(~n, 1);
}

int subtraction(int a, int b)
{
    return add(a, negNum(b));
}

/**
 * 乘法：
 *    res = 0
 *    比较 b 的二进制最后一位
 *      若为1，则 res = res + a;
 *      若为0，则什么都不做
 *      同时 a 左移一位， b右移一位
 *    直到 b = 0  
*/

int multi(int a, int b)
{
    int res = 0;
    while (b != 0)
    {
        if (b & 1)
            res = add(res, a);
        a <<= 1;
        b >>= 1;
    }
    return res;
}

/**
 * 除法：
*/

int divide(int a, int b)
{
    if (!b)
    {
        cout <<"divisor is zero\n";
        return 0;
    }

    if (a == INT_MIN && b == INT_MAX)
        return 1;
    else if (b == INT_MIN)
        return 0;
    else if (a ==INT_MIN)
    {
        int res = divide(add(a, 1), b);
        return add(res, divide(subtraction(a, multi(res, b)),b));
    }
    else 
        return divide(a, b);

}
int main()
{
    int a = 3;
    cout << add(a, a) << endl;
    cout << subtraction(a, a) << endl;
    return 0;
}