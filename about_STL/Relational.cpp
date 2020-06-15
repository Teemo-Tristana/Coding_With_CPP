

#include "Relational.hpp"

using namespace std;


int main()
{
    equal_to<int> equal_to_obj;
    not_equal_to<int> not_equal_to_obj;
    greater<int> greater_obj;
    greater_equal<int> greater_equal_obj;
    less<int> less_obj;
    less_equal<int> less_equal_obj;
 
    std::cout << equal_to_obj(3, 5) << std::endl;
    std::cout << not_equal_to_obj(3, 5) << std::endl;
    std::cout << greater_obj(3, 5) << std::endl;
    std::cout << greater_equal_obj(3, 5) << std::endl;
    std::cout << less_obj(3, 5) << std::endl;
    std::cout << less_equal_obj(3, 5) << std::endl;
 
    std::cout << "**************************" << std::endl;
 
    std::cout << equal_to<int>()(3, 5) << std::endl;
    std::cout << not_equal_to<int>()(3, 5) << std::endl;
    std::cout << greater<int>()(3, 5) << std::endl;
    std::cout << greater_equal<int>()(3, 5) << std::endl;
    std::cout << less<int>()(3, 5) << std::endl;
    std::cout << less_equal<int>()(3, 5) << std::endl;
 
    return 0;
}