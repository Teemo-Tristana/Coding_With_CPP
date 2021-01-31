

/**
 * 11.1 描述map 和 vector 的不同？
 * 
 *  map 是键值对类型的关联容器， vector 是顺序容器
 * 
*/

/**
 * 11.2 分别给出最适合使用 list、vector、deque、map以及set的例子？
 * 
 *  list 是 双向循环链表、适合频繁地插入删除元素的场景
 *  vector 是可动态增长的数组，适合频繁地访问元素的场景
 *  deque 是双端队列，两端开口，适合与频繁地在头尾插入删除元素的场景
 *  以上三个都是顺序容器
 *  map 是关联容器，适合有关联的场景
 *  set 是关联容器，适合于不重复元素的场景
 * 
*/

/**
 * 11.3 编写你自己的单词计数程序
*/
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void test_11_3()
{
    std::map<std::string, std::size_t> word_count;
    std::string word;
    while (std::cin >> word)
    {
        ++word_count[word];
    }

    for (const auto &e : word_count)
    {
        std::cout << e.first << " : " << e.second << endl;
    }
}

/**
 * 11.4 扩展你的程序，忽略大小写和标点。例如，"example."、"example,"和"Example"应该递增相同的计数器。？
*/

void test_11_4()
{
    std::map<std::string, std::size_t> word_count;
    std::string word;
    while (std::cin >> word)
    {
        for (auto &w : word)
        {
            w = tolower(w);
        }

        word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        ++word_count[word];
    }

    for (const auto &e : word_count)
    {
        std::cout << e.first << " : " << e.second << endl;
    }
}


void test_11_7()
{
    map<string, vector<string>> m;
    for (string ln; cout <<"Last name :\n", cin >> ln && ln !="##";){
        for (string cn; cout <<"|-Children's names :\n", cin >> ln && cn !="##";){
            m[ln].push_back(cn);
        }
    }
}