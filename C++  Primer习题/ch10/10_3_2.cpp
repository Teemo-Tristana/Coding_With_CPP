#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// 10_14
void test_10_14()
{
    auto f = [](int i, int j) { return i + j; };
}

// 10_15
void test_10_15()
{
    int x = 10;
    auto f = [x](int i) { return x + i; };
}

void elimdups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto new_end = std::unique(words.begin(), words.end());

    words.erase(new_end, words.end());
}

void biggies(std::vector<string> &words, std::vector<string>::size_type sz)
{
    elimdups(words);

    std::stable_sort(words.begin(), words.end(), [](string const &lhs, string const &rhs) { return lhs.size() > rhs.size(); });

    auto wc = std::find_if(words.begin(), words.end(), [sz](const string &str) { return str.size() >= sz; });

    std::for_each(wc, words.end(), [](const string &str) { std::cout << str << " "; });
}

void test_10_16()
{
    std::vector<std::string> v{
        "1234", "1234", "1234", "hi~", "alan", "alan", "cp"};
    std::cout << "ex10.16: ";
    biggies(v, 3);
    std::cout << std::endl;
}

// class Sales_data
// {
// public:
//     Sales_data(string a);
// };
// void test_10_17()
// {
//     Sales_data d1("aa"), d2("aaaa"), d3("aaa"), d4("z"), d5("aaaaz");

//     std::vector<Sales_data> v{d1, d2, d3, d4, d5};

//     std::sort(v.begin(), v.end(), [](const Sales_data &sd1, Sales_data &sd2) {
//         return sd1.isbn().size() < sd2.isbn().size();
//     });

//     for (const auto &e : v)
//     {
//         std::cout << e.isbn() << " ";
//     }

//     std::cout << std::endl;
// }

// 10_18

void biggies_partition(std::vector<std::string> &words, std::size_t sz)
{
    elimdups(words);

    auto pivot = partition(words.begin(), words.end(), [sz](const std::string &str) {
        return str.size() >= sz;
    });

    for (auto it = words.cbegin(); it != pivot; ++it)
    {
        std::cout << *it << " ";
    }
}

void test_10_18()
{
    std::vector<std::string> v{"the", "quick", "red", "fox", "jumps",
                               "over", "the", "slow", "red", "turtle"};

    std::cout << "ex10.18: ";
    biggies_partition(v, 4);
    std::cout << std::endl;
}

void biggies_stable_partition(vector<string> &words, std::size_t sz)
{
    elimdups(words);

    auto pivot = stable_partition(words.begin(), words.end(), [sz](string &str) { return str.size() >= sz; });

    for (auto it = words.cbegin(); it != pivot; ++it)
    {
        cout << *it << " ";
    }
}

void test_10_19()
{
    std::vector<std::string> v{"the", "quick", "red", "fox", "jumps",
                               "over", "the", "slow", "red", "turtle"};

    biggies_stable_partition(v, 4);
    std::cout << std::endl;
}

int main()
{
    test_10_19();

    return 0;
}