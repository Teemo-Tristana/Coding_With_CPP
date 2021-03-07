<<<<<<< HEAD
#include "EX12_29.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


TextQuery::TextQuery(std::ifstream& ifs)
{
    string text;
    StrBlob::size_type n = 0;
    while (getline(ifs, text)) {
        sp_text.push_back(text);
        n = sp_text.size() - 1;    // 当前行号
        istringstream line (text);
        string word;
        while (line >> word) {
            auto &lines = sp_dictionary[word];

            if (!lines) {
                lines.reset (new std::set<StrBlob::size_type>);
            }
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string& word) const
{
    // 如果未找到sought, 返回一个指向此set的指针。
    static shared_ptr<set<StrBlob::size_type>> nodata (new set<StrBlob::size_type>);
    auto loc = sp_dictionary.find(word);

    if (loc == sp_dictionary.end()) {
        return QueryResult(word, nodata, sp_text);
    }
    else {
        return QueryResult(word, loc->second, sp_text);
    }
}

ostream& print(ostream& os, const QueryResult& qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " times." << endl;

    for (auto iter = qr.begin(); iter != qr.end(); ++ iter) {
        ConstStrBlobPtr p (*qr.getFile(), *iter);
        os << "\t(line " << *iter+1 << ") " << p.deref() << endl;
    }
    return os;
}
=======
#include "EX12_29.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


TextQuery::TextQuery(std::ifstream& ifs)
{
    string text;
    StrBlob::size_type n = 0;
    while (getline(ifs, text)) {
        sp_text.push_back(text);
        n = sp_text.size() - 1;    // 当前行号
        istringstream line (text);
        string word;
        while (line >> word) {
            auto &lines = sp_dictionary[word];

            if (!lines) {
                lines.reset (new std::set<StrBlob::size_type>);
            }
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string& word) const
{
    // 如果未找到sought, 返回一个指向此set的指针。
    static shared_ptr<set<StrBlob::size_type>> nodata (new set<StrBlob::size_type>);
    auto loc = sp_dictionary.find(word);

    if (loc == sp_dictionary.end()) {
        return QueryResult(word, nodata, sp_text);
    }
    else {
        return QueryResult(word, loc->second, sp_text);
    }
}

ostream& print(ostream& os, const QueryResult& qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " times." << endl;

    for (auto iter = qr.begin(); iter != qr.end(); ++ iter) {
        ConstStrBlobPtr p (*qr.getFile(), *iter);
        os << "\t(line " << *iter+1 << ") " << p.deref() << endl;
    }
    return os;
}
>>>>>>> 9a5e9bede5efffbf2eb1d5a82ed59e134223b5e5
