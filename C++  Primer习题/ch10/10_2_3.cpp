
// 10_9 实现你自己的 elimDups。分别在读取输入后、调用 unique后以及调用erase后打印vector的内容。

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename Sequence>
auto println(Sequence const &seq) -> std::ostream &
{
    for (auto const &e : seq)
    {
        std::cout << e << " ";
    }
    return std::cout << std::endl;
}

auto eliminate_duplicates(std::vector<std::string> &vs) -> std::vector<std::string> &
{
    std::sort(vs.begin(), vs.end());
    println(vs);

    auto new_end = std::unique(vs.begin(), vs.end());
    println(vs);

    vs.erase(new_end, vs.end());
    return vs;
}

void test_10_9()
{
    std::vector<std::string> vs{"a", "v", "a", "s", "v", "a", "a"};
    println(vs);
    println(eliminate_duplicates(vs));
}

/**
 * 你认为算法不改变容器大小的原因是什么？
 *      算法的借口是迭代器，而迭代器是用来改变容器的元素的，这样设计时的算法具有通用性。
*/

int main()
{
    test_10_9();

    return 0;
    
}