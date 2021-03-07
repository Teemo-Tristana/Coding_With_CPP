#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <map>

using namespace std;

/**
 * 11.12  编写程序，读入string和int的序列，将每个string和int存入一个pair 中，pair保存在一个vector中。? 
*/

void test_12()
{
    std::vector<std::pair<std::string, int>> vpair;
    std::string str;

    int i;
    while (std::cin >> str >> i)
    {
        // 方法1
        vpair.push_back(std::pair<std::string, int>(str, i));

        // 方法2
        vpair.push_back(std::make_pair(str, i));

        // 方法3
        vpair.push_back({str, i});
    }

    for (const auto &v : vpair)
    {
        std::cout << v.first << " : " << v.second << std::endl;
    }
}

/**
 * 11.13 在上一题的程序中，至少有三种创建pair的方法。编写此程序的三个版本，分别采用不同的方法创建pair。解释你认为哪种形式最易于编写和理解，为什么？
 * 
 * 方法1 最好理解，它直接表明pair的类型和初始化
 * 方法3 最简洁
*/

/**
 * 11.14 在上一题的程序中，至少有三种创建pair的方法。编写此程序的三个版本，分别采用不同的方法创建pair。解释你认为哪种形式最易于编写和理解，为什么？？
*/

class Families
{
public:
    using Child = pair<string, string>;
    using Children = vector<Child>;
    using Data = map<string, Children>;

    void add(string &const last_name, string &const firsetname, const string birthday)
    {
        auto child = make_pair(firsetname, birthday);
        data[last_name].push_back(child);
    }

    void print() const
    {
        for (auto &d : data)
        {
            cout << d.first << ":\n";
            for (auto const &c : d.second)
            {
                cout << c.first << " " << c.second << endl;
            }
            cout << endl;
        }
    }

private:
    Data data;
};
