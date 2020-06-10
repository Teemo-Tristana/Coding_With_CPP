#include <iostream>
using namespace std;

template <calss Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key>>
class set;

class Set
{
private:
    typedef key_type Key;
    typedef value_type Key;
    typedef size_type std::size_t;
    typedef difference_type std::ptrdiff_t;
    typedef Key_compare Compare;
    typedef Value_compare Compare;
    typedef allocator_type Allocator;
    typedef reference value_type &;
    typedef reference Allocator::reference;
    typedef const_reference Allocator::const_reference;
    typedef const_reference const value_type &;
    typedef pointer Allocator::pointer;
    typedef pointer std::allocator_traits<Alloctor>::pointer;
    typedef const_pointer Allocator::const_pointer;
    typedef const_pointer std::allocator_traits<Allocator>::const_pointer;

    // typedef iterator
    // typedef const_iterator;
    typedef reverse_iterator std::reverse_iterator<iterator> typedef const_reverse_iterator std::reverse_iterator<const_iterator>

    //C++17起
    // typedef node_type
    // typedef insert_return_type

public:
    Set();
    ~Set();
    void operator=();
    Allocator get_allocator();
    
};