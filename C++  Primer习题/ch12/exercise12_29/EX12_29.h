#ifndef EX12_29_H
#define EX12_29_H

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

#include "../example.h"

class QueryResult;

class TextQuery
{
public:
    //   using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream &ifs);
    QueryResult query(const std::string &word) const;

private:
    StrBlob sp_text;
    // 每个单词到它所出现的行号的映射
    std::map<std::string, std::shared_ptr<std::set<StrBlob::size_type>>> sp_dictionary;
};


class QueryResult
{
public:
    friend std::ostream &print(std::ostream &, const QueryResult &);

public:
    std::set<StrBlob::size_type>::iterator begin() const { return lines->begin(); }
    std::set<StrBlob::size_type>::iterator end() const { return lines->end(); }
    std::shared_ptr<StrBlob> getFile() const { return make_shared<StrBlob>(file); }
    QueryResult(const std::string &s,
                std::shared_ptr<std::set<StrBlob::size_type>> sp_set,
                StrBlob sb) : sought(s), lines(sp_set), file(sb) {}

private:
    std::string sought; // 要查找的单词
                        
    std::shared_ptr<std::set<StrBlob::size_type>> lines; // 出现的行号
  
    StrBlob file;   // 输入文件
};

#endif