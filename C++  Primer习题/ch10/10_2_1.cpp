/**
 * 只读算法:
 *      find()
 *      count()
 *      accmulate()
 *      equal()
 * 
 *  对于只读算法：最好使用cbegin() 和 cend()
*/

#include <iostream>
#include <vector>
#include <numeric>

// 10_3
void test_10_3(){
    std::vector<int> v{1,2,3,4};
    std::cout << std::accumulate(v.cbegin(), v.cend(), 0) << std::endl;
}


/**
 *  10_4 假定 v 是一个vector，那么调用 accumulate(v.cbegin(),v.cend(),0) 有何错误（如果存在的话）？
 *  传入的是0，结果会是 int 类型
*/


/**
 * 10_5 在本节对名册（roster）调用equal 的例子中，如果两个名册中保存的都是C风格字符串而不是string，会发生什么？
 *      C 风格字符串是用字符串的指针表示的，因此，这会导致比较的是两个指针，而非两个指针所指向的内容。
*/



int main(){
    test_10_3();
}