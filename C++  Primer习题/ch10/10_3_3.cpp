#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

size_t bigerThann(const vector<string> &vec, const int &n)
{

    return count_if(vec.cbegin(), vec.cend(),
                    [&](const string &str) { return str.size() > n; });
}

void test_10_20()
{
    vector<string> v{"1234", "123456", "1234567", "1234567", "1234567", "1234567"};
    int n = 6;
    std::cout << "ex10.20: " << bigerThann(v, n) << std::endl;
}


void test_10_21(){
    int i = 10;
    auto f =[&i]()-> bool {return (i == 0  ? true : !(i--));};

    while (!f()){
        cout << i << endl;
    }
}

int main(){
    test_10_21();
}