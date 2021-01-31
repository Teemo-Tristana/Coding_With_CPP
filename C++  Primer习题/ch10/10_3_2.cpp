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

int main()
{
    test_10_16();

    return 0;
}