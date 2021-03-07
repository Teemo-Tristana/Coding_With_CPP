<<<<<<< HEAD
#include <iostream>
#include <string>
#include <fstream>

#include "EX12_29.h"

using namespace std;



void runQueries (ifstream &infile)
{
    TextQuery tq (infile);

    while (true) {
        cout << "Enter word to look for, or q to quit: ";
        string s;

        if (!(cin >> s) || s == "q") break;
            print (cout, tq.query(s)) << endl;
    }
}


int main()
{
    ifstream ifs ("C:/Users/tutu/Documents/code/cpp_primer/ch12/textQuery.cpp");
	runQueries (ifs);
    return 0;
=======
#include <iostream>
#include <string>
#include <fstream>

#include "EX12_29.h"

using namespace std;



void runQueries (ifstream &infile)
{
    TextQuery tq (infile);

    while (true) {
        cout << "Enter word to look for, or q to quit: ";
        string s;

        if (!(cin >> s) || s == "q") break;
            print (cout, tq.query(s)) << endl;
    }
}


int main()
{
    ifstream ifs ("C:/Users/tutu/Documents/code/cpp_primer/ch12/textQuery.cpp");
	runQueries (ifs);
    return 0;
>>>>>>> 9a5e9bede5efffbf2eb1d5a82ed59e134223b5e5
}