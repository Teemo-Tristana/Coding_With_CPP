#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

// 12_28
// 12_27 和 28 作用相同，效果一样，但是 12_27 抽象化，使用了 C++的面向对象的对象思想，更好
#include <string>
#include <vector>

#include <memory>

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void test_while(map<string, set<vector<string>::size_type>> &dictionary,
                vector<string> &input);

void test_do_while(map<string, set<vector<string>::size_type>> &dictionary,
                   vector<string> &input);

void test_12_18()
{
    std::ifstream file("./exercise12_27/storyDataFile.txt");
    vector<string> input;
    std::map<string, std::set<decltype(input.size())>> dictionary;
    decltype(input.size()) lineNo{0};

    for (string line; std::getline(file, line); ++lineNo)
    {
        input.push_back(line);
        std::istringstream line_stream(line);

        string word;
        while (line_stream >> word)
        {
            for (auto &w : word)
                w = tolower(w);

            // 若 不含有，则加入
            if (!dictionary[word].count(lineNo))
                dictionary[word].insert(lineNo);
        }
    }

    cout << "-------------------" << endl;
    for (auto &s : input)
    {
        cout << s << endl;
    }
    cout << "-------------------" << endl;

    //
    // test_while(dictionary, input);
    test_do_while(dictionary, input);
}


// 12_29 
// 更喜欢 while ，也更习惯 while
void test_while(map<string, set<vector<string>::size_type>> &dictionary,
                vector<string> &input)
{

    while (true)
    {
        std::cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(std::cin >> s) || s == "q")
            break;
        auto found = dictionary.find(s);
        if (found != dictionary.end())
        {
            std::cout << s << " occurs " << found->second.size() << (found->second.size() > 1 ? " times" : " time") << std::endl;
            for (auto i : found->second)
                std::cout << "\t(line " << i + 1 << ") " << input.at(i) << std::endl;
        }
        else
            std::cout << s << " occurs 0 time" << std::endl;
    }
}

void test_do_while(map<string, set<vector<string>::size_type>> &dictionary,
                   vector<string> &input)
{
    do
    {
        std::cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(std::cin >> s) || s == "q")
            break;
        auto found = dictionary.find(s);
        if (found != dictionary.end())
        {
            std::cout << s << " occurs " << found->second.size() << (found->second.size() > 1 ? " times" : " time") << std::endl;
            for (auto i : found->second)
                std::cout << "\t(line " << i + 1 << ") " << input.at(i) << std::endl;
        }
        else
            std::cout << s << " occurs 0 time" << std::endl;
    } while (1);
}


int main()
{
    test_12_18();

    return 0;
}