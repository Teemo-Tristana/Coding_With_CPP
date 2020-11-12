/**
 * 不用做任何比较判断找出两个数中较大的数
*/

// 若 n 为 1 返回1，否则返回0

#include "header.h"

int flip(int n)
{
    return n ^ 1;
}

// 判断数字的正负： n>= 0返回1，否则返回 0
int sign(int n)
{
    // n 右移31后区最高位为符号位，负数为1，正数为0
    return flip((n >> 31) & 1);
}

// 两个数相减，通过结果来比较，但是肯能出现溢出的bug
int getMax1(int a, int b)
{
    int c = a - b;
    int scA = sign(c);
    int scB = flip(scA);
    return a * scA + b * scB;
}

// 不会出现溢出的bug
int getMax2(int a, int b)
{
    int c = a - b;
    int sa = sign(a); // a 的符号
    int sb = sign(b); // b 的符号
    int sc = sign(c); // c 的符号
    int diff_sign_ab = sa ^ sb; // 若 a、b符号不同则为 1 ，否则为0 
    int same_sign_ab = flip(diff_sign_ab); // 若a、b符号相同为1， 否则为0
    int rA = diff_sign_ab * sa + same_sign_ab * sc;
    int rB = flip(rA);

    return a * rA + b * rB;
}
int main()
{
    int x =11;
    cout << ((x >> 31) & 1) << endl;
    cout << flip( ((x >> 31) & 1)) << endl;
    return 0;
}