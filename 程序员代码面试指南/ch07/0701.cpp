/**
 * 1. 不使用额外变量交换两个整数的值
*/
#include "header.h"

void swap(int &a, int &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

int main()
{
    int a = 100;
    int b = 666;
    printf("a = %d\t b = %d\n", a, b);
    swap(a, b);
    printf("a = %d\t b = %d\n", a, b);

    return 0;
}