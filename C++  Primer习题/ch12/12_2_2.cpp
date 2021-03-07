#include <iostream>
#include <memory>
#include <string>

using namespace std;

void test_12_26()
{
    int n = 5;

    allocator<string> alloc; // 可分配 string 的 alloctor 对象
    auto p = alloc.allocate(n); // 分配 n 个未初始化的string

    string str; 
    auto q = p;// q 指向最后构造的元素之后的位置
    while (cin >> str && q != p + n) 
    {
        alloc.construct(q++, str); // 构造字符串
        char ch = getchar();
        while (ch == '\n')
        {
            break;
        }
    }

    while (q != p)
    {
        cout << *--q << " ";
        alloc.destroy(q); // 释放 string
    }

    alloc.deallocate(p, n); // 释放 allocator 分配资源

    return;
}

int main()
{
    test_12_26();

    return 0;
}
