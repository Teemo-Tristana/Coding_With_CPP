#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * 11.15 对一个int到vector的map，其mapped_type、key_type和 value_type分别是什么？
 *  eg map<int, vector<string>> vec;
 * 
 * mapped_type ： vector<string>
 * key_type    :  int
 * value_type  : std::pair<const int, vector<string>>
*/

/**
 * 11.16 使用一个map迭代器编写一个表达式，将一个值赋予一个元素。
*/

void test_11_16()
{
    std::map<int, string> m;

    // 方式1
    std::map<int, string>::iterator it = m.begin();
    it->second = "hello";

    // 方式2
    auto it2 = m.begin();
    it2->second = "world";
}

/**
 * 11.17 假定 c 是一个string的multiset，v 是一个string 的vector，解释下面的调用。指出每个调用是否合法？
 * 
*/

void test_11_17()
{
    std::multiset<string> c;
    std::vector<string> v;

    // a ✔
    copy(v.begin(), v.end(), inserter(c, c.end()));

    // b ❌ multiset 没有 push_back 方法，而 back_inserter(v) 的容器 v 需要支持 push_back
    copy(v.begin(), v.end(), back_inserter(c));

    // c ✔
    copy(c.begin(), c.end(), inserter(v, v.end()));

    // d ✔
    copy(c.begin(), c.end(), back_inserter(v));
}

/**
 * 11.18 写出第382页循环中map_it 的类型，不要使用auto 或 decltype。
*/
void test_11_18()
{
    map<string, size_t> word_count;
    map<string, size_t>::const_iterator it = word_count.cbegin();
}

/**
 * 11.19 定义一个变量，通过对11.2.2节中的名为 bookstore 的multiset 调用begin()来初始化这个变量。写出变量的类型，不要使用auto 或 decltype。
*/
class Sales_data
{
};
void test_12_18()
{
    using compareType = bool (*)(const Sales_data &lhs, const Sales_data &rhs);
    std::multiset<Sales_data, compareType> bookstore(compareIsbn);
    std::multiset<Sales_data, compareType>::iterator c_it = bookstore.begin();
}