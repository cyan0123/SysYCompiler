#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <utility>

#include "Lex.h"

#define TEST 2
#define lexlist list<pair<string, string>>

using namespace std;

int main()
{
	ifstream fin;
	fin.open("./testfile.txt", ios::in);
	Lex lex;
	string str;
	while (getline(fin, str))
	{
		lex.analysis(str);
	}
	fin.close();

	if (TEST == 2)
	{
		ofstream fout;
		fout.open("./output.txt", ios::out);
		lexlist res = lex.getLex_out();
		for (lexlist::iterator it = res.begin(); it != res.end(); it++)
		{
			fout << it->first << ' ' << it->second << '\n';
		}
		fout.close();
	}
	return 0;
}