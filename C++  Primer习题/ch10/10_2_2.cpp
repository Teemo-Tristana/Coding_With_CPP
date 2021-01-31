#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
void test_10_6()
{
    vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::fill_n(vec.begin(), vec.size(), -1);
    for (auto &v : vec)
    {
        cout << v << " ";
    }

    cout << endl;
}

// 10_7 下面程序是否有错误？如果有，请改正：
void test_10_7()
{
    // (a)
    vector<int> vec;
    list<int> lst;
    int i;
    while (cin >> i)
        lst.push_back(i);
    // 这里应该加入一个 vec.resize(lst.size()) 以确保vec的容器大小至少和输入序列一样多。
    copy(lst.cbegin(), lst.cend(), vec.begin());
    
    //(b)
    vector<int> vec;
    /**
     * vector 的 reserve 和 resize
     *  reverse 改变的是容器的容量 capacity
     *  resize  改编的是容器的大小 size
     * 因此，这里应该将改为 resize 比较合适
    */
    vec.resize(10);
    vec.reserve(10);

    fill_n(vec.begin(), 10, 0);
}


// 10_8 本节提到过，标准库算法不会改变它们所操作的容器的大小。为什么使用 back_inserter 不会使这一断言失效？
/**
 * back_inserter 是插入迭代器， 在 iterator.h 头文件中，不是标准库的算法
*/

int main()
{
    test_10_6();
}