#include <iostream>
#include <utility>

int main()
{
    int x = 2;
    std::move(x);
    std::pair<int,int>(1,2);
    std::make_pair<int,int>(1,2)
}