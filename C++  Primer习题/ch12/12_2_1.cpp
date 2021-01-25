#include <iostream>
#include <string>
#include <cstring>
#include <memory>

using namespace std;

// 12_23
void test_12_23()
{
    const char *c1 = "Hello";
    const char *c2 = "World";

    unsigned int len = strlen(c1) + strlen(c2) + 1;
    char *c = new char [len] ();

    strcat_s(c, len, c1);
    strcat_s(c, len, c2);
    cout <<"-------------------\n";
    cout << *c << endl;
    cout << c << endl;

    string s1 = "Hello";
    string s2 = "World";

    strcpy_s(c, len, (s1 + s2).c_str());
    
    cout <<"-------------------\n";
    cout << *c << endl;
    cout << c << endl;

    delete  [] c;

}

// 12_24
// 版本1
void test_12_24_1(){
    cout << "How long do you want the string\n";
    int size{0};
    cin >> size;
    char* input  = new char[size + 1]();
    cin.ignore();
    cout << "input the string : ";
    cin.get(input, size+1);
    cout << input;
    delete [] input;

}

void test_12_24_2(){
    cout <<"Please intput your string :\n";
    string str;
    getline(cin, str);

    char * input = new char[str.size()+1]();
    strcat(input, str.c_str());
    cout << input << endl;

    delete [] input;

}

int main(){
    test_12_24_2();

    return 0;
}