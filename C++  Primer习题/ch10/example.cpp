#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
// #include <iterator>

using namespace std;

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

void elimDups(vector<string> &words)
{
    sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void test1(vector<string> &vec)
{
    elimDups(vec);
    sort(vec.begin(), vec.end(), isShorter);
}

void test2(vector<string> &words)
{
    elimDups(words);
    stable_sort(words.begin(), words.end(), isShorter);
}

/****************** Lambda *******************/

/**
 * 可调度对象：
 *  1. 函数
 *  2. 函数指针
 *  3. 重载了函数调用运算符的类
 *  4. lambda 表达式
 * 
 * 
 *  一个 lambda 表达式是一个可调用的代码单元， 可以视为 一个未命名的内联函数 
 *  形式如下：
 *      [capture list] (parameter list) -> return type { function body }
 * 
 *      1. capture list 捕获列表是 lambda 函数所定义的函数的局部变量列表， 通常为空
 *             一个 lambda 只有在其捕获列表中捕获一个所在函数中的局部变量，才能在函数体中使用该变量。
 *             捕获列表只用于局部非 static 变量。 lambda 可以直接使用局部变量 static 变量 和在它所在函数之外的声明的名字。
 *      2. pameter list 参数列表和普通函数类似，但是 lambda 不能有 默认参数【lambda 实参和形参数目一定相等】
 *      3. return type
 *      4. function body
 *      
 *  2、3、4和普通函数类型
 *  与普通函数不同的是: lambda 必须使用位尾置返回 来指定返回类型。
 *  如果忽略返回类型，lambda 表达式会根据函数体中的代码推断出返回类型
 *          若函数体只有一个 return 语句， 则返回类型从返回表达式的类型推断而来
 *          否则，若未指定返回类型，返回类型为 void
 *      Note:   如果 lambda 的函数体包含任意单一 return 之外的内容， 且未指定返回类型，则返回 void 
 *  
 *     
*/

void test3()
{
    auto f = [] { return 42; };

    cout << f() << endl;
}

string &make_plural(int cnt, string, string);

// 不捕获任何参数的 lambda 参数
void test4()
{
    auto cmp = [](const string &lhs, const string &rhs) {
        return lhs.size() < rhs.size();
    };

    vector<string> words;
    stable_sort(words.begin(), words.end(), [](const string &lhs, const string &rhs) { return lhs.size() < rhs.size(); });

    int sz = 0;
    [sz](const string &a) { return a.size() >= sz; };

    auto wc = find_if(words.begin(), words.end(), [sz](const string &a) { return a.size() >= sz; });

    auto cnt = words.end() - wc;
    cout << cnt << " " << make_plural(cnt, "word", "s") << " of length " << sz << " or longer" << endl;

    for_each(wc, words.end(), [](const string &s) { cout << s << " "; });
}

void bigges(vector<string> &words, vector<string>::size_type sz)
{
    elimDups(words);
    stable_sort(words.begin(), words.end(), [](const string &lhs, const string &rhs) { return lhs.size() < rhs.size(); });

    auto wc = find_if(words.begin(), words.end(), [sz](const string &a) {
        return a.size() >= sz;
    });

    auto cnt = words.end() - wc;

    cout << cnt << " " << make_plural(cnt, "word", "s") << " of lenght " << sz << " or longer" << endl;

    for_each(wc, words.end(), [](const string &str) { cout << str << " "; });

    cout << endl;
}