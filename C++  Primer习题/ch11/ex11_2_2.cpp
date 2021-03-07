
/**
 * 11_9. 定义一个map，将单词与一个行号的list关联，list中保存的是单词所出现的行号
*/
#include <iostream>
#include <map>
#include <list>
#include <string>

using namespace std;


void test_11_9(){
    std::map<std::string, std::list<std::size_t>> ml;
}


/**
 * 11.10 可以定义一个vector::iterator 到 int 的map吗？list::iterator 到 int 的map呢？对于两种情况，如果不能，解释为什么。？
 * 
 *    map 是有序的关联容器，必须由提供比较操作 
 *    vector::iterator 有自定义的比较操作 < 
 *    list::iterator 的 list 不支持比较操作。
*/

/**
 * 11.11 不使用decltype 重新定义 bookstore。？
 *  
*/
class Scales_data{};
void test_11_11(){
    using Less = bool (*) (Scales_data const &, Scales_data const &);
    std::multimap<Scales_data, Less> bookstore();
}