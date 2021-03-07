#ifndef EX12_27_H
#define EX12_27_H


/**
 * 文本查询程序:
 *  用户给定的文件中查询单词，返回单词出现的次数以及所在行的列表
 * 
 * 
 * 分析:
 *      1. 逐行读取文本，并将每一行拆分为独立的单词
 *      2. 输出时：
 *              提取每个单词的关联行
 *              按出现的顺序升序无重复
 *              打印给定行的文本
 * 
 *      3. vector<string> data ，data 保存输入文件的副本， 每一行为 data 的一个元素， 打印时，
 *                       根据行数作为下标来提取对应的一行。
 * 
 *      4. 使用 istringstream 来将每行分解为单词
 *      5. 使用 set 来保存每个单词在输入文本中出现的行号，从而保证每行只出现一个且按行号递增
 *      6. 使用 map 将 set 和关联起来，从而实现提取任意单词
*/


#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>

class QueryResult;

// 输入文件类
class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream &);
    QueryResult query(const std::string &s) const;

private:
    std::shared_ptr<std::vector<std::string>> data; // 按行保存输入的文本
    std::map<std::string, std::shared_ptr<std::set<line_no>>> record; // 将每个单词和它出现的行号关联
};


// 查询类
class QueryResult
{
public:
    friend std::ostream &print(std::ostream &, const QueryResult &);

    QueryResult(std::string str,
                std::shared_ptr<std::set<TextQuery::line_no>> sp,
                std::shared_ptr<std::vector<std::string>> f) : word(str), lineNo(sp), data(f)
    {
    }

private:
    std::string word; // 查询单词
    std::shared_ptr<std::set<TextQuery::line_no>> lineNo; // 出现的行号
    std::shared_ptr<std::vector<std::string>> data; // 输入文件
};

std::ostream &print(std::ostream &, const QueryResult &);

#endif