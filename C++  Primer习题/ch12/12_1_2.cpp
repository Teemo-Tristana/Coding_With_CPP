
//12.6
#include <iostream>
#include <vector>
#include <memory>


using namespace std;

// 获取动态分配的 vector : 返回一个指向 vector<int> 的指针
vector<int> *getpvec()
{
    return new vector<int>();
}

// 读取标准输入，将读入的值保存在 vector 中
void getNum(vector<int> *&pvec)
{
    int num = 0;
    while (cin >> num)
    {
        pvec->push_back(num);
        char ch = getchar();
        if (ch == '\n')
            break;
    }
}

// 输出 vector 的值
void printVec(vector<int> *&pvec)
{
    for (const auto &v : *pvec)
    {
        cout << v << " ";
    }
    cout << endl;
}

void test_12_6(){
    cout <<"common pointer\n";
    vector<int>* pvec = getpvec();
    getNum(pvec);
    printVec(pvec);
    
    delete pvec;
    pvec = nullptr;
    return ;
}


// 12.7
shared_ptr<vector<int>> getspvec(){
    return make_shared<vector<int>>();
}

void getSpNum(shared_ptr<vector<int>>& spvec){
    int num = 0;
    while (cin >> num){
        spvec->push_back(num);
        char ch = getchar();
        if (ch == '\n')
            break;
    }
}

void printVec(shared_ptr<vector<int>>& spvec){
    for (const auto& v : *spvec){
        cout << v <<" ";
    }
    cout << endl;
}

void test_12_7(){
    cout <<"shared_ptr\n";
    auto spvec = getspvec();
    getSpNum(spvec);
    printVec(spvec);
    
}

int main(){
    test_12_7();
    return 0;
}


//12.8
bool test_12_8(){
    int* p = new int;
    // ... 

    return p;
}
/**
 * 返回类型是一个 bool 类型，但是返回的却是一个常规指针
 * 这样会导致常规指针被隐式地转为bool，从而使得该指针则不能被 delete
 * 其指向的空间将得不到释放。
*/


//12.9
// 该示例很好地说明了智能指针的优势
void test_12_9(){
    // 常规指针
    // q, r 是用 new 申请的常规指针
    int *q = new int(42), *r = new int(100);

    // 将 q 赋值给 r，则 r 和 q 指向同一块内存空间
    // 但 r 原来的空间并没有被释放，而 r 此时又指向其他空间,导致原来的空间将永远得不到释放
    // 因此会导致内存泄漏
    r = q;

    // 智能指针
    // q2 r2 都是 shared_ptr 智能指针
    auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);

    // 将 q2 赋值给 r2, 此时 q2 r2 指向相同的对象，该对象引用计数为2
    // r2 原对象的引用计数-1，变为0，原对象自动被释放
    r2 = q2;
}
