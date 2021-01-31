#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>

void test_10_1()
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 6, 6, 2};
    std::cout << std::count(vec.begin(), vec.end(), 6) << std::endl;
}

void test_10_2()
{

    std::list<std::string> ls = {"aa", "aaa", "aa", "cc"};
    std::cout << std::count(ls.cbegin(), ls.cend(), "aa") << std::endl;
}

int main()
{
    test_10_2();
}