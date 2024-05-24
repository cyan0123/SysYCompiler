#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <utility>

#include "Lex.h"
#include "Syntax.h"

#define TEST 3
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
	else if (TEST == 3)
	{
		Syntax syn;
		syn.analysis(lex.getLex_out());

		ofstream fout;
		fout.open("./output.txt", ios::out);
		list<string> res = syn.getSyn_out();
		for (list<string>::iterator it = res.begin(); it != res.end(); it++)
		{
			fout << *it << '\n';
		}
		fout.close();
	}
	return 0;
}