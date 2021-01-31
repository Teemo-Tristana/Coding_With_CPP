#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>

using namespace std;

// 10_11
template <typename seq>
inline std::ostream &println(seq const &sq)
{
    for (auto const &e : sq)
    {
        std::cout << e << " ";
    }
    cout << endl;
    return cout;
}

inline bool isShoter(const string &lhs, const string &rhs)
{
    return lhs.size() < rhs.size();
}

void elimDups(vector<string> &vs)
{
    sort(vs.begin(), vs.end());
    auto new_end = unique(vs.begin(), vs.end());
    vs.erase(new_end, vs.end());
}

void test_10_11()
{
    vector<string> v{"1234", "1234", "1234", "Hi", "alan", "wang"};

    elimDups(v);
    stable_sort(v.begin(), v.end(), isShoter);
    cout << endl;
    println(v);

    return;
}

// 10_12
// class Sales_data{};

// inline bool compareIsbn(const Sales_data& sd1, const Sales_data &sd2){
//     return sd1.isbn().size() < sd2.isbn().size();
// }

bool predicate(const string &str)
{
    return str.size() >= 5;
}

void test_10_13()
{
    auto v = vector<string>{"a", "as", "aasss", "aaaaassaa", "aaaaaabba", "aaa"};

    auto pivot = partition(v.begin(), v.end(), predicate);

    for (auto it = v.cbegin(); it != pivot; ++it)
    {
        std::cout << *it << " ";
    }
    cout << endl;
}

int main()
{
    test_10_13();

    return 0;
}