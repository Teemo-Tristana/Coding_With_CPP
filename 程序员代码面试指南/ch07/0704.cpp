#include "header.h"

/**
 * 整数的二进制数中有多少个1
*/

int count_1(int n)
{
    int cnt = 0;
    while (n != 0)
    {
        cnt += (n & 1);
        n >>= 1;
    }
    return cnt;
}



int count_2(int n)
{
    int cnt = 0;
    while (n != 0)
    {
       n = n & (n-1);
       ++cnt;
    }
    return cnt;
}


int count_3(int n)
{
    n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 1) & 0x33333333);
    n = (n & 0x0f0f0f0f) + ((n >> 1) & 0x0f0f0f0f);
    n = (n & 0x0000ffff) + ((n >> 1) & 0x0000ffff);
}