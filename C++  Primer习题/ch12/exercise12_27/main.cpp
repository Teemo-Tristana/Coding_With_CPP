#include <iostream>
#include <string>
#include <fstream>
#include "EX12_27.h"

using namespace std;

void runQueries(ifstream &infile)
{
	TextQuery tq(infile);

	while (true)
	{
		cout << "enter word to look for, or q to quit: ";
		string word;
		if (!(cin >> word) || word == "q")
			break;
		print(cout, tq.query(word)) << endl;
	}
}

int main()
{
	ifstream ifs("./storyDataFile.txt");
	runQueries(ifs);
	return 0;
}