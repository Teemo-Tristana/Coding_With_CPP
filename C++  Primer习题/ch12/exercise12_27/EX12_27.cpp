<<<<<<< HEAD
#include "EX12_27.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

TextQuery::TextQuery(ifstream& ifs) : data(new vector<string>)
{
	string text;
	while (getline(ifs, text))
	{
		data->push_back(text);
		int n = data->size() - 1;
		
		// 拆分单词
		istringstream line(text);
		string word;
		while (line >> word)
		{
			auto &ptoline = record[word];// ptoline 是一个 shared_ptr 指针
			if (!ptoline) // 第一次遇到该单词时，指针为空
				ptoline.reset(new set<line_no>); // 分配一个新的 set
			ptoline->insert(n); // 将 此行号 插入 set 中
		}
	}
}

QueryResult TextQuery::query(const string& word) const
{
	// 若未找到该单词，则返回一个指向此 set 的指针
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = record.find(word);
	if (loc == record.end())
		return QueryResult(word, nodata, data);
	else
		return QueryResult(word, loc->second, data);
}


std::ostream& print(std::ostream& os, const QueryResult& qr)
{
	os << qr.word << " occurs " << qr.lineNo->size() << " "
		<< "time" << (qr.lineNo->size() > 1 ? "s" : "") << endl;
	for (auto num : *qr.lineNo)
		os << "\t[line " << num + 1 << "] " << *(qr.data->begin() + num) << endl;
	return os;
=======
#include "EX12_27.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

TextQuery::TextQuery(ifstream& ifs) : data(new vector<string>)
{
	string text;
	while (getline(ifs, text))
	{
		data->push_back(text);
		int n = data->size() - 1;
		
		// 拆分单词
		istringstream line(text);
		string word;
		while (line >> word)
		{
			auto &ptoline = record[word];// ptoline 是一个 shared_ptr 指针
			if (!ptoline) // 第一次遇到该单词时，指针为空
				ptoline.reset(new set<line_no>); // 分配一个新的 set
			ptoline->insert(n); // 将 此行号 插入 set 中
		}
	}
}

QueryResult TextQuery::query(const string& word) const
{
	// 若未找到该单词，则返回一个指向此 set 的指针
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = record.find(word);
	if (loc == record.end())
		return QueryResult(word, nodata, data);
	else
		return QueryResult(word, loc->second, data);
}


std::ostream& print(std::ostream& os, const QueryResult& qr)
{
	os << qr.word << " occurs " << qr.lineNo->size() << " "
		<< "time" << (qr.lineNo->size() > 1 ? "s" : "") << endl;
	for (auto num : *qr.lineNo)
		os << "\t[line " << num + 1 << "] " << *(qr.data->begin() + num) << endl;
	return os;
>>>>>>> 9a5e9bede5efffbf2eb1d5a82ed59e134223b5e5
}