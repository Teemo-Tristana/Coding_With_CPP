#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>

// #include <iterator>

using namespace std;

// 声明 _1 是占位符号
using std::placeholders::_1;
using std::placeholders::_2;

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
 *  lambda 函数是一个函数对象，编译时编译器生成一个与 lambda 对应类型的类，编译器会再生成一个该类型的未命名的对象。
 *  形式如下：
 *      [capture list] (parameter list) -> return type { function body }
 * 
 *      1. capture list 捕获列表是 lambda 函数所定义的函数的局部变量列表， 通常为空
 *             一个 lambda 只有在其捕获列表中捕获一个所在函数中的局部变量，才能在函数体中使用该变量。
 *             捕获列表只用于局部非 static 变量。 lambda 可以直接使用局部变量 static 变量 和在它所在函数之外的声明的名字。
 *             捕获列表的变量可以分为 值 或 引用传递。
 *                  值传递： lambda 捕获的变量在 lambda 函数 创建 时拷贝。
 *                  引用传递：
 * 
 *             隐式捕获：
 *                  编译器可以根据 lambda 中的代码推导使用的变量，为指示编译器推断捕获列表，应该在捕获列表中写一个 & 或 = 
 *                      & 告知编译器采用引用传递方式
 *                      = 告知编译器采用值传递方式 
 * 
 *                  当混合使用时，捕获列表第一个参数必须是 & 或 = 且显示捕获的变量必须和隐式捕获使用不同的传递方式
 *  
 *      2. pameter list 
 *          参数列表和普通函数类似，但是 lambda 不能有 默认参数【lambda 实参和形参数目一定相等】
 *      
 *      3. return type
 *          与普通函数不同的是: lambda 必须使用位尾置返回 来指定返回类型。
 *          如果忽略返回类型，lambda 表达式会根据函数体中的代码推断出返回类型
 *                  若函数体只有一个 return 语句， 则返回类型从返回表达式的类型推断而来
 *                  否则，若未指定返回类型，返回类型为 void
 *          Note:   如果 lambda 的函数体包含任意单一 return 之外的内容， 且未指定返回类型，则返回 void 
 *        
 *          当需要为 lambda 定义返回类型时，必须使用尾置返回类型    
 *      
 * 4. function body
 *      
 *  2、3、4和普通函数类型

 * 
 * 
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

void biggies(vector<string> &words, vector<string>::size_type sz)
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

void fcnt1()
{
    size_t v1 = 42;

    // lambda 值传递
    auto f = [v1] { return v1; };
    v1 = 0;
    auto j = f(); // j = 42
}

void fcnt2()
{
    size_t v1 = 42;

    // lambda 引用传递
    auto f = [&v1] { return v1; };
    v1 = 0;
    auto j = f(); // j = 0
}

// 隐藏捕获
void fcnt3(vector<string> &words)
{
    // sz 是隐式捕获， 值捕获方式
    auto wc = find_if(words.begin(), words.end(), [=](const string &lhs, const string &rhs) { return lhs.size() > rhs.size(); });
}

void fcnt4(vector<string> &words, vector<string>::size_type sz, ostream &os = cout, char ch = ' ')
{

    for_each(words.begin(), words.end(), [&, ch](const string &str) { os << str << ch; });

    for_each(words.begin(), words.end(), [=, &os](const string &str) { cout << str << ch; });
}

void fcnt5()
{
    size_t v1 = 42;
    auto f = [v1]() mutable { return ++v1; };
    v1 = 0;
    auto j = f(); //43
}

void fcnt6()
{
    size_t v1 = 42;
    auto f = [&]() { return ++v1; };
    v1 = 0;
    auto j = f(); //1;
}

// 当需要为 lambda 定义返回类型时，必须使用尾置返回类型
void test_7()
{
    vector<int> v1;
    transform(v1.begin(), v1.end(), v1.begin(),
              [](int i) -> int { if (i < 0) {return -i;}else{return i;} });
}


/****************** bind *******************/
/**
 * bind() 函数可以视为一个通用的 函数适配器 : 接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表
 *      auto newCallable = bind(callable, arg_list)
 *  
 * bind() 绑定可调用对象中的参数或重新1安排调用顺序
 * 用 bind 重排参数顺序
 * bind() 绑定引用参数
 *      ref() : 若希望传递给 bind() 一个对象而又不拷贝它， 就必须调用标准库 ref 函数
 *      cref():  用于 const 引用的类对象
*/

bool check_size(const string& lhs, string::size_type sz){
    return lhs.size() >= sz;
}   

// _1 是占位符
auto check6 = bind(check_size, _1, 6);

void test_8(){
    string str = "hello";
    bool b1 = check6(str);
}

void test_9(){
    vector<string> words;
    int sz = 0;
    auto wc = find_if(words.begin(), words.end(), bind(check_size, _1, sz));
}

void test_9(){
    vector<string> words;
    //  isShorter(A, B)
    sort(words.begin(), words.end(),isShorter);

    // bind 重排参数顺序
    // isShorter(B, A)
    sort(words.begin(), words.end(), bind(isShorter, _2, _1));
}

ostream& println(ostream& os, const string&  str, char ch){
    return os << str << ch;
}

void test_10(vector<string>& vec, ostream& os){
    // bind() 绑定引用参数
    for_each(vec.begin(), vec.end(), bind(println, ref(os), _1,' '));
}