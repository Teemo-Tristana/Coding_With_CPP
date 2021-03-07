

/**
 * 11.5 解释map和set的区别。你如何选择使用哪个？
 *   map 和 set 都是关联容器
 *   map 是键值对，而 set 的键即值， 当需要存储键值对是使用 map， 而只需要存储键的时则适合用set
 * 
*/

/**
 * 11.6 解释set和list 的区别。你如何选择使用哪个？
 *   set 是不重复元素的集合，是关联容器，底层是基于红黑树实现的
 *   list 是双向循环链表，是顺序容器，底层是基于链表实现的
*/

/**
 * 11.7 定义一个map，关键字是家庭的姓，值是一个vector，保存家中孩子（们）的名。编写代码，实现添加新的家庭以及向已有家庭中添加新的孩子。
*/

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void test_11_7()
{
    map<string, vector<string>> m;
    for (string ln; cout <<"Last name :\n", cin >> ln && ln !="##";){
        for (string cn; cout <<"|-Children's names :\n", cin >> ln && cn !="##";){
            m[ln].push_back(cn);
        }
    }
}


/**
 * 11.8 编写一个程序，在一个vector而不是一个set中保存不重复的单词。使用set的优点是什么？
*/

void test_11_8(){
    std::vector<string> exclude { "aa", "bb", "cc", "dd", "ee", "ff" };
    for (std::string word; std::cout <<"Enter plz :\n", std::cin >> word;){
        auto is_exclude = std::binary_search(exclude.cbegin(), exclude.cend(), word);
        if (!is_exclude){
            exclude.emplace_back(word);
        }
        auto reply = is_exclude ? "excluded": "no_excluded"        ;
        std::cout << reply << std::endl;   
    }
}
