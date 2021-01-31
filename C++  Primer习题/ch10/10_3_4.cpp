#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

bool isLessThanorEqualToN(const string &str, string::size_type sz)
{
    return str.size() <= sz;
}
// 10_22
void test_10_22()
{
    std::vector<string> authors{"1234567", "1234", "1234567890", "1234567", "12345"};

    cout << count_if(authors.cbegin(), authors.cend(), bind(isLessThanorEqualToN, _1, 6)) << endl;
}

// 10_23 bind 接受几个参数？
// 假设被绑定的函数接受 n 个参数， 则bind()函数接受 n + 1 个参数

bool check_size(const string &str, size_t i)
{
    return i > str.size();
}

// 10_24
void test_10_24()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    string str("12345");

    auto it = find_if(v.cbegin(), v.cend(), bind(check_size, str, _1));

    if (it != v.end())
    {
        cout << *it << endl;
    }
}

void elimdups(vector<string> &vs)
{
    std::sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
    elimdups(words);
    auto it = stable_partition(words.begin(), words.end(), bind(check_size, _1, sz));

    for_each(words.begin(), it, [](const string &s) { cout << s << " "; });
}

void test_10_25()
{
    std::vector<std::string> v{"the", "quick", "red", "fox", "jumps",
                               "over", "the", "slow", "red", "turtle"};
    biggies(v, 4);
}

int main()
{
    test_10_25();

    return 0;
}